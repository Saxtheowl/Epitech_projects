# B-PSU-100 — Semester-1

Root: `Semester-1/B-PSU-100`

## Découverte

### My_ls

- Source: `My_ls/MyLs/my_ls.pdf`

- Aperçu (PDF): extraction indisponible

- Implémentation: binaire `my_ls` avec options `-a`, `-l`, `-R`, `-t`, tri par nom/mtime, format long (permissions, liens, user, group, taille, date), impression récursive avec en-têtes comme `ls -R`.
- Build/Tests: Makefile présent; `make test` exécute `tests/test.sh` (5 cas basiques) — OK.
- README: ajouté dans `Semester-1/B-PSU-100/My_ls/`.


### My_navy

- Source: `My_navy/My_navy/B-PSU-100_my_navy.pdf`

- Aperçu (PDF): extraction indisponible

- Exigences (préliminaire):

  - MUST: À préciser d'après le sujet

  - SHOULD: Tests automatisés + Makefile

  - OPTIONAL: Optimisations, bonus


### My_sokoban

- Source: `My_sokoban/My_sokoban/B-PSU-100_my_sokoban.pdf`

- Aperçu (PDF): extraction indisponible

- Exigences (préliminaire):

  - MUST: À préciser d'après le sujet

  - SHOULD: Tests automatisés + Makefile

  - OPTIONAL: Optimisations, bonus


### My_sudo

- Source: `My_sudo/My_sudo/B-PSU-100_my_sudo.pdf`

- Aperçu (PDF): extraction indisponible

- Exigences (préliminaire):

  - MUST: À préciser d'après le sujet

  - SHOULD: Tests automatisés + Makefile

  - OPTIONAL: Optimisations, bonus


### My_Top

- Source: `My_Top/My_Top/B-PSU-100_my_top.pdf`

- Aperçu (PDF): extraction indisponible

- Exigences (préliminaire):

  - MUST: À préciser d'après le sujet

  - SHOULD: Tests automatisés + Makefile

  - OPTIONAL: Optimisations, bonus


## Plan (générique)

- Parsing/IO suivant le sujet

- Cœur algorithmique minimal viable

- Gestion d'erreurs conforme

- Makefile et cible test

- Cas d'essai reproductibles


## Tests

- Exécuter tous les tests détectés: `scripts/test_all.sh` (à la racine).

- Tester uniquement ce projet: lancer manuellement les Makefile des sous-projets sous `Semester-1/B-PSU-100`.


## État d'implémentation

- Scaffolding de tests: en cours de déploiement

- Implémentations: à prioriser par simplicité
  - My_ls: implémenté et testé (5 cas). Reste à étoffer selon PDF complet si besoin (compat. options supplémentaires, formats particuliers).
