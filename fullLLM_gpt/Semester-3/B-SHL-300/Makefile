SHELL := /bin/sh

.PHONY: all test clean

all:
	@echo "Nothing to build. Use ./bdsh"

test:
	sh tests/test.sh

clean:
	rm -f tests/tmp/*.json 2>/dev/null || true

