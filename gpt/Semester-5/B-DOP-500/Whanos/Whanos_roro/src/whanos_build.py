#!/usr/bin/env python3
#
# EPITECH PROJECT, 2025
# Whanos_roro
# File description:
#   Build helper for Whanos-compatible repositories
#

import json
import os
import shutil
import subprocess
import sys
from typing import Dict, Tuple


HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.abspath(os.path.join(HERE, os.pardir))


def have(cmd: str) -> bool:
    return shutil.which(cmd) is not None


def detect(repo: str) -> Dict:
    proc = subprocess.run(
        [sys.executable,
         os.path.join(HERE, 'whanos_detect.py'), repo],
        check=True, capture_output=True, text=True)
    return json.loads(proc.stdout)


def pick_dockerfiles(lang: str) -> Tuple[str, str]:
    base = os.path.join(ROOT, 'images', lang.lower(), 'Dockerfile.base')
    standalone = os.path.join(
        ROOT, 'images', lang.lower(), 'Dockerfile.standalone')
    return base, standalone


def wants_base(repo: str, lang: str) -> bool:
    # If the repo has a Dockerfile at root that starts with FROM whanos-<lang>
    df = os.path.join(repo, 'Dockerfile')
    if not os.path.isfile(df):
        return False
    try:
        with open(df, 'r') as f:
            first = f.read(2000)
        return f"FROM whanos-{lang.lower()}" in first
    except Exception:
        return True


def build(repo: str, tag: str = 'app:latest', push: bool = False) -> int:
    info = detect(repo)
    lang = info.get('language')
    if lang in (None, 'Unknown', 'Ambiguous'):
        print(f"Error: cannot determine language ({info.get('reason')})",
              file=sys.stderr)
        return 84
    base_df, standalone_df = pick_dockerfiles(lang)
    if wants_base(repo, lang):
        # Build the base image first
        base_tag = f"whanos-{lang.lower()}"
        cmd1 = ['docker', 'build', '-f', base_df, '-t', base_tag, ROOT]
        cmd2 = ['docker', 'build', repo, '-t', tag]
        print(' '.join(cmd1))
        print(' '.join(cmd2))
        if have('docker'):
            if subprocess.call(cmd1) != 0:
                return 84
            rc = subprocess.call(cmd2)
            if rc == 0 and push:
                subprocess.call(['docker', 'push', tag])
            return rc
        return 0
    else:
        # Standalone build using our Dockerfile
        cmd = ['docker', 'build', '-f', standalone_df, repo, '-t', tag]
        print(' '.join(cmd))
        if have('docker'):
            rc = subprocess.call(cmd)
            if rc == 0 and push:
                subprocess.call(['docker', 'push', tag])
            return rc
        return 0


def main(argv):
    if len(argv) < 2 or len(argv) > 4:
        print('Usage: whanos_build.py <repo_root> [tag] [--push]', file=sys.stderr)
        return 84
    repo = os.path.abspath(argv[1])
    tag = 'app:latest'
    push = False
    for a in argv[2:]:
        if a == '--push':
            push = True
        else:
            tag = a
    if not os.path.isdir(repo):
        print('Error: repo_root is not a directory', file=sys.stderr)
        return 84
    return build(repo, tag, push)


if __name__ == '__main__':
    sys.exit(main(sys.argv))
