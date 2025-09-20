# EvalExpr (B-CPE-101)

## Objectif
Évaluer une expression arithmétique passée en argument (infixe, opérateurs `+ - * / %`, parenthèses, signes unaires) et afficher le résultat suivi d’un retour à la ligne. Les spécifications proviennent de `EvalExpr.pdf` et du bootstrap pédagogique associé.

## Contraintes du sujet
- `MUST` coder en C et livrer via un `Makefile` fournissant au minimum `all`, `clean`, `fclean`, `re`.
- `MUST` n’utiliser que `write`, `malloc`, `free` (les autres appels système/libC sont interdits).
- `MUST` fournir la fonction `int eval_expr(char const *str)` et utiliser le `main` imposé.
- `MUST` supporter les 5 opérateurs + gestion illimitée des parenthèses et des espaces.
- `SHOULD` structurer le parseur en descente récursive (nombres → facteurs → termes → expression) comme suggéré dans le bootstrap.
- `KNOWN LIMIT` le sujet garantit des entrées valides; le programme ne gère donc pas les erreurs syntaxiques ni les divisions par zéro.

## Build
- `make` compile le binaire `eval_expr`.
- `make clean` / `make fclean` suppriment les artefacts; `make re` reconstruit.

## Exécution
- `./eval_expr "(3+2)*5"` imprime `25`.
- Si l’arité est différente de 2 (`ac != 2`), le programme quitte avec le statut `84` sans sortie.

## Tests
- `make test` lance `tests/test.sh` (11 cas couvrant opérateurs, précédence, parenthèses imbriquées, espaces, chaînes de signes unaires et mélanges mod/div).

## Dépendances
- Outils: `gcc`, `make`, un interpréteur POSIX `sh` (pour `tests/test.sh`).
- Aucun package externe n’est requis; la compilation se limite à la libc par défaut.

## Notes d’implémentation
- Parseur en descente récursive: `parse_expression` (sommation) → `parse_term` (produits, divisions, modulo) → `parse_factor` (parenthèses, unaires) → `parse_number`.
- Affichage via `my_put_nbr` / `my_putchar` respectant la contrainte des appels système autorisés.
