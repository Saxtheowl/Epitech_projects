##
## EPITECH PROJECT, 2025
## Popeye - Makefile
## File description:
## Build and test via Docker/Compose
##

.PHONY: all build up down test clean fclean re tests_run

IMAGE	=	popeye-ci:latest

all: build

build:
	docker build -t $(IMAGE) -f Dockerfile .

up: build
	docker compose up --build -d

down:
	docker compose down --remove-orphans || true

test: build
	docker run --rm -v "$(PWD)/../../..:/workspace" $(IMAGE) /bin/sh -lc "make -C /workspace/Semester-2 tests_run"

tests_run:
	@echo "No local unit tests; use 'make test' to run CI pipeline in Docker"

clean:
	@true

fclean: down
	@true

re: fclean all
