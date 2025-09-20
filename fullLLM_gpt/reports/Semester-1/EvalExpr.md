# EvalExpr — B-CPE-101 (Semester-1)

## Sujet & références
- **Source principale**: `EvalExpr.pdf` (pages 1–2) — définition de la fonction, contraintes, exemple d’exécution.
- **Complément pédagogique**: `EvalExprBootstrap.pdf` (pages 1–4) — rappel sur le parsing en descente récursive et découpage nombre/facteur/terme.

## Objectifs retenus
Comprendre et implémenter un parseur en descente récursive capable d’évaluer une expression arithmétique valide en notation infixe et de renvoyer un entier via la fonction `int eval_expr(char const *str)`.

## Exigences du sujet
- [MUST] Compiler en C et livrer un `Makefile` avec cibles `all`, `clean`, `fclean`, `re` (`EvalExpr.pdf`, p.1).
- [MUST] Restreindre les appels système à `write`, `malloc`, `free` (`EvalExpr.pdf`, p.1).
- [MUST] Fournir la fonction `eval_expr` et utiliser le `main` imposé (`EvalExpr.pdf`, p.1).
- [MUST] Gérer les opérateurs `+ - * / %`, la précédence (+/− < */% < parenthèses) et les parenthèses imbriquées (`EvalExpr.pdf`, p.1).
- [MUST] Supporter des espaces arbitraires dans l’expression (implicite dans l’exemple p.2 et rappel bootstrap p.4).
- [SHOULD] Structurer l’analyse selon le modèle nombre → facteurs → expressions (bootstrap p.1–3).
- [SHOULD] Permettre les signes unaires répétés avant un facteur (bootstrap p.4 suggère gestion des signes avant parenthèse/nombre).
- [KNOWN LIMIT] Le sujet garantit des expressions valides; aucune détection d’erreur n’est requise (`EvalExpr.pdf`, p.1).

## Approche retenue
1. **Parsing**: implémentation d’un parseur LL(1) récursif composé de `parse_expression`, `parse_term`, `parse_factor`, `parse_number` (conformément au bootstrap).
2. **Gestion des espaces**: normalisation via `skip_spaces` pour accepter les espaces/retours.
3. **Signes unaires**: accumulation d’un signe avant chaque facteur (permet `--+10`).
4. **IO minimalistes**: `my_putchar` et `my_put_nbr` pour respecter la contrainte d’appels système.
5. **Tests**: script automatisé rejouant l’exemple officiel (p.2) et couvrant parenthèses, précédence, divisions, modulo, chaînes de signes et espaces extrêmes.

## État d’implémentation
- `main.c`: reprend le `main` imposé (retourne 84 si `ac != 2`).
- `src/eval_expr.c`: descente récursive complète, avec gestion des espaces et des signes unaires.
- `src/io.c`: sorties standard via `write` uniquement.
- `include/eval_expr.h`: expose `eval_expr`, `my_putchar`, `my_put_nbr`.
- `Makefile`: cibles `all`, `clean`, `fclean`, `re`, `test`, compilation stricte `-std=c99 -Wall -Wextra -Werror`.

## Plan d’implémentation suivi
1. Lecture du sujet + bootstrap, identification des niveaux de grammaire.
2. Implémentation du parseur (nombre → facteur → terme → expression) avec propagation de pointeur.
3. Ajout des helpers IO compatibles (pas de printf).
4. Script de tests `tests/test.sh` pour automatiser l’exemple et des cas limites.
5. Intégration du script au `Makefile` via la cible `test`.

## Jeu de tests
- Lancer `make test` depuis le répertoire projet.
- Le script compile, exécute `eval_expr` sur 11 cas:
  - `(3+2)*5` — exemple officiel.
  - Opérations simples (`2+2`, `10-3-2`), divisions en chaîne (`18/3/3`).
  - Mélange modulo/produit (`5*3%4`).
  - Parenthèses imbriquées et espaces (`40 + (2*5) - 7`, `  12 * ( -3 + 5 )`).
  - Signes unaires multiples (`-3+10`, `-(2-5)`, `--++10`).
  - Profondeur d’imbrication (`(1+(2*(3+(4*(5-6)))))`).
- En sortie: récapitulatif `[OK]/[KO]`, total pass/fail, statut de retour non nul en cas d’échec.

## Checklist d’évaluation
- [x] Fonction `eval_expr` conforme et exposée dans `include/eval_expr.h`.
- [x] `main` imposé repris à l’identique.
- [x] Respect des appels système autorisés uniquement.
- [x] Gestion de la précédence + parenthèses + signes unaires.
- [x] `Makefile` conforme + cible `test`.
- [x] Tests automatisés incluant l’exemple du sujet.

## Risques / limites
- Pas de détection d’erreur sur expressions invalides (non demandé).
- Résultats intermédiaires calculés en `long long`, conversion finale `int` — des dépassements peuvent survenir si l’expression déborde le domaine 32 bits.
- Aucun test de performance; complexité proportionnelle à la taille de l’expression.

## Actions futures possibles
- Étendre la batterie de tests (e.g. combinaisons plus longues, grands nombres, modulo négatif).
- Ajouter un mode debug pour tracer le parsing lors d’investigations.

