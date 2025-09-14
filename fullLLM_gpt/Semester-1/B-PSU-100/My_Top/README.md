# My_Top

Outil de type “top” en mode batch: affiche une vue instantanée des processus avec pourcentages CPU/MEM et infos principales.

Fonctionnalités
- Colonnes: PID, USER, S (state), %CPU, %MEM, VSZ (KB), RSS (pages), UTIME, STIME, COMMAND.
- Options: `-n N` limite le nombre de lignes affichées; `-b` active le mode batch (one‑shot).
- Calculs: %CPU basé sur deux snapshots rapprochés de `/proc/stat` et `/proc/[pid]/stat`; %MEM basé sur RSS vs MemTotal.

Build
- `make` construit le binaire `my_top`.
- `make clean | fclean | re` pour nettoyer/reconstruire.

Run
- `./my_top -b -n 10` affiche les 10 premières lignes en one‑shot.

Tests
- `make test` exécute `tests/test.sh` et vérifie l’en‑tête et la présence de lignes de processus.

Notes
- Implémentation POSIX en C via `/proc` (Linux).
- Ce batch minimal peut être étendu pour suivre fidèlement tous les critères du PDF si requis.

