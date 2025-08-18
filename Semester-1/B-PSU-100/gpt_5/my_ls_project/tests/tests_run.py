#!/usr/bin/env python3
# Stdlib-only test runner for my_ls
import os, subprocess, tempfile, shutil, sys, textwrap

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
BIN = os.path.join(ROOT, "my_ls")

def run(cmd, cwd=None):
    p = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, cwd=cwd)
    out, err = p.communicate()
    return p.returncode, out.decode("utf-8", "ignore"), err.decode("utf-8", "ignore")

def require_compiled():
    if not os.path.exists(BIN):
        print("KO - binary not found, did you run make?", file=sys.stderr)
        sys.exit(84)

def ok(label):
    print(f"OK  - {label}")

def ko(label, details=""):
    print(f"KO  - {label}")
    if details:
        print(textwrap.indent(details, prefix="     "))
    return False

def main():
    require_compiled()
    tmp = tempfile.mkdtemp(prefix="my_ls_tests_")
    try:
        # Fixtures
        d1 = os.path.join(tmp, "dir1")
        d2 = os.path.join(tmp, "dir1", "sub")
        os.makedirs(d2, exist_ok=True)
        with open(os.path.join(tmp, "a.txt"), "w") as f:
            f.write("A")
        with open(os.path.join(tmp, ".hidden"), "w") as f:
            f.write("H")
        with open(os.path.join(d1, "b.txt"), "w") as f:
            f.write("B")

        # 1) basic run
        code, out, err = run([BIN], cwd=tmp)
        assert code == 0, "basic run should exit 0"
        assert "a.txt" in out, "should list a.txt"
        ok("basic run")

        # 2) -a shows hidden
        code, out, err = run([BIN, "-a"], cwd=tmp)
        assert code == 0, "-a exit 0"
        assert ".hidden" in out, "hidden file should be listed with -a"
        ok("-a shows hidden")

        # 3) -l format starts with permissions and contains size
        code, out, err = run([BIN, "-l"], cwd=tmp)
        assert code == 0, "-l exit 0"
        assert "total" in out.splitlines()[0], "should show total line"
        # look for typical '-rw' pattern
        assert any(line.startswith(("-", "d", "l")) for line in out.splitlines()[1:]), "long format lines"
        ok("-l long format")

        # 4) -d prints directory itself, not contents
        code, out, err = run([BIN, "-d", "dir1"], cwd=tmp)
        assert code == 0, "-d exit 0"
        assert out.strip() == "dir1", "should print just directory name"
        ok("-d prints directory entry")

        # 5) -R recursive shows subfolder header
        code, out, err = run([BIN, "-R", "dir1"], cwd=tmp)
        assert code == 0, "-R exit 0"
        assert "dir1:" in out or "\ndir1:\n" in out, "should print dir header"
        ok("-R recursive")

        # 6) -t/-r don't crash (sorting covered implicitly)
        code, out, err = run([BIN, "-tr"], cwd=tmp)
        assert code == 0, "-tr exit 0"
        ok("-t/-r options")

        # 7) invalid option => exit 84
        code, out, err = run([BIN, "-Z"], cwd=tmp)
        assert code == 84, "invalid option should exit 84"
        assert "invalid option" in err, "error message on stderr"
        ok("invalid option => 84")

        print("\nAll tests passed.")
    except AssertionError as e:
        print("Test failure:", e, file=sys.stderr)
        sys.exit(84)
    finally:
        shutil.rmtree(tmp, ignore_errors=True)

if __name__ == "__main__":
    main()
