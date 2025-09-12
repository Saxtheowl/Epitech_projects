# BSQ (Biggest Square)

But: trouver et marquer le plus grand carré de '.' dans une carte (format Epitech: première ligne = nombre de lignes, puis carte avec '.' et 'o').

Build
- `make` construit le binaire `bsq`.
- `make clean | fclean | re` pour nettoyer/reconstruire.

Run
- `./bsq <map_file>` affiche la carte avec le plus grand carré marqué par des `x`.
- Retourne 84 si erreurs d’arguments/lecture/format.

Tests
- `make test` exécute `tests/test.sh` avec des cartes simples et vérifie la sortie.

Notes
- Implémentation par programmation dynamique en O(R*C) mémoire et temps.

