# InfinAdd (B-CPE-101)

Addition et soustraction de grands entiers représentés sous forme de chaînes.

## Build

```sh
make
```

Binaire produit : `infin_add`. Les cibles `clean`, `fclean`, `re`, `test` sont disponibles.

## Usage

```sh
./infin_add "-876435" "987143265"
# -> 986266830
```

- Les deux paramètres sont des entiers signés (avec éventuels espaces/`+`/`-` multiples).
- Résultat affiché sans zéros superflus, précédé d’un unique `-` si négatif.
- Retourne `84` si le nombre d’arguments est incorrect ou en cas d’allocation échouée.

## Implémentation

- Analyse des signes puis addition/soustraction des valeurs absolues selon les règles des entiers relatifs.
- Les valeurs sont stockées sous forme de chaînes décimales (little-endian pour les calculs).
- Opérations élémentaires : `add_abs`, `sub_abs`, `compare_abs`, normalisation des zéros.
- Aucune fonction de la libC n’est utilisée en dehors de `write`, `malloc`, `free`.

## Tests

```sh
make test          # compile + exécute tests/tests.sh
./scripts/test.sh  # wrapper pratique
```

Le jeu de tests couvre :
- Sommes positives avec retenues.
- Nombres négatifs et combinaisons signe/opposé.
- Cas limite `0` et grands entiers (plusieurs dizaines de chiffres).
