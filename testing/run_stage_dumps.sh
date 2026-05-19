#!/bin/bash
#
# 阶段性中间产物快速验证脚本（无金标准 diff，只跑通并保存输出）。
#
# - testing/test_ast/*.pas      : 走 --stop-after=parse --dump-ast，保存 AST
# - testing/test_semantic/*.pas : 走 --stop-after=semantic --dump-symbols，保存符号表
#
# 用法（在根目录执行）：
#   ./testing/run_stage_dumps.sh
#
# 结果目录默认：testing/stage_dump_results/
#   - ast/<name>.ast      AST dump
#   - symbols/<name>.sym  符号表 dump

set -u

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
CODE_DIR="$ROOT_DIR"
AST_DIR="$ROOT_DIR/testing/test_ast"
SEM_DIR="$ROOT_DIR/testing/test_semantic"
CMAKE_BUILD_DIR="$ROOT_DIR/build"
PASCC_BIN="$CMAKE_BUILD_DIR/bin/pascc"
RESULT_DIR="${1:-$ROOT_DIR/testing/stage_dump_results}"
AST_OUT_DIR="$RESULT_DIR/ast"
SYM_OUT_DIR="$RESULT_DIR/symbols"
LOG_DIR="$RESULT_DIR/logs"
BUILD_LOG="$LOG_DIR/build_pascc.log"

mkdir -p "$AST_OUT_DIR" "$SYM_OUT_DIR" "$LOG_DIR"

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

total=0
failed=0

run_case() {
  local pas="$1"
  local stage="$2"
  local flag="$3"
  local out_dir="$4"
  local name
  name="$(basename "${pas%.pas}")"
  local out_file="$out_dir/$name.${stage}"
  local err_file="$LOG_DIR/$name.$stage.stderr"

  total=$((total + 1))
  if "$PASCC_BIN" -i "$pas" "--stop-after=$stage" "$flag" \
        >/dev/null 2>"$err_file"; then
    mv "$err_file" "$out_file"
    echo "[ok]   $stage  $name"
  else
    failed=$((failed + 1))
    echo "[FAIL] $stage  $name  (see $err_file)"
  fi
}

shopt -s nullglob

for pas in "$AST_DIR"/*.pas; do
  run_case "$pas" parse --dump-ast "$AST_OUT_DIR"
done

for pas in "$SEM_DIR"/*.pas; do
  run_case "$pas" semantic --dump-symbols "$SYM_OUT_DIR"
done

echo
echo "total=$total no_output=$failed"
echo "ast dumps in:     $AST_OUT_DIR"
echo "symbol dumps in:  $SYM_OUT_DIR"
echo "（[FAIL] 表示该样例在对应阶段就出错了——比如 test_ast/test.pas 是故意的语法错误样例）"
