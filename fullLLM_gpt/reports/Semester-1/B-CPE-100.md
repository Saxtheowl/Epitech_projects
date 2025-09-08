# B-CPE-100 — Semester-1

Root: `Semester-1/B-CPE-100`

## Découverte

### Count_island

- Source: `Count_island/CountIsland.pdf`

- Aperçu (PDF): extraction indisponible

- Exigences (préliminaire):

  - MUST: À préciser d'après le sujet

  - SHOULD: Tests automatisés + Makefile

  - OPTIONAL: Optimisations, bonus


### Firtree

- Source: `Firtree/Tree.pdf`

- Aperçu (PDF): extraction indisponible

- Exigences (préliminaire):

  - MUST: Binaire `firtree` imprimant un sapin de taille N, gestion d'erreurs

  - SHOULD: Tests automatisés + Makefile

  - OPTIONAL: Optimisations, bonus


### MatchNmatch

- Source: `MatchNmatch/MatchNmatch.pdf`

- Aperçu (PDF): extraction indisponible

- Exigences (préliminaire):

  - MUST: À préciser d'après le sujet

  - SHOULD: Tests automatisés + Makefile

  - OPTIONAL: Optimisations, bonus


### Pool

- Source: `Pool/Day01/manifesto.pdf`

- Aperçu (PDF): extraction indisponible

- Exigences (préliminaire):

  - MUST: À préciser d'après le sujet

  - SHOULD: Tests automatisés + Makefile

  - OPTIONAL: Optimisations, bonus


### Rushs

- Source: `Rushs/Rush2/Rush2.pdf`

- Aperçu (PDF): extraction indisponible

- Exigences (préliminaire):

  - MUST: À préciser d'après le sujet

  - SHOULD: Tests automatisés + Makefile

  - OPTIONAL: Optimisations, bonus


### Star

- Source: `Star/B-CPE-100_Star.pdf`

- Aperçu (PDF): extraction indisponible

- Exigences (préliminaire):

  - MUST: À préciser d'après le sujet

  - SHOULD: Tests automatisés + Makefile

  - OPTIONAL: Optimisations, bonus


### WorkshopLib

- Source: `WorkshopLib/WorkshopLib.pdf`

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

- Tester uniquement ce projet: lancer manuellement les Makefile des sous-projets sous `Semester-1/B-CPE-100`.


## État d'implémentation

- Scaffolding de tests: en place (scripts/test_all.sh)

- Implémentations:
  - Star: implémenté en C avec Makefile et tests (sizes 1,2,4,5 + erreur 0) — OK
  - Firtree: implémenté en C avec Makefile + tests (comparaison à l'oracle `firtree.tgz` pour tailles 1..5 + erreur 0) — OK
  - Autres sous-projets: à faire
