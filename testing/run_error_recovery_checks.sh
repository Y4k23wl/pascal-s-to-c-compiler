#!/bin/bash

set -u

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
CODE_DIR="$ROOT_DIR"
RECOVERY_DIR="$ROOT_DIR/testing/error_recovery"
SEMANTIC_DIR="$ROOT_DIR/testing/semantic_errors"
CMAKE_BUILD_DIR="$ROOT_DIR/build"
PASCC_BIN="$CMAKE_BUILD_DIR/bin/pascc"
RESULT_DIR="${1:-$ROOT_DIR/testing/error_recovery_results}"
LOG_DIR="$RESULT_DIR/logs"
BUILD_LOG="$LOG_DIR/build_pascc.log"
TIMEOUT_SECS=10

mkdir -p "$LOG_DIR"

build_pascc() {
  if ! cmake -S "$CODE_DIR" -B "$CMAKE_BUILD_DIR" -DCMAKE_BUILD_TYPE=Release >"$BUILD_LOG" 2>&1; then
    return 1
  fi
  if ! cmake --build "$CMAKE_BUILD_DIR" --config Release >>"$BUILD_LOG" 2>&1; then
    return 1
  fi
  if [[ -x "$CMAKE_BUILD_DIR/bin/pascc.exe" ]]; then
    PASCC_BIN="$CMAKE_BUILD_DIR/bin/pascc.exe"
  fi
  [[ -x "$PASCC_BIN" ]]
}

if ! build_pascc; then
  echo "failed to build pascc, see $BUILD_LOG" >&2
  exit 1
fi

shopt -s nullglob
pas_files=()
for dir in "$RECOVERY_DIR" "$SEMANTIC_DIR"; do
  for f in "$dir"/*.pas; do
    pas_files+=("$f")
  done
done

if [[ ${#pas_files[@]} -eq 0 ]]; then
  echo "no error samples found under $RECOVERY_DIR or $SEMANTIC_DIR" >&2
  exit 1
fi

SUMMARY_TSV="$RESULT_DIR/summary.tsv"
SUMMARY_TXT="$RESULT_DIR/summary.txt"

printf "case\tcategory\tstatus\texit_code\texpected_exit\tstderr_log\n" >"$SUMMARY_TSV"
{
  echo "Error recovery report"
  echo "root: $ROOT_DIR"
  echo "samples: ${#pas_files[@]}"
  echo
} >"$SUMMARY_TXT"

pass_count=0
fail_count=0

run_with_timeout() {
  # $1: timeout secs, $2..: command
  local secs="$1"; shift
  "$@" &
  local pid=$!
  ( sleep "$secs"; kill -9 "$pid" 2>/dev/null ) &
  local watcher=$!
  local rc=0
  wait "$pid" 2>/dev/null || rc=$?
  kill "$watcher" 2>/dev/null
  wait 2>/dev/null
  return "$rc"
}

for pas_file in "${pas_files[@]}"; do
  case_dir="$(dirname "$pas_file")"
  case_name="$(basename "$pas_file" .pas)"
  category="$(basename "$case_dir")"
  stdout_log="$LOG_DIR/${category}__${case_name}.stdout.log"
  stderr_log="$LOG_DIR/${category}__${case_name}.stderr.log"
  diff_log="$LOG_DIR/${category}__${case_name}.diff.log"
  expected_stderr="${pas_file%.pas}.expected.stderr"
  expected_exit_file="${pas_file%.pas}.expected.exit"

  run_with_timeout "$TIMEOUT_SECS" "$PASCC_BIN" -i "$pas_file" >"$stdout_log" 2>"$stderr_log"
  exit_code=$?

  status="PASS"
  detail=""

  if [[ "$exit_code" -eq 137 || "$exit_code" -eq 9 ]]; then
    status="TIMEOUT"
    detail="exceeded ${TIMEOUT_SECS}s"
  fi

  if [[ ! -f "$expected_stderr" ]]; then
    status="MISSING_GOLDEN"
    detail="$expected_stderr not found"
  fi

  if [[ "$status" == "PASS" ]]; then
    if ! diff -u "$expected_stderr" "$stderr_log" >"$diff_log" 2>&1; then
      status="STDERR_MISMATCH"
      detail="$diff_log"
    else
      rm -f "$diff_log"
    fi
  fi

  expected_exit=""
  if [[ -f "$expected_exit_file" ]]; then
    expected_exit="$(tr -d '[:space:]' <"$expected_exit_file")"
    if [[ "$status" == "PASS" && "$expected_exit" != "$exit_code" ]]; then
      status="EXIT_MISMATCH"
      detail="expected=$expected_exit actual=$exit_code"
    fi
  fi

  if [[ "$status" == "PASS" ]]; then
    pass_count=$((pass_count + 1))
  else
    fail_count=$((fail_count + 1))
  fi

  printf "%s\t%s\t%s\t%s\t%s\t%s\n" "$case_name" "$category" "$status" "$exit_code" "$expected_exit" "$stderr_log" >>"$SUMMARY_TSV"
  {
    echo "[$category/$case_name]"
    echo "status: $status"
    echo "exit: $exit_code (expected: ${expected_exit:-?})"
    echo "stderr: $stderr_log"
    if [[ -n "$detail" ]]; then
      echo "detail: $detail"
    fi
    echo
  } >>"$SUMMARY_TXT"
done

{
  echo "passed: $pass_count/${#pas_files[@]}"
  echo "failed: $fail_count/${#pas_files[@]}"
} >>"$SUMMARY_TXT"

echo "wrote error recovery logs to $RESULT_DIR"
echo "passed: $pass_count/${#pas_files[@]}  failed: $fail_count/${#pas_files[@]}"

if [[ "$fail_count" -gt 0 ]]; then
  exit 1
fi
exit 0
