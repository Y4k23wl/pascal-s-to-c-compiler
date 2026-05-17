#!/usr/bin/env python3

from __future__ import annotations

import argparse
import difflib
import os
import shutil
import subprocess
import sys
from pathlib import Path


ROOT_DIR = Path(__file__).resolve().parent.parent
TESTING_DIR = ROOT_DIR / "testing"
BUILD_DIR = ROOT_DIR / "build"
PASCC_PATHS = [BUILD_DIR / "bin" / "pascc.exe", BUILD_DIR / "bin" / "pascc"]


def run_command(cmd: list[str], *, stdout_path: Path | None = None, stderr_path: Path | None = None,
                cwd: Path | None = None, input_path: Path | None = None) -> int:
    shared_output = stdout_path is not None and stderr_path is not None and stdout_path == stderr_path
    stdout_handle = open(stdout_path, "wb") if stdout_path is not None else subprocess.DEVNULL
    stderr_handle = stdout_handle if shared_output else (
        open(stderr_path, "wb") if stderr_path is not None else subprocess.DEVNULL
    )
    stdin_handle = open(input_path, "rb") if input_path is not None else None

    try:
        proc = subprocess.run(
            cmd,
            cwd=str(cwd) if cwd is not None else None,
            stdin=stdin_handle,
            stdout=stdout_handle,
            stderr=stderr_handle,
            check=False,
        )
        return proc.returncode
    finally:
        if stdin_handle is not None:
            stdin_handle.close()
        if stdout_path is not None:
            stdout_handle.close()
        if stderr_path is not None and not shared_output:
            stderr_handle.close()


def find_pascc() -> Path | None:
    for path in PASCC_PATHS:
        if path.exists():
            return path
    return None


def build_pascc(build_log: Path, build_type: str) -> Path:
    build_log.parent.mkdir(parents=True, exist_ok=True)
    with open(build_log, "wb") as log:
        configure = subprocess.run(
            ["cmake", "-S", str(ROOT_DIR), "-B", str(BUILD_DIR), f"-DCMAKE_BUILD_TYPE={build_type}"],
            stdout=log,
            stderr=subprocess.STDOUT,
            check=False,
        )
        if configure.returncode != 0:
            raise RuntimeError(f"failed to configure project, see {build_log}")

        build = subprocess.run(
            ["cmake", "--build", str(BUILD_DIR), "--config", build_type],
            stdout=log,
            stderr=subprocess.STDOUT,
            check=False,
        )
        if build.returncode != 0:
            raise RuntimeError(f"failed to build project, see {build_log}")

    pascc = find_pascc()
    if pascc is None:
        raise RuntimeError("build finished but pascc executable was not found under build/bin")
    return pascc


def choose_c_compiler(explicit: str | None) -> str:
    if explicit:
        return explicit
    for candidate in ("cc", "clang", "gcc", "cl"):
        path = shutil.which(candidate)
        if path is not None:
            return path
    raise RuntimeError("missing required C compiler: expected one of cc/clang/gcc/cl")


def choose_pascal_compiler(explicit: str | None) -> str:
    if explicit:
        return explicit
    path = shutil.which("fpc")
    if path is None:
        raise RuntimeError("missing required Pascal compiler: fpc")
    return path


def compile_c_source(compiler: str, source_path: Path, exe_path: Path, log_path: Path) -> int:
    compiler_name = Path(compiler).name.lower()
    if compiler_name == "cl" or compiler_name == "cl.exe":
        cmd = [
            compiler,
            "/nologo",
            "/TC",
            str(source_path),
            f"/Fe:{exe_path}",
        ]
    else:
        cmd = [compiler, "-std=c99", str(source_path), "-o", str(exe_path)]
    return run_command(cmd, stdout_path=log_path, stderr_path=log_path)


def compile_pascal_source(compiler: str, source_path: Path, exe_path: Path, log_path: Path, cwd: Path) -> int:
    cmd = [compiler, f"-o{exe_path.name}", str(source_path.name)]
    return run_command(cmd, stdout_path=log_path, stderr_path=log_path, cwd=cwd)


def write_text(path: Path, text: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text, encoding="utf-8")


