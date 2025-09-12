# EvalExpr (B-CPE-101)

Évalue une expression arithmétique donnée en argument et affiche le résultat.

Référence: EvalExpr.pdf / EvalExprBootstrap.pdf.

Build
- `make` construit le binaire `eval_expr`.
- `make clean | fclean | re` pour nettoyer/reconstruire.

Run
- `./eval_expr "(3+2)*5"` → `25`.
- Si le nombre d’arguments est différent de 1, le programme retourne 84.

Tests
- `make test` exécute `tests/test.sh` (8 cas basiques dont parenthèses, priorités, mod/div, unaires).

Notes
- Respecte la contrainte: seules `write`, `malloc`, `free` sont utilisées (et fonctions internes).
- Parser récursif: factor (nombre ou parenthèses avec prise en charge de +/− unaires) → term (*,/,% ) → expr (+,−).
