# BSQ (B-CPE-110)

Finds the largest possible square in a grid while avoiding obstacles. The map is
read from a file where the first line gives the number of rows, followed by rows of
`.` (empty) and `o` (obstacles).

## Contraintes du sujet
- `MUST` n’utiliser que `open`, `read`, `close`, `write`, `malloc`, `free` (réf. `BSQ.pdf`).
- `MUST` lire une carte dont la première ligne indique le nombre de lignes, suivie de
  lignes composées uniquement de `.` (vide) et `o` (obstacle) de longueur uniforme.
- `MUST` remplacer la plus grande zone carrée de `.` par `x`, en privilégiant le
  carré le plus haut puis le plus à gauche en cas d’égalité.
- `MUST` écrire `map error\n` sur la sortie d’erreur et quitter avec 84 pour toute
  carte invalide ou erreur d’E/S.
- `KNOWN LIMIT` seul le format texte est supporté; aucune compression ni caractères
  supplémentaires n’est tolérée.

## Build

```sh
make
```

Produces the `bsq` binary. Additional targets: `clean`, `fclean`, `re`, `test`.

## Usage

```sh
./bsq maps/example_map
```

On success, the program prints the map with the largest square filled using `x`.
If the map is invalid the program prints nothing and exits with status 84.

## Implementation notes

- `read_entire_file` loads the file using only the allowed system calls
  (`open`, `read`, `close`, `malloc`, `free`).
- `parse_map` validates dimensions, character set and uniform line length.
- Dynamic programming (`solve_bsq`) computes square sizes in O(rows × cols).
- `mark_square` replaces the winning square with `x` before the map is printed.

## Tests

```sh
make test          # builds and runs regression scenarios
./scripts/test.sh  # convenience wrapper
```

`tests/test.sh` reconstruit le binaire, s’appuie sur `tests/solve_ref.py` (solveur de
référence en Python) pour comparer la sortie à un résultat déterministe, et vérifie
également que les cartes invalides retournent bien 84 avec `map error` sur stderr.
