# B-SHL-300 — BDSH (Shell JSON DB)

Root: `Semester-3/B-SHL-300`

## Découverte

- Source: `BDSH/B-SHL-300_BDSH.txt` (Version 3.0)
- Sujet: Écrire un script `/bin/sh` gérant une base de données au format JSON dans un fichier. Le script supporte la création de base et de tables, l'insertion, la mise à jour (bonus), la suppression (bonus), la sélection avec projections, filtre `where`, tri `orderby`, jointure simple, et option `-j` pour sortie JSON.
- Emplacement du fichier DB (priorité): `-f FILE`, sinon variable d'environnement `BDSH_File`, sinon configuration `.bdshrc`.
- Interface: `./bdsh [OPTION]... [COMMAND] [REQUEST]`
- Options: `-h|--help`, `-f|--file=FILE`, `-j` (sortie JSON pour `select`).
- Commandes: `create database`, `create table <name> <col1,col2,...>`, `insert <table> k=v,k=v`, `update` (bonus), `select`, `delete` (bonus).
- Contraintes: Shell POSIX `/bin/sh`, erreurs sur `stderr`, code retour 1 en cas d'erreur. Binaires autorisés: `[`, `test`, `expr`, `wc`, `head`, `tail`, `cat`, `sort`, `grep`, `sed`, `rm`, `cut`, `ps`, `tr`, `touch`, `mkdir`, `find`.

## Exigences

- MUST: Script `bdsh` en `/bin/sh` respectant l'interface, création DB/table, insertion, sélection avec `where`, `orderby`, jointure simple à 2 tables, formatage tableau et option `-j`.
- SHOULD: Makefile avec cibles `all`, `test`, `clean`; tests reproductibles couvrant les exemples du sujet et cas limites; validation de paramètres; robustesse I/O; lecture `.bdshrc` et `BDSH_File`.
- OPTIONAL: `update` et `delete` (bonus non testés automatiquement), gestion d'échappement avancée, validations de schéma.

## Plan

- Parsing CLI: `-f/--file`, `-j`, `-h`; résolution du fichier DB (arg/env/rc).
- Format DB: JSON pretty-print: `{ "schemas": {..}, "tables": { <table>: [\n  {...},\n] } }` (1 objet par ligne).
- create: `database` (squelette), `table` (schéma + tableau vide).
- insert: parse `k=v,...`, sérialise en objet JSON, append dans l'array de la table.
- select: projection colonnes, `where k=v` (égalité), `orderby col` (tri ASCII), `join <key>` entre 2 tables `t1,t2`.
- Sorties: tableau aligné (largeurs calculées) ou JSON (`-j`).
- Tests: script `tests/test.sh` + `make test`, couvre exemples et limites.

## Tests (exécution)

- `make test` à la racine du projet `Semester-3/B-SHL-300` exécute les cas principaux et affiche un récapitulatif.

## État d'implémentation

- Script `bdsh`: ajouté (create/insert/select/where/orderby/join, `-j`).
- Makefile: ajouté (`test` inclus).
- Tests: ajoutés sous `tests/` (exemples du sujet + cas limites de base).
