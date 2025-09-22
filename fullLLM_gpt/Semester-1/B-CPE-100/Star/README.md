# Star (B-CPE-100)

Implementation of the Epitech "Star" exercise: render a symmetrical ASCII star of the
requested size, writing characters only through the `my_putchar` helper supplied by the
graders (itself wrapping `write(2)`).

## Contraintes du sujet
- `MUST` exposer `void star(int size);` (pas d’appel direct à `write`/`printf` dans le
  code livré; utiliser `my_putchar`).
- `MUST` accepter `size = 0` sans sortie et retourner 0.
- `MUST` retourner 84 sans sortie standard si l’argument est manquant ou non numérique.
- `SHOULD` conserver la livraison propre (supprimer `main`/`my_putchar` de confort avant
  soumission officielle si requis).

## Build

```sh
make
```

## Usage

```sh
./star <size>
```

- `<size>` is a non-negative integer. `0` produces no output, as required by the
  subject.
- On invalid input the program returns `84` without printing anything.

## Tests

```sh
make test
```

The test suite extrait les exemples officiels (`star_example.txt`), compare le rendu pour
les tailles 1, 2, 4 et 5, valide le cas `size = 0`, et vérifie les erreurs (argument
manquant, non numérique, valeur négative).