def output_consistency(args: argparse.Namespace) -> int:
    test_dir = TESTING_DIR / "open_set"
    result_dir = Path(args.result_dir) if args.result_dir else TESTING_DIR / "output_consistency_results"
    log_dir = result_dir / "logs"
    case_root = result_dir / "cases"
    build_log = log_dir / "build_pascc.log"

    log_dir.mkdir(parents=True, exist_ok=True)
    case_root.mkdir(parents=True, exist_ok=True)

    pascc = build_pascc(build_log, args.build_type)
    c_compiler = choose_c_compiler(args.c_compiler)
    pascal_compiler = choose_pascal_compiler(args.pascal_compiler)

    pas_files = sorted(test_dir.glob("*.pas"))
    if not pas_files:
        print(f"no Pascal samples found under {test_dir}", file=sys.stderr)
        return 1

    summary_tsv = result_dir / "summary.tsv"
    summary_txt = result_dir / "summary.txt"
    write_text(summary_tsv, "case\tstatus\tdetail\n")
    write_text(
        summary_txt,
        f"Output consistency report\nroot: {ROOT_DIR}\nsamples: {len(pas_files)}\n\n",
    )

    total = 0
    passed = 0

    for pas_file in pas_files:
        total += 1
        case_name = pas_file.stem
        case_dir = case_root / case_name
        if case_dir.exists():
            shutil.rmtree(case_dir)
        case_dir.mkdir(parents=True)

        case_pas = case_dir / f"{case_name}.pas"
        case_in = case_dir / f"{case_name}.in"
        shutil.copy2(pas_file, case_pas)

        original_input = test_dir / f"{case_name}.in"
        if original_input.exists():
            shutil.copy2(original_input, case_in)

        pascc_log = log_dir / f"{case_name}.pascc.log"
        cc_log = log_dir / f"{case_name}.cc.log"
        fpc_log = log_dir / f"{case_name}.fpc.log"
        diff_log = log_dir / f"{case_name}.diff.log"

        generated_c = case_dir / f"{case_name}.c"
        c_exe = case_dir / (f"{case_name}.c.exe" if os.name == "nt" else f"{case_name}.c.out")
        pas_exe = case_dir / (f"{case_name}.pas.exe" if os.name == "nt" else f"{case_name}.pas.out")
        c_stdout = case_dir / f"{case_name}.c.stdout"
        c_stderr = case_dir / f"{case_name}.c.stderr"
        pas_stdout = case_dir / f"{case_name}.pas.stdout"
        pas_stderr = case_dir / f"{case_name}.pas.stderr"

        status = "PASS"
        detail = "-"

        if run_command([str(pascc), "-i", str(case_pas)], stdout_path=pascc_log, stderr_path=pascc_log) != 0:
            status = "PASCC_COMPILE_FAIL"
            detail = str(pascc_log)
        elif not generated_c.exists():
            status = "PASCC_OUTPUT_MISSING"
            detail = str(generated_c)
        elif compile_c_source(c_compiler, generated_c, c_exe, cc_log) != 0:
            status = "C_COMPILE_FAIL"
            detail = str(cc_log)
        elif compile_pascal_source(pascal_compiler, case_pas, pas_exe, fpc_log, case_dir) != 0:
            status = "PASCAL_COMPILE_FAIL"
            detail = str(fpc_log)
        else:
            input_path = case_in if case_in.exists() else None

            c_rc = run_command([str(c_exe)], input_path=input_path, stdout_path=c_stdout, stderr_path=c_stderr)
            if c_rc != 0:
                status = "C_RUNTIME_FAIL"
                detail = f"exit={c_rc} stderr={c_stderr}"

            if status == "PASS":
                pas_rc = run_command([str(pas_exe)], input_path=input_path, stdout_path=pas_stdout, stderr_path=pas_stderr)
                if pas_rc != 0:
                    status = "PASCAL_RUNTIME_FAIL"
                    detail = f"exit={pas_rc} stderr={pas_stderr}"

            if status == "PASS":
                c_bytes = c_stdout.read_bytes()
                pas_bytes = pas_stdout.read_bytes()
                if c_bytes != pas_bytes:
                    pas_text = pas_bytes.decode("utf-8", errors="replace").splitlines(keepends=True)
                    c_text = c_bytes.decode("utf-8", errors="replace").splitlines(keepends=True)
                    diff = "".join(
                        difflib.unified_diff(
                            pas_text,
                            c_text,
                            fromfile=str(pas_stdout),
                            tofile=str(c_stdout),
                        )
                    )
                    write_text(diff_log, diff)
                    status = "OUTPUT_MISMATCH"
                    detail = str(diff_log)

            if status == "PASS":
                passed += 1

        with summary_tsv.open("a", encoding="utf-8") as out_tsv:
            out_tsv.write(f"{case_name}\t{status}\t{detail}\n")
        with summary_txt.open("a", encoding="utf-8") as out_txt:
            out_txt.write(f"{case_name:<18} {status:<22} {detail}\n")

    with summary_txt.open("a", encoding="utf-8") as out_txt:
        out_txt.write(f"\npassed: {passed}/{total}\n")

    print(summary_txt.read_text(encoding="utf-8"), end="")
    return 0 if passed == total else 1


RECOVERY_TIMEOUT_SECS = 10


def _run_pascc_with_timeout(pascc: Path, pas_file: Path, stdout_path: Path, stderr_path: Path, timeout: int) -> tuple[int, bool]:
    """Run pascc on a sample with a hard timeout. Returns (exit_code, timed_out)."""
    with open(stdout_path, "wb") as out_h, open(stderr_path, "wb") as err_h:
        try:
            proc = subprocess.run(
                [str(pascc), "-i", str(pas_file)],
                stdout=out_h,
                stderr=err_h,
                check=False,
                timeout=timeout,
            )
            return proc.returncode, False
        except subprocess.TimeoutExpired:
            return -1, True


