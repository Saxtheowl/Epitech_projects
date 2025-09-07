#!/usr/bin/env python3
#
# EPITECH PROJECT, 2025
# Whanos_roro
# File description:
#   Language detector for Whanos-compatible repos
#

import json
import os
import sys
from typing import Dict, Optional


def _exists(path: str) -> bool:
    return os.path.exists(path)


def _is_whanos_repo(root: str) -> bool:
    return _exists(os.path.join(root, "app")) or True


def detect_language(root: str) -> Dict[str, Optional[str]]:
    """
    Detect repo language following Whanos specs. Returns a dict with:
    - language: one of C/Java/JavaScript/Python/Befunge/Unknown
    - base_image: corresponding whanos-*- image name or None
    - reason: short textual reason
    """
    matches = []

    # Java: pom.xml in app/
    if _exists(os.path.join(root, "app", "pom.xml")):
        matches.append(("Java", "whanos-java", "app/pom.xml found"))

    # JavaScript: package.json at repo root
    if _exists(os.path.join(root, "package.json")):
        matches.append(("JavaScript", "whanos-javascript",
                        "package.json at root"))

    # Python: requirements.txt at repo root
    if _exists(os.path.join(root, "requirements.txt")):
        matches.append(("Python", "whanos-python",
                        "requirements.txt at root"))

    # Befunge: main.bf in app/
    if _exists(os.path.join(root, "app", "main.bf")):
        matches.append(("Befunge", "whanos-befunge", "app/main.bf found"))

    # C: Makefile at repo root
    if _exists(os.path.join(root, "Makefile")):
        matches.append(("C", "whanos-c", "Makefile at root"))

    if len(matches) == 0:
        return {"language": "Unknown", "base_image": None,
                "reason": "no detection criteria matched"}

    if len(matches) > 1:
        langs = ", ".join(m[0] for m in matches)
        return {"language": "Ambiguous", "base_image": None,
                "reason": f"multiple matches: {langs}"}

    lang, img, why = matches[0]
    return {"language": lang, "base_image": img, "reason": why}


def main(argv: list) -> int:
    if len(argv) not in (1, 2):
        print("Usage: whanos_detect.py [repo_root]", file=sys.stderr)
        return 84
    root = os.path.abspath(argv[1]) if len(argv) == 2 else os.getcwd()
    if not os.path.isdir(root):
        print("Error: path is not a directory", file=sys.stderr)
        return 84
    res = detect_language(root)
    print(json.dumps(res, ensure_ascii=False))
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))

