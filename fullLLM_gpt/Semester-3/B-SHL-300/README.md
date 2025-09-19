> Crédits disponibles: 1 crédits

## BDSH — Simple JSON DB in POSIX sh

- Binary: `./bdsh` (shebang `/bin/sh`)
- DB file selection priority: `-f FILE` > env `BDSH_File` > local `.bdshrc`
- Authorized tools used: `[`, `test`, `expr`, `wc`, `head`, `tail`, `cat`, `sort`, `grep`, `sed`, `rm`, `cut`, `ps`, `tr`, `touch`, `mkdir`, `find`.

### Build
- Nothing to build. Ensure `bdsh` is executable: `chmod +x bdsh`.

### Usage
- Help: `./bdsh -h`
- Create DB: `./bdsh -f db.json create database`
- Create table: `./bdsh -f db.json create table user id,firstname,lastname`
- Insert: `./bdsh -f db.json insert user id=1,firstname=John,lastname=SMITH`
- Select (table): `./bdsh -f db.json select user firstname,lastname`
- Select with where: `./bdsh -f db.json select user firstname,id where lastname=SMITH`
- Select with order: `./bdsh -f db.json select user firstname where lastname=SMITH orderby firstname`
- Join: `./bdsh -f db.json select user,age age,firstname,lastname join id where age=42`
- JSON output: add `-j` to any `select`.

Notes:
- Errors are printed on stderr and return code is 1.
- `update`/`delete` are not implemented (bonus).

Implementation detail: to avoid fragile JSON round-trips, a sidecar state directory `<db.json>.state` stores per-table rows. The JSON DB file is regenerated from this state on each change.

### Tests
- Run all tests: `make test`
- Location: `tests/test.sh`

Expected summary (passing):
```
Passed: 6  Failed: 0
```

### Clean
- Remove temp DBs: `make clean`

### Limits
- Schema is not enforced.
- Only equality `where` and simple two-table equi-join are supported.
