# Antman & Giantman (B-CPE-110)

Lossless compression / decompression pipeline:
- `antman/antman` reads an input file and writes a compressed representation to stdout.
- `giantman/giantman` reads the compressed stream and restores the original data to stdout.

## Contraintes du sujet
- `MUST` n’utiliser que les appels système autorisés (lecture/écriture de fichiers via `open`, `read`, `write`, `close`, plus `malloc`/`free`).
- `MUST` respecter le format de sortie défini par le sujet: en-tête `AR01` suivi d’un octet identifiant le type (`1`=texte, `2`=HTML, `3`=P3).
- `MUST` refuser les types en dehors de `1..3` et retourner 84.
- `MUST` faire échouer la décompression si l’en-tête est invalide ou si le type embarqué ne correspond pas à l’argument fourni.
- `KNOWN LIMIT` algorithme PackBits-like commun aux trois types; des optimisations spécifiques (HTML balises, PPM) restent possibles en bonus.

## Format

A simple PackBits-like encoding is used:
- Header `"AR01"` followed by one byte storing the file type argument.
- Stream of blocks where the control byte MSB decides between literal and run blocks:
  * `0xxxxxxx` → copy the next `(ctrl + 1)` raw bytes.
  * `1xxxxxxx` → repeat the following byte `(ctrl & 0x7F) + 1` times.
This approach is lossless and works on arbitrary binary data.

## Build

```sh
make          # builds antman/antman and giantman/giantman
make clean    # remove objects
make fclean   # remove objects + binaries
make re       # rebuild
```

## Usage

```sh
./antman/antman input_file 1 > compressed.bin
./giantman/giantman compressed.bin 1 > output_file
```

The second argument (1=text, 2=HTML, 3=P3 PPM) is currently informational but kept to
match the subject. The output of `giantman` is byte-for-byte identical to the original.

## Tests

```sh
make test          # run both antman and giantman regression suites
./antman/tests/test.sh
./giantman/tests/test.sh
```

Tests actuels:
- Allers/retours sur données texte, HTML et binaires.
- Vérification automatique de l’en-tête (`AR01` + type) après compression.
- Refus des types invalides côté `antman`.
- Côté `giantman`: échec si le type ne correspond pas ou si l’en-tête est corrompu.
