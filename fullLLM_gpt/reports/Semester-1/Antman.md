# Antman (B-CPE-110)

## Subject recap
- Two binaries: `antman` (compress) and `giantman` (decompress).
- Supported file hints (1=lyrics, 2=HTML, 3=P3 PPM) but programs must cope with any
  content; compression must be lossless (giantman must reproduce the original file).
- Allowed syscalls: `open`, `read`, `write`, `close`, `malloc`, `free`, `stat`.

## Implementation
- Compression uses a PackBits-inspired RLE:
  * Output header `"AR01"` + one byte storing the file type.
  * Literal blocks: control byte `0xxxxxxx` followed by `(ctrl+1)` raw bytes.
  * Run blocks: control byte `1xxxxxxx` followed by the repeated byte, repeated
    `(ctrl&0x7F)+1` times.
  Runs start at sequences of ≥2 identical bytes, giving modest but reliable
  compression while being 100% reversible.
- Decompression validates the header and emits literal/run segments back to stdout.
- File loading is done with custom helpers that reallocate dynamically yet rely only
  on allowed syscalls. Output uses `write_all` to avoid partial writes.

## Tests
- `make test` runs `antman/tests/test.sh` and `giantman/tests/test.sh`:
  * Antman tests create sample inputs (text, HTML-like, binary), compress them,
    decompress via `giantman`, and diff the output.
  * Giantman tests similarly round-trip using both binaries to guarantee symmetry.

## Notes & risks
- Compression ratio varies; RLE shines on repeated bytes and remains near 2× in the
  worst case (header + block tags). The spec only requires that it “compresses
  sometimes”, which this approach satisfies.
- The type byte is currently informational; the pipeline can be extended with
  type-specific heuristics in the future.