def error_recovery(args: argparse.Namespace) -> int:
    sample_dirs = [TESTING_DIR / "error_recovery", TESTING_DIR / "semantic_errors"]
    result_dir = Path(args.result_dir) if args.result_dir else TESTING_DIR / "error_recovery_results"
    log_dir = result_dir / "logs"
    build_log = log_dir / "build_pascc.log"

    log_dir.mkdir(parents=True, exist_ok=True)
    pascc = build_pascc(build_log, args.build_type)

    pas_files: list[Path] = []
    for d in sample_dirs:
        pas_files.extend(sorted(d.glob("*.pas")))
    if not pas_files:
        names = ", ".join(str(d) for d in sample_dirs)
        print(f"no error samples found under {names}", file=sys.stderr)
        return 1

    summary_tsv = result_dir / "summary.tsv"
    summary_txt = result_dir / "summary.txt"
    write_text(summary_tsv, "case\tcategory\tstatus\texit_code\texpected_exit\tstderr_log\n")
    write_text(
        summary_txt,
        f"Error recovery report\nroot: {ROOT_DIR}\nsamples: {len(pas_files)}\n\n",
    )

    pass_count = 0
    fail_count = 0

    for pas_file in pas_files:
        case_name = pas_file.stem
        category = pas_file.parent.name
        stem = f"{category}__{case_name}"
        stdout_log = log_dir / f"{stem}.stdout.log"
        stderr_log = log_dir / f"{stem}.stderr.log"
        diff_log = log_dir / f"{stem}.diff.log"
        expected_stderr = pas_file.with_suffix(".expected.stderr")
        expected_exit_file = pas_file.with_suffix(".expected.exit")

        exit_code, timed_out = _run_pascc_with_timeout(
            pascc, pas_file, stdout_log, stderr_log, RECOVERY_TIMEOUT_SECS
        )

        status = "PASS"
        detail = ""
        expected_exit_str = ""

        if timed_out:
            status = "TIMEOUT"
            detail = f"exceeded {RECOVERY_TIMEOUT_SECS}s"
        elif not expected_stderr.exists():
            status = "MISSING_GOLDEN"
            detail = f"{expected_stderr} not found"
        else:
            expected_bytes = expected_stderr.read_bytes()
            actual_bytes = stderr_log.read_bytes()
            if expected_bytes != actual_bytes:
                exp_text = expected_bytes.decode("utf-8", errors="replace").splitlines(keepends=True)
                act_text = actual_bytes.decode("utf-8", errors="replace").splitlines(keepends=True)
                diff = "".join(difflib.unified_diff(
                    exp_text, act_text,
                    fromfile=str(expected_stderr), tofile=str(stderr_log),
                ))
                write_text(diff_log, diff)
                status = "STDERR_MISMATCH"
                detail = str(diff_log)

        if expected_exit_file.exists():
            expected_exit_str = expected_exit_file.read_text(encoding="utf-8").strip()
            if status == "PASS" and expected_exit_str != str(exit_code):
                status = "EXIT_MISMATCH"
                detail = f"expected={expected_exit_str} actual={exit_code}"

        if status == "PASS":
            pass_count += 1
        else:
            fail_count += 1

        with summary_tsv.open("a", encoding="utf-8") as out_tsv:
            out_tsv.write(
                f"{case_name}\t{category}\t{status}\t{exit_code}\t{expected_exit_str}\t{stderr_log}\n"
            )
        with summary_txt.open("a", encoding="utf-8") as out_txt:
            out_txt.write(
                f"[{category}/{case_name}]\n"
                f"status: {status}\n"
                f"exit: {exit_code} (expected: {expected_exit_str or '?'})\n"
                f"stderr: {stderr_log}\n"
            )
            if detail:
                out_txt.write(f"detail: {detail}\n")
            out_txt.write("\n")

    with summary_txt.open("a", encoding="utf-8") as out_txt:
        out_txt.write(f"passed: {pass_count}/{len(pas_files)}\n")
        out_txt.write(f"failed: {fail_count}/{len(pas_files)}\n")

    print(f"wrote error recovery logs to {result_dir}")
    print(f"passed: {pass_count}/{len(pas_files)}  failed: {fail_count}/{len(pas_files)}")
    return 0 if fail_count == 0 else 1


def main() -> int:
    parser = argparse.ArgumentParser(description="Cross-platform test driver for pascc.")
    parser.add_argument("--build-type", default="Release", help="CMake build type, default: Release")

    subparsers = parser.add_subparsers(dest="command", required=True)

    output_parser = subparsers.add_parser("output-consistency", help="Run open-set end-to-end comparison")
    output_parser.add_argument("--result-dir", help="Override result directory")
    output_parser.add_argument("--c-compiler", help="Override C compiler command")
    output_parser.add_argument("--pascal-compiler", help="Override Pascal compiler command")
    output_parser.set_defaults(func=output_consistency)

    recovery_parser = subparsers.add_parser("error-recovery", help="Run error recovery checks")
    recovery_parser.add_argument("--result-dir", help="Override result directory")
    recovery_parser.set_defaults(func=error_recovery)

    args = parser.parse_args()
    try:
        return args.func(args)
    except RuntimeError as exc:
        print(str(exc), file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
