# My_ls

Clone simplifié de `ls` avec support des options de base.

Options
- `-a`: inclut les fichiers cachés.
- `-l`: affichage long (droits, liens, user, group, taille, date, nom). Affiche aussi `total` (somme des blocs/2) pour un répertoire.
- `-R`: parcours récursif des sous-répertoires avec en-têtes `path:`.
- `-t`: tri par date de modification (descendant).

Build
- `make` construit le binaire `my_ls`.
- `make clean | fclean | re` pour nettoyer/reconstruire.

Run
- `./my_ls [options] [fichiers|répertoires ...]`

Tests
- `make test` exécute `tests/test.sh` (5 cas basiques: listing, -a, -t, -R, -l).

Notes
- Implémenté en C POSIX. Les sorties sont compatibles avec `ls` pour les cas couverts par les tests.

