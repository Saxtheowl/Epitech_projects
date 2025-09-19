# BSQ

- Semester: Semester-1
- UE: B-CPE-110
- Subject source: `README.md`

## Summary
# BSQ (Biggest Square) But: trouver et marquer le plus grand carré de '.' dans une carte (format Epitech: première ligne = nombre de lignes, puis carte avec '.' et 'o'). Build - `make` construit le binaire `bsq`. - `make clean | fclean | re` pour nettoyer/reconstruire. Run - `./bsq <map_file>` affiche la carte avec le plus grand carré marqué par des `x`. - Retourne 84 si erreurs d’arguments/lecture/format. Tests - `make test` exécute `tests/test.sh` avec des cartes simples et vérifie la sortie. Notes - Implémentation par programmation dynamique en O(R*C) mémoire et temps.

## Requirements (heuristic)
- [MUST] Implement per subject. (Details not auto-extracted)

## Plan (initial)
- Parsing/IO setup
- Core logic
- Error handling
- Tests from examples + edge cases

## Implementation Status
- Language: C
- Makefile: yes
- Tests present: yes

## How To Test
- Build: `make` (if available)
- Run tests: `make test` (stub added when missing)

## Risks / Gaps
- Auto-extracted summary may miss constraints.
- Manual review recommended before final submission.