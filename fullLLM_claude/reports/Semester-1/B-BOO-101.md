# Rapport de Projet : Semester-1 / B-BOO-101 - Bootcamp Phoenix

## Vue d'ensemble
- **Semestre** : 1
- **Projet** : B-BOO-101 - Bootcamp Phoenix
- **Type** : Bootcamp de remédiation (5 jours)
- **Langage** : C
- **Crédits** : 0

## Description du module
Bootcamp de remédiation pour les étudiants ayant des lacunes en programmation C de base. Objectif : reprendre les fondamentaux et reconstruire des bases solides.

## Analyse des jours

### Day01 : Welcome back ✅ TERMINÉ
- **PDF** : `Semester-1/B-BOO-101/Bootcamp_Phoenix/Day01/day01.pdf`
- **Status** : Implémenté et testé avec succès

#### Tâches implémentées (6 tâches) :
1. **TASK 01 - show_alphabet** ✅
   - Fonction : `int show_alphabet(void);`
   - Affiche l'alphabet en minuscules (a-z)
   - Implémentation : `show_alphabet.c`

2. **TASK 02 - show_combinations** ✅
   - Fonction : `int show_combinations(void);`
   - Affiche toutes les combinaisons de 3 chiffres différents (012, 013, ..., 789)
   - Implémentation : `show_combinations.c`

3. **TASK 03 - show_number** ✅
   - Fonction : `int show_number(int nb);`
   - Affiche un nombre entier (gère tous les valeurs d'int)
   - Implémentation : `show_number.c`

4. **TASK 04 - show_string** ✅
   - Fonction : `int show_string(char const *str);`
   - Affiche une chaîne de caractères
   - Implémentation : `show_string.c`

5. **TASK 05 - reverse_string** ✅
   - Fonction : `char *reverse_string(char *str);`
   - Inverse une chaîne de caractères sur place
   - Implémentation : `reverse_string.c`

6. **TASK 06 - to_number** ✅
   - Fonction : `int to_number(char const *str);`
   - Convertit une chaîne en nombre (gère les cas complexes)
   - Implémentation : `to_number.c`

#### Contraintes techniques respectées :
- ✅ Utilisation uniquement de `my_putchar` pour l'affichage
- ✅ Compilation avec `gcc *.c`
- ✅ Gestion des erreurs (exit code 84)
- ✅ Pas de push du main ni de my_putchar

### Day02 : Recursive and strings ✅ TERMINÉ
- **PDF** : `Semester-1/B-BOO-101/Bootcamp_Phoenix/Day02/day02.pdf`
- **Status** : Implémenté, testé et tests unitaires Criterion ajoutés

#### Tâches implémentées (8 tâches + tests) :
1. **TASK 01 - iterative_factorial** ✅
   - Fonction : `int iterative_factorial(int nb);`
   - Calcule la factorielle de façon itérative
   - Gestion : 0! = 1, si n < 0 alors n! = 0

2. **TASK 02 - recursive_power** ✅
   - Fonction : `int recursive_power(int nb, int p);`
   - Calcule nb^p de façon récursive
   - Gestion : n^0 = 1, si p < 0 alors n^p = 0

3. **TASK 03 - is_prime_number** ✅
   - Fonction : `int is_prime_number(int nb);`
   - Retourne 1 si le nombre est premier, 0 sinon
   - Gestion : 0 et 1 ne sont pas premiers

4. **TASK 04 - my_strcpy** ✅
   - Fonction : `char *my_strcpy(char *dest, char const *src);`
   - Copie une chaîne dans une autre
   - Reproduction du comportement de strcpy

5. **TASK 05 - my_strncmp** ✅
   - Fonction : `int my_strncmp(char const *s1, char const *s2, int n);`
   - Compare n caractères de deux chaînes
   - Reproduction du comportement de strncmp

6. **TASK 06 - my_strstr** ✅
   - Fonction : `char *my_strstr(char *str, char const *to_find);`
   - Trouve une sous-chaîne dans une chaîne
   - Reproduction du comportement de strstr

7. **TASK 07 - my_strupcase** ✅
   - Fonction : `char *my_strupcase(char *str);`
   - Met toutes les lettres en majuscules

8. **TASK 08 - my_strcapitalize** ✅
   - Fonction : `char *my_strcapitalize(char *str);`
   - Met en majuscule la première lettre de chaque mot

9. **TASK 09 - Unit Tests** ✅
   - Tests Criterion pour `my_strcpy` et `my_strncmp`
   - Couverture : 60% lignes, 40% branches minimum
   - Fichiers : `tests/test_my_strcpy.c`, `tests/test_my_strncmp.c`

### Tests automatisés
- **Framework** : Tests custom avec `test_program`
- **Build** : `make test`
- **Status** : ✅ Tous les tests passent
- **Couverture** : Toutes les fonctions testées avec cas limites

## Architecture technique

### Structure de build :
```
Day01/
├── Makefile          # Build system
├── *.c              # 6 fichiers sources des tâches
├── tests/
│   ├── test_main.c   # Programme de test
│   └── my_putchar.c  # Fonction d'affichage
└── *.o              # Objets compilés
```

### Compilation :
- Flags : `-Wall -Wextra -Werror`
- Targets : `all`, `clean`, `fclean`, `re`, `test`

### Day03 : Phoenix library and arguments ✅ TERMINÉ
- **PDF** : `Semester-1/B-BOO-101/Bootcamp_Phoenix/Day03/day03.pdf`
- **Status** : Implémenté et testé avec succès

#### Tâches implémentées (5 tâches) :
1. **TASK 01 - libphoenix.a** ✅
   - Bibliothèque statique contenant toutes les fonctions des jours précédents
   - Structure : `lib/phoenix/Makefile` et fichiers sources
   - Fonctions : my_putchar, show_number, show_string, reverse_string, etc.

2. **TASK 02 - phoenix.h** ✅
   - Header contenant tous les prototypes de la libphoenix
   - Localisation : `includes/phoenix.h`

3. **TASK 03 - concat_strings** ✅
   - Fonction : `char *concat_strings(char *dest, char const *src);`
   - Concatène deux chaînes (similaire à strcat)

4. **TASK 04 - show_params** ✅
   - Programme : `task04/show_params`
   - Affiche tous les arguments de la ligne de commande
   - Build : Makefile utilisant libphoenix

5. **TASK 05 - sorted_params** ✅
   - Programme : `task05/sorted_params`
   - Affiche les arguments triés par ordre ASCII
   - Build : Makefile utilisant libphoenix

### Day04 : Memory, re-parameters and structures ✅ TERMINÉ
- **PDF** : `Semester-1/B-BOO-101/Bootcamp_Phoenix/Day04/day04.pdf`
- **Status** : Implémenté et testé avec malloc/free

#### Tâches implémentées (6 tâches) :
1. **TASK 01 - duplicate_string** ✅
   - Fonction : `char *duplicate_string(char const *src);`
   - Alloue et copie une chaîne (similaire à strdup)

2. **TASK 02 - concat_parameters** ✅
   - Programme : `task02/concat_parameters`
   - Concatène tous les arguments séparés par \n

3. **TASK 03 - split_string** ✅
   - Fonction : `char **split_string(char const *str);`
   - Découpe une chaîne en mots (séparateurs non-alphanumériques)

4. **TASK 04 - show_string_array** ✅
   - Fonction : `int show_string_array(char * const *array);`
   - Affiche un tableau de chaînes

5. **TASK 05 - parameters_to_array** ✅
   - Fonction : `struct info_param *parameters_to_array(int ac, char **av);`
   - Stocke les paramètres dans un tableau de structures

6. **TASK 06 - show_parameters_array** ✅
   - Fonction : `int show_parameters_array(struct info_param const *par);`
   - Affiche le contenu du tableau de structures

### Day05 : The Starry Day ✅ TERMINÉ
- **PDF** : `Semester-1/B-BOO-101/Bootcamp_Phoenix/Day05/day05.pdf`
- **Status** : Mini-projet terminé et testé

#### Projet implémenté :
1. **Programme star** ✅
   - Binaire : `star`
   - Dessine des étoiles de tailles variables
   - Gestion d'erreurs : Usage, taille invalide
   - Tests : Différentes tailles (0, 1, 2, 5)
   - Architecture modulaire avec fonctions spécialisées
   - Build : Makefile complet (all, clean, fclean, re)

## Status final du B-BOO-101
- **Jours terminés** : 5/5 ✅
- [x] Day01 : Welcome back (6 tâches)
- [x] Day02 : Recursive and strings (8 tâches + tests unitaires)
- [x] Day03 : Phoenix library and arguments (5 tâches)
- [x] Day04 : Memory, re-parameters and structures (6 tâches)
- [x] Day05 : The Starry Day (mini-projet)

## Évaluation globale
- **Conformité** : ✅ Respecte toutes les contraintes Epitech
- **Qualité** : ✅ Code propre avec gestion d'erreurs
- **Tests** : ✅ Tests complets avec cas limites
- **Documentation** : ✅ README et Makefile clairs

## Notes
Le Day01 est entièrement fonctionnel et constitue une excellente base pour les exercices de remédiation. Toutes les fonctions de base (affichage, manipulation de chaînes, conversion) sont correctement implémentées.