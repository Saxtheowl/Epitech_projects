# My_ls — B-PSU-100 (Semester-1)

## Sujet & contraintes
- Source: `MyLs/my_ls.pdf` (rappel). Objectif: reproduire un sous-ensemble de `ls` en C.
- Options requises: `-a`, `-l`, `-R`, `-t` (+ combinaison avec arguments multiples).
- Gestion des erreurs: signaler sur `stderr` (`my_ls: path: strerror`) et continuer le traitement des autres chemins.
- Utilisation des appels POSIX standards (`opendir`, `readdir`, `lstat`, etc.). Aucun main fourni par le sujet → programme autonome.

## Implémentation
- `src/main.c` : parsing des options, séparation options/chemins, délégation à `list_paths`.
- `src/ls.c` :
  - `stat_entry` duplique proprement nom + chemin, appelle `lstat`; nettoyage intégré en cas d’erreur.
  - `list_directory` agrège les entrées (filtre `-a`, total `-l`, récursivité `-R`), avec realloc sécurisé et libération systématique via `free_entries`.
  - `list_paths` sépare fichiers/répertoires, stockés dans deux tableaux dynamiques; nouvelles vérifications d’allocation (`strdup`, `realloc`).
- `src/print.c` : format long (`-l`) complet (permissions, nlink, owner, group, taille, date formatée).
- `src/sort.c` : tri lexicographique par défaut, tri par mtime décroissant si `-t` (tie-break par nom).

## Tests
- `make test` exécute `tests/test.sh` qui construit un sandbox (`tests/tmp`) et compare la sortie de `my_ls` sur 5 cas :
  1. listing simple
  2. `-a` (fichiers cachés)
  3. `-t` (ordre mtime)
  4. `-R` (entêtes de répertoires)
  5. `-l` (format long).
- La suite a été relancée après les correctifs mémoire (`make fclean && make test` → « Passed: 5 Failed: 0 »).

## Points d’attention / suivis
- L’implémentation gère désormais toutes les erreurs d’allocation (`malloc`/`realloc`/`strdup`) sans fuites.
- Les sorties sont alignées sur `ls` pour les cas pris en charge. D’autres options (`-r`, `-1`, etc.) ne sont pas implémentées (conforme au périmètre sujet).
- Pour un audit futur : enrichir les tests (`-l` + liens symboliques, grands répertoires) et vérifier l’affichage des liens symboliques (`readlink`) si exigé par une variante du sujet.

## Comment tester
```sh
cd Semester-1/B-PSU-100/My_ls
make fclean
make
./my_ls -alRt path ...
make test
```

Résultat attendu : suite de tests OK sans fuites ni crash.
