#!/usr/bin/env python3
import os
import re
import sys
import subprocess
import shutil
from datetime import datetime
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def log(msg: str, log_fp):
    ts = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    line = f"[{ts}] {msg}\n"
    sys.stdout.write(line)
    sys.stdout.flush()
    if log_fp:
        log_fp.write(line)
        log_fp.flush()


def list_semesters(root: Path):
    return sorted([p for p in root.iterdir() if p.is_dir() and p.name.startswith("Semester-")])


def is_project_dir(path: Path) -> bool:
    # Heuristic: a project directory is a leaf with any of these markers
    markers = ["Makefile", "README.md", "readme.md", "src", "include"]
    if not path.is_dir():
        return False
    # Ignore .venv, reports, logs, scripts root
    if path.name in {"reports", "logs", "scripts", ".venv"}:
        return False
    # Has files or common project dirs
    for m in markers:
        if (path / m).exists():
            return True
    # Or contains a pdf
    if list(path.glob("*.pdf")):
        return True
    # Leaf with files inside but no deeper dirs
    return any(path.glob("*")) and not any(c.is_dir() for c in path.iterdir())


def find_projects(semester_dir: Path):
    projects = []
    # Common Epitech layout: Semester-X/<UE>/<Project>
    for ue_dir in sorted([p for p in semester_dir.iterdir() if p.is_dir()]):
        for proj_dir in sorted([p for p in ue_dir.iterdir() if p.is_dir()]):
            if is_project_dir(proj_dir):
                projects.append(proj_dir)
    return projects


def choose_pdf(pdfs):
    if not pdfs:
        return None
    # Prefer subject*.pdf
    subjects = [p for p in pdfs if re.search(r"subject", p.name, re.I)]
    if subjects:
        pdfs = subjects
    # Prefer names with fewer trailing digits
    def score(p: Path):
        # lower is better
        m = re.search(r"(\d+)(?=\.pdf$)", p.name)
        dcount = len(m.group(1)) if m else 0
        return (dcount, -p.stat().st_mtime)

    return sorted(pdfs, key=score)[0]


