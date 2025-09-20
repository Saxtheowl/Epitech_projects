# Final Stumper (B-CPE-101)

Analyse la sortie d’un "rush1-x" (ASCII rectangle) et indique quelle(s) variante(s)
correspond, ainsi que les dimensions.

## Build

```sh
make
```

Génère `rush3`. Cibles habituelles : `clean`, `fclean`, `re`, `test`.

## Usage

```sh
./rush1-1 4 4 | ./rush3
# [rush1-1] 4 4
```

- L’entrée standard doit contenir l’intégralité du motif (chaque ligne terminée par
  `\n`).
- En cas d’aucune correspondance, le programme affiche `none` suivi d’un retour
  chariot.
- Plusieurs variantes peuvent produire le même motif (ex. dimensions 1×1 ou 5×1) :
  elles sont listées et séparées par ` || `.

## Implémentation

- Lecture via buffer statique (voir `main.c` fourni) puis calcul de la largeur/hauteur
  en validant l’uniformité des lignes.
- Comparaison avec les cinq générateurs `rush1-1` à `rush1-5` implémentés sous forme
  de fonctions retournant le caractère attendu à chaque position.
- Résultats imprimés à la volée (`write` uniquement), sans allocations inutiles.

## Tests

```sh
make test          # exécute tests/test.sh
./scripts/test.sh  # wrapper pratique
```

Le script extrait les binaires officiels `rush1-x` fournis (`rush1_bins.tgz`) et vérifie :
- Cas basique pour chaque rush.
- Cas ambigus (`1x1`, `5x1`).
- Cas sans correspondance.

Tous les tests renvoient actuellement `Passed: 6  Failed: 0`.
