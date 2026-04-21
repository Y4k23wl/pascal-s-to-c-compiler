#!/bin/bash

set -u

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
CODE_DIR="$ROOT_DIR"
TEST_DIR="$ROOT_DIR/testing/error_recovery"
CMAKE_BUILD_DIR="$ROOT_DIR/build"
PASCC_BIN="$CMAKE_BUILD_DIR/bin/pascc"
RESULT_DIR="${1:-$ROOT_DIR/testing/error_recovery_results}"
LOG_DIR="$RESULT_DIR/logs"
BUILD_LOG="$LOG_DIR/build_pascc.log"

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
pas_files=("$TEST_DIR"/*.pas)
if [[ ${#pas_files[@]} -eq 0 ]]; then
  echo "no error recovery samples found under $TEST_DIR" >&2
  exit 1
fi

SUMMARY_TSV="$RESULT_DIR/summary.tsv"
SUMMARY_TXT="$RESULT_DIR/summary.txt"

printf "case\tstatus\texit_code\tstderr_log\n" >"$SUMMARY_TSV"
{
  echo "Error recovery report"
  echo "root: $ROOT_DIR"
  echo "samples: ${#pas_files[@]}"
  echo
} >"$SUMMARY_TXT"

for pas_file in "${pas_files[@]}"; do
  case_name="$(basename "$pas_file" .pas)"
  stdout_log="$LOG_DIR/$case_name.stdout.log"
  stderr_log="$LOG_DIR/$case_name.stderr.log"

  if "$PASCC_BIN" -i "$pas_file" >"$stdout_log" 2>"$stderr_log"; then
    status="UNEXPECTED_SUCCESS"
    exit_code=0
  else
    exit_code=$?
    status="EXPECTED_FAIL"
  fi

  printf "%s\t%s\t%s\t%s\n" "$case_name" "$status" "$exit_code" "$stderr_log" >>"$SUMMARY_TSV"
  {
    echo "[$case_name]"
    echo "status: $status"
    echo "exit: $exit_code"
    echo "stderr: $stderr_log"
    echo
  } >>"$SUMMARY_TXT"
done

echo "wrote error recovery logs to $RESULT_DIR"