def extract_pdf_text(pdf_path: Path, log_fp, max_pages=5) -> str:
    # Try pdftotext if available
    if shutil.which("pdftotext"):
        try:
            res = subprocess.run([
                "pdftotext", "-q", "-enc", "UTF-8", str(pdf_path), "-"
            ], check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            return res.stdout.decode("utf-8", errors="ignore")
        except Exception as e:
            log(f"pdftotext failed for {pdf_path}: {e}", log_fp)
    # Fallback to PyPDF2
    try:
        import PyPDF2  # type: ignore
    except Exception:
        try:
            subprocess.run([sys.executable, "-m", "pip", "install", "--quiet", "PyPDF2"], check=True)
            import PyPDF2  # type: ignore
        except Exception as e:
            log(f"PyPDF2 install failed: {e}", log_fp)
            return ""
    try:
        text_parts = []
        with open(pdf_path, "rb") as f:
            reader = PyPDF2.PdfReader(f)
            n = min(len(reader.pages), max_pages)
            for i in range(n):
                try:
                    text_parts.append(reader.pages[i].extract_text() or "")
                except Exception as e:
                    log(f"PyPDF2 page {i} error: {e}", log_fp)
        return "\n".join(text_parts)
    except Exception as e:
        log(f"PyPDF2 read failed for {pdf_path}: {e}", log_fp)
        return ""


def detect_language(project_dir: Path):
    exts = set(p.suffix for p in project_dir.rglob("*") if p.is_file())
    if any(e in exts for e in [".c", ".h"]):
        return "C"
    if any(e in exts for e in [".cpp", ".hpp", ".cc", ".hh"]):
        return "C++"
    if ".py" in exts:
        return "Python"
    if ".hs" in exts:
        return "Haskell"
    if ".rs" in exts:
        return "Rust"
    if ".java" in exts:
        return "Java"
    if ".js" in exts or ".ts" in exts:
        return "JavaScript/TypeScript"
    return "Unknown"


def has_make_test(makefile_path: Path) -> bool:
    try:
        txt = makefile_path.read_text(errors="ignore")
        return bool(re.search(r"^test\s*:\s*$", txt, re.M))
    except Exception:
        return False


def ensure_test_scaffold(project_dir: Path, log_fp):
    scripts_dir = project_dir / "scripts"
    scripts_dir.mkdir(exist_ok=True)
    test_sh = scripts_dir / "test.sh"
    if not test_sh.exists():
        test_sh.write_text("""#!/usr/bin/env bash
set -euo pipefail
echo "[INFO] No tests defined yet for $(basename $(pwd))."
exit 0
""")
        test_sh.chmod(0o755)
        log(f"Created {test_sh}", log_fp)
    mk = project_dir / "Makefile"
    if mk.exists() and not has_make_test(mk):
        with mk.open("a") as f:
            f.write("\n\n# Added by auto_report.py\n.PHONY: test\nTEST_SCRIPT=./scripts/test.sh\n\ntest:\n\t@if [ -x $$(echo $(TEST_SCRIPT)) ]; then \\\n\t\t$$(echo $(TEST_SCRIPT)); \\\n\telse \\\n\t\techo 'No tests script found'; \\\n\tfi\n")
        log(f"Appended test target to {mk}", log_fp)


def ensure_readme(project_dir: Path, semester_name: str, ue_name: str, project_name: str, report_rel: Path, log_fp):
    readme = project_dir / "README.md"
    if readme.exists():
        return
    content = f"""
# {project_name}

Semester: {semester_name} — UE: {ue_name}

Overview
- See the generated report for subject summary and plan: `{report_rel}`

Build
- If a `Makefile` exists: `make`

Run
- See project-specific instructions in the report and/or subject.

Test
- `make test` (provided stub; extend `scripts/test.sh`).

Dependencies
- Depends on the project language/toolchain. Install as needed.
""".strip() + "\n"
    readme.write_text(content)
    log(f"Created {readme}", log_fp)


def summarize_text(text: str) -> dict:
    # Very light heuristic extraction into buckets
    lines = [l.strip() for l in text.splitlines() if l.strip()]
    buckets = {"objectives": [], "deliverables": [], "constraints": [], "evaluation": [], "examples": []}
    cur = None
    for l in lines[:800]:  # limit scanning
        low = l.lower()
        if any(k in low for k in ["objective", "goal", "purpose"]):
            cur = "objectives"
        elif any(k in low for k in ["deliverable", "turn-in", "hand-in"]):
            cur = "deliverables"
        elif any(k in low for k in ["constraint", "forbidden", "authorized", "allowed", "not allowed"]):
            cur = "constraints"
        elif any(k in low for k in ["evaluation", "grading", "marking", "criteria"]):
            cur = "evaluation"
        elif any(k in low for k in ["example", "usage", "expected output"]):
            cur = "examples"
        if cur:
            # Keep short lines that look like bullet/requirement lines
            if re.match(r"^[-•].+", l) or len(l) < 120:
                buckets[cur].append(l)
    return buckets


def generate_report(semester_dir: Path, project_dir: Path, log_fp, text_src: str, text: str, ambiguity_note: str):
    semester_name = semester_dir.name
    ue_name = project_dir.parent.name
    project_name = project_dir.name
    out_dir = ROOT / "reports" / semester_name
    out_dir.mkdir(parents=True, exist_ok=True)
    out_path = out_dir / f"{project_name}.md"

    buckets = summarize_text(text)
    lang = detect_language(project_dir)
    has_mk = (project_dir / "Makefile").exists()
    has_tests = (project_dir / "tests").exists() or (project_dir / "scripts" / "test.sh").exists()

    requirements = []
    for sec, lines in buckets.items():
        for l in lines:
            tag = "MUST" if re.search(r"\b(must|required|have to|mandatory|shall)\b", l, re.I) else (
                "SHOULD" if re.search(r"\b(should|recommended)\b", l, re.I) else "OPTIONAL"
            )
            requirements.append((tag, l))

    # Trim long list
    requirements = requirements[:30]

    content = []
    content.append(f"# {project_name}")
    content.append("")
    content.append(f"- Semester: {semester_name}")
    content.append(f"- UE: {ue_name}")
    content.append(f"- Subject source: `{text_src}`")
    if ambiguity_note:
        content.append(f"- Note: {ambiguity_note}")
    content.append("")
    content.append("## Summary")
    if text:
        preview = " ".join(text.split())[:800]
        content.append(preview + ("…" if len(text) > 800 else ""))
    else:
        content.append("No extractable subject text. See README or code.")
    content.append("")
    content.append("## Requirements (heuristic)")
    if requirements:
        for tag, l in requirements:
            content.append(f"- [{tag}] {l}")
    else:
        content.append("- [MUST] Implement per subject. (Details not auto-extracted)")
    content.append("")
    content.append("## Plan (initial)")
    content.append("- Parsing/IO setup")
    content.append("- Core logic")
    content.append("- Error handling")
    content.append("- Tests from examples + edge cases")
    content.append("")
    content.append("## Implementation Status")
    content.append(f"- Language: {lang}")
    content.append(f"- Makefile: {'yes' if has_mk else 'no'}")
    content.append(f"- Tests present: {'yes' if has_tests else 'no'}")
    content.append("")
    content.append("## How To Test")
    content.append("- Build: `make` (if available)")
    content.append("- Run tests: `make test` (stub added when missing)")
    content.append("")
    content.append("## Risks / Gaps")
    content.append("- Auto-extracted summary may miss constraints.")
    content.append("- Manual review recommended before final submission.")

    out_path.write_text("\n".join(content))
    log(f"Wrote report {out_path}", log_fp)

    # Ensure per-project README and test stubs
    report_rel = out_path.relative_to(ROOT)
    ensure_readme(project_dir, semester_name, ue_name, project_name, report_rel, log_fp)
    ensure_test_scaffold(project_dir, log_fp)


def main():
    timestamp = datetime.now().strftime("%Y%m%d-%H%M%S")
    logs_dir = ROOT / "logs"
    logs_dir.mkdir(exist_ok=True)
    log_path = logs_dir / f"session-{timestamp}.log"
    with open(log_path, "a") as log_fp:
        log(f"Session started at {timestamp}", log_fp)
        semesters = list_semesters(ROOT)
        log(f"Found semesters: {[s.name for s in semesters]}", log_fp)
        total_projects = 0
        for sem in semesters:
            projects = find_projects(sem)
            log(f"{sem.name}: {len(projects)} project(s)", log_fp)
            for proj in projects:
                total_projects += 1
                log(f"Processing {proj}", log_fp)
                pdfs = list(proj.glob("*.pdf"))
                readmes = [*proj.glob("README*"), *proj.glob("readme*"), *proj.glob("Readme*")]
                subject_src = None
                text = ""
                ambiguity = ""
                if pdfs:
                    chosen = choose_pdf(pdfs)
                    if chosen and len(pdfs) > 1 and chosen != pdfs[0]:
                        ambiguity = f"Multiple PDFs found; chose {chosen.name}."
                    subject_src = chosen.name if chosen else pdfs[0].name
                    if chosen:
                        text = extract_pdf_text(chosen, log_fp)
                elif readmes:
                    # Choose the first lexicographically
                    subject_src = readmes[0].name
                    try:
                        text = readmes[0].read_text(errors="ignore")
                    except Exception as e:
                        log(f"Failed to read {readmes[0]}: {e}", log_fp)
                else:
                    subject_src = "<none>"
                    text = ""
                    ambiguity = "No PDF or README found; report uses heuristics only."

                generate_report(sem, proj, log_fp, subject_src, text, ambiguity)

        log(f"Processed {total_projects} project(s).", log_fp)
        log("Session completed.", log_fp)
        print(f"\nLog written to: {log_path}")


if __name__ == "__main__":
    main()

