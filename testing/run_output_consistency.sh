#!/bin/bash

set -u

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
CODE_DIR="$ROOT_DIR"
TEST_DIR="$ROOT_DIR/testing/open_set"
PASCC_BIN="$ROOT_DIR/pascc"
RESULT_DIR="${1:-$ROOT_DIR/testing/output_consistency_results}"
LOG_DIR="$RESULT_DIR/logs"
CASE_DIR_ROOT="$RESULT_DIR/cases"
BUILD_LOG="$LOG_DIR/build_pascc.log"

mkdir -p "$LOG_DIR" "$CASE_DIR_ROOT"

if ! command -v cc >/dev/null 2>&1; then
  echo "missing required C compiler: cc" >&2
  exit 1
fi

if ! command -v fpc >/dev/null 2>&1; then
  echo "missing required Pascal compiler: fpc" >&2
  exit 1
fi

build_pascc() {
  c++ -std=c++17 -I"$CODE_DIR" \
    "$CODE_DIR/pascal_s_driver.cpp" \
    "$CODE_DIR/ast.cpp" \
    "$CODE_DIR/semantic.cpp" \
    "$CODE_DIR/codegen.cpp" \
    "$CODE_DIR/pascal_s_parser.tab.c" \
    "$CODE_DIR/pascal_s_lexer.c" \
    -o "$PASCC_BIN" >"$BUILD_LOG" 2>&1
}

run_case() {
  local exe_path="$1"
  local input_path="$2"
  local stdout_path="$3"
  local stderr_path="$4"

  if [[ -f "$input_path" ]]; then
    "$exe_path" <"$input_path" >"$stdout_path" 2>"$stderr_path"
  else
    "$exe_path" >"$stdout_path" 2>"$stderr_path"
  fi
}

if ! build_pascc; then
  echo "failed to build pascc, see $BUILD_LOG" >&2
  exit 1
fi

shopt -s nullglob
pas_files=("$TEST_DIR"/*.pas)
if [[ ${#pas_files[@]} -eq 0 ]]; then
  echo "no Pascal samples found under $TEST_DIR" >&2
  exit 1
fi

SUMMARY_TSV="$RESULT_DIR/summary.tsv"
SUMMARY_TXT="$RESULT_DIR/summary.txt"

printf "case\tstatus\tdetail\n" >"$SUMMARY_TSV"
{
  echo "Output consistency report"
  echo "root: $ROOT_DIR"
  echo "samples: ${#pas_files[@]}"
  echo
} >"$SUMMARY_TXT"

total=0
passed=0

for pas_file in "${pas_files[@]}"; do
  total=$((total + 1))

  case_name="$(basename "$pas_file" .pas)"
  case_dir="$CASE_DIR_ROOT/$case_name"
  rm -rf "$case_dir"
  mkdir -p "$case_dir"

  case_pas="$case_dir/$case_name.pas"
  case_in="$case_dir/$case_name.in"
  cp "$pas_file" "$case_pas"
  if [[ -f "$TEST_DIR/$case_name.in" ]]; then
    cp "$TEST_DIR/$case_name.in" "$case_in"
  fi

  pascc_log="$LOG_DIR/$case_name.pascc.log"
  cc_log="$LOG_DIR/$case_name.cc.log"
  fpc_log="$LOG_DIR/$case_name.fpc.log"
  diff_log="$LOG_DIR/$case_name.diff.log"

  generated_c="$case_dir/$case_name.c"
  c_exe="$case_dir/$case_name.c.out"
  pas_exe="$case_dir/$case_name.pas.out"
  c_stdout="$case_dir/$case_name.c.stdout"
  c_stderr="$case_dir/$case_name.c.stderr"
  pas_stdout="$case_dir/$case_name.pas.stdout"
  pas_stderr="$case_dir/$case_name.pas.stderr"

  status="PASS"
  detail="-"

  if ! "$PASCC_BIN" -i "$case_pas" >"$pascc_log" 2>&1; then
    status="PASCC_COMPILE_FAIL"
    detail="$pascc_log"
  elif [[ ! -f "$generated_c" ]]; then
    status="PASCC_OUTPUT_MISSING"
    detail="$generated_c"
  elif ! cc -std=c99 "$generated_c" -o "$c_exe" >"$cc_log" 2>&1; then
    status="C_COMPILE_FAIL"
    detail="$cc_log"
  elif ! (
    cd "$case_dir" &&
    fpc -o"$pas_exe" "$case_pas" >"$fpc_log" 2>&1
  ); then
    status="PASCAL_COMPILE_FAIL"
    detail="$fpc_log"
  else
    if run_case "$c_exe" "$case_in" "$c_stdout" "$c_stderr"; then
      :
    else
      c_rc=$?
      status="C_RUNTIME_FAIL"
      detail="exit=$c_rc stderr=$c_stderr"
    fi

    if [[ "$status" == "PASS" ]] && run_case "$pas_exe" "$case_in" "$pas_stdout" "$pas_stderr"; then
      :
    elif [[ "$status" == "PASS" ]]; then
      pas_rc=$?
      status="PASCAL_RUNTIME_FAIL"
      detail="exit=$pas_rc stderr=$pas_stderr"
    fi

    if [[ "$status" == "PASS" ]] && ! cmp -s "$c_stdout" "$pas_stdout"; then
      diff -u "$pas_stdout" "$c_stdout" >"$diff_log" 2>&1 || true
      status="OUTPUT_MISMATCH"
      detail="$diff_log"
    fi

    if [[ "$status" == "PASS" ]]; then
      passed=$((passed + 1))
    fi
  fi

  printf "%s\t%s\t%s\n" "$case_name" "$status" "$detail" >>"$SUMMARY_TSV"
  printf "%-18s %-22s %s\n" "$case_name" "$status" "$detail" >>"$SUMMARY_TXT"
done

{
  echo
  echo "passed: $passed/$total"
} >>"$SUMMARY_TXT"

cat "$SUMMARY_TXT"
