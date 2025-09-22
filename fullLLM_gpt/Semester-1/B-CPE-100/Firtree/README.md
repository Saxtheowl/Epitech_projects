# Firtree (B-CPE-100)

Implementation of the Epitech "Fir Tree" exercise: render a scalable ASCII fir tree of the
requested size using only the `my_putchar` helper supplied by the grader (itself wrapping
`write(2)`).

## Contraintes du sujet
- `MUST` livrer uniquement la fonction `void tree(int size);` qui écrit la sortie via
  `my_putchar` (pas d'appels directs à `printf`, `puts`, etc.).
- `MUST` accepter `size = 0` sans rien afficher et retourner normalement.
- `MUST` éviter tout dépassement d’entier ou comportement indéfini pour les tailles
  raisonnables (le sujet teste typiquement `0..5`).
- `SHOULD` garder la livraison propre (pas de binaire, `my_putchar.c` fourni ici
  uniquement pour le développement local).

## Build

```sh
make
```

## Usage

```sh
./firtree <size>
```

- `<size>` is a non-negative integer. `0` is valid and produces no output, as required by
  the subject.
- Invalid inputs return exit code `84` without printing anything.

## Tests

```sh
make test
```

The test suite extrait l'oracle officiel (`firtree.tgz`), compare le rendu pour les tailles
0 à 5, et couvre les cas d'erreur représentatifs (argument manquant, valeur non numérique,
entier négatif).
