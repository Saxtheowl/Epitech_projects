# Final Stumper (B-CPE-101)

## Subject recap
- **Binary**: `rush3` (`Final_Stumper`, p.1).
- **Goal**: lire la sortie d’un `rush1-x` et afficher la ou les variantes compatibles + dimensions (`Final_Stumper`, p.1).
- **Output**: `[rush1-n] w h` pour chaque correspondance, séparées par ` || `; sinon `none`. Toujours terminer par `\n` (`Final_Stumper`, p.1).
- **Constraints**: seules les syscalls `read`, `write`, `malloc`, `free` sont autorisées (p.1). Les erreurs doivent passer par `stderr` avec code `84`; succès → `0` (p.1).

## Implementation
- `main` lit jusqu’à `BUFF_SIZE` (4096) octets depuis stdin, termine la chaîne et renvoie `84` en cas d’erreur `read` (conformément au sujet).
- `rush3` calcule largeur/hauteur, vérifie l’uniformité des lignes et rejette les entrées vides/malfaites → affiche `none`.
- Comparaison via générateurs internes `rush_1_x_char` reproduisant fidèlement les bords/cas ambigus (`width == 1` ou `height == 1`).
- Affichage en flux (`write` exclusivement) au format attendu, accumulation des variantes multiples avec séparateur ` || `.

## Tests
- `make test` / `./scripts/test.sh`:
  - Extrait les binaires officiels `rush1-x` fournis dans `rush1_bins.tgz`.
  - Vérifie les exemples du sujet (4×4, ambigu 1×1) + cas supplémentaires (`5×1`, motif invalide → `none`).
  - Nettoyage auto du répertoire temporaire via `trap`.
- Dernière exécution: `Passed: 6  Failed: 0`.

## Checklist
- [x] Detects all five rush patterns with correct formatting.
- [x] Handles ambiguous outputs by listing all matching variants.
- [x] Validates and normalises input dimensions.
- [x] Respects syscall constraints (`read`, `write`, `malloc`, `free`).
- [x] Automated regression suite documented.

## Risks / follow-up
- Current buffer size (4096) matches subject hint but could be extended to handle
  bigger inputs if needed (basic loop already stops when the buffer fills).
- Input validation assumes printable ASCII; further checks could enforce this if
  desired.
