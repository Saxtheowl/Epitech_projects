#!/usr/bin/env python3
import os
import re
import sys
import shutil
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
REPORTS_DIR = ROOT / "reports"
LOGS_DIR = ROOT / "logs"

def log_write(log_path: Path, text: str):
    log_path.parent.mkdir(parents=True, exist_ok=True)
    with log_path.open("a", encoding="utf-8") as f:
        f.write(text)

def find_docs(project_root: Path):
    candidates = []
    for p in project_root.rglob("*"):
        name_lower = p.name.lower()
        if p.is_file():
            if p.suffix.lower() == ".pdf":
                candidates.append(p)
            elif name_lower.startswith("readme") and p.suffix.lower() in (".md", ".txt", ""):
                candidates.append(p)
    return candidates

def choose_best_doc(files):
    pdfs = [f for f in files if f.suffix.lower() == ".pdf"]
    if pdfs:
        subject_pdfs = [f for f in pdfs if f.name.lower().startswith("subject")]
        pool = subject_pdfs if subject_pdfs else pdfs
        def score_name(f: Path):
            base = f.stem
            m = re.search(r"(.*?)(?:[-_]?\d+)?$", base)
            sans_num = (m.group(1) if m else base).lower()
            penalty = 1 if re.search(r"\d+$", base) else 0
            return (penalty, len(sans_num))
        chosen = sorted(pool, key=lambda f: (score_name(f), -f.stat().st_mtime))[:1]
        return chosen[0] if chosen else None
    readmes = [f for f in files if f.name.lower().startswith("readme")]
    if readmes:
        def ext_rank(p: Path):
            ext = p.suffix.lower()
            return {".md": 0, ".markdown": 1, ".txt": 2, "": 3}.get(ext, 9)
        return sorted(readmes, key=lambda f: (ext_rank(f), -f.stat().st_mtime))[0]
    return None

def extract_readme_summary(path: Path, max_lines=40):
    try:
        text = path.read_text(encoding="utf-8", errors="ignore")
    except Exception:
        return ""
    lines = [ln.rstrip() for ln in text.splitlines()]
    out = []
    for i, ln in enumerate(lines):
        out.append(ln)
        if len(out) >= max_lines:
            break
    return "\n".join(out)

def maybe_pdftotext(path: Path, max_chars=2000):
    exe = shutil.which("pdftotext")
    if not exe:
        return None
    txt_path = path.with_suffix(".txt.__tmp__")
    try:
        rc = os.system(f'"{exe}" -l 2 "{path}" "{txt_path}" > /dev/null 2>&1')
        if rc != 0 or not txt_path.exists():
            return None
        content = txt_path.read_text(encoding="utf-8", errors="ignore")
        try:
            txt_path.unlink()
        except Exception:
            pass
        return content[:max_chars]
    except Exception:
        return None

def generate_project_report(semester_dir: Path, project_dir: Path, log_path: Path):
    rel_project = project_dir.relative_to(ROOT)
    report_dir = REPORTS_DIR / semester_dir.name
    report_dir.mkdir(parents=True, exist_ok=True)
    report_path = report_dir / f"{project_dir.name}.md"

    subdirs = [d for d in project_dir.iterdir() if d.is_dir()]
    subdirs = [d for d in subdirs if not d.name.startswith('.')]

    lines = []
    lines.append(f"# {project_dir.name} — {semester_dir.name}\n")
    lines.append(f"Root: `{rel_project}`\n")
    lines.append("## Découverte\n")
    if not subdirs:
        lines.append("Aucun sous-projet détecté.\n")
    for sub in sorted(subdirs, key=lambda p: p.name.lower()):
        docs = find_docs(sub)
        chosen = choose_best_doc(docs)
        lines.append(f"### {sub.name}\n")
        if chosen is None:
            lines.append("- Source: Aucune doc trouvée\n")
        else:
            rel = chosen.relative_to(project_dir)
            lines.append(f"- Source: `{rel}`\n")
            if chosen.suffix.lower() == ".pdf":
                text = maybe_pdftotext(chosen)
                if text:
                    preview = "\n".join(["> " + ln for ln in text.splitlines()[:30]])
                    lines.append("- Aperçu (PDF):\n" + preview + "\n")
                else:
                    lines.append("- Aperçu (PDF): extraction indisponible\n")
            else:
                preview = extract_readme_summary(chosen, max_lines=25)
                if preview:
                    lines.append("- Aperçu (README):\n" + "\n".join("> " + ln for ln in preview.splitlines()) + "\n")
        lines.append("- Exigences (préliminaire):\n")
        lines.append("  - MUST: À préciser d'après le sujet\n")
        lines.append("  - SHOULD: Tests automatisés + Makefile\n")
        lines.append("  - OPTIONAL: Optimisations, bonus\n")
        lines.append("")

    lines.append("## Plan (générique)\n")
    lines.append("- Parsing/IO suivant le sujet\n")
    lines.append("- Cœur algorithmique minimal viable\n")
    lines.append("- Gestion d'erreurs conforme\n")
    lines.append("- Makefile et cible test\n")
    lines.append("- Cas d'essai reproductibles\n")
    lines.append("")

    lines.append("## Tests\n")
    lines.append("- Exécuter tous les tests détectés: `scripts/test_all.sh` (à la racine).\n")
    lines.append(f"- Tester uniquement ce projet: lancer manuellement les Makefile des sous-projets sous `{rel_project}`.\n")
    lines.append("")

    lines.append("## État d'implémentation\n")
    lines.append("- Scaffolding de tests: en cours de déploiement\n")
    lines.append("- Implémentations: à prioriser par simplicité\n")
    lines.append("")

    report_path.write_text("\n".join(lines), encoding="utf-8")
    log_write(log_path, f"[REPORT] Generated {report_path.relative_to(ROOT)}\n")

def main():
    ts = time.strftime("%Y%m%d-%H%M%S")
    log_path = LOGS_DIR / f"session-{ts}.log"
    log_write(log_path, f"Session started at {ts}\nROOT={ROOT}\n")

    semesters = [p for p in ROOT.iterdir() if p.is_dir() and p.name.startswith("Semester-")]
    for sem in sorted(semesters, key=lambda p: p.name):
        projects = [p for p in sem.iterdir() if p.is_dir() and not p.name.startswith('.')]
        for proj in sorted(projects, key=lambda p: p.name.lower()):
            try:
                generate_project_report(sem, proj, log_path)
            except Exception as e:
                log_write(log_path, f"[ERROR] {proj.relative_to(ROOT)}: {e}\n")

    log_write(log_path, "Session complete.\n")
    print(str(log_path))

if __name__ == "__main__":
    sys.exit(main())
