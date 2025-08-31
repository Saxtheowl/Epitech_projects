##
## EPITECH PROJECT, 2025
## Semester-2 aggregator Makefile
## File description:
## Build and test all *_roro projects in this semester
##

.PHONY: all clean fclean re tests_run list

PROJECTS := $(shell git ls-files "Semester-2/**/_roro/Makefile" | xargs -n1 dirname)

all:
	@set -e; \
	for d in $(PROJECTS); do \
		echo "==> Building $$d"; \
		$(MAKE) -C $$d all; \
	done

tests_run:
	@set -e; \
	for d in $(PROJECTS); do \
		if [ -f "$$d/Makefile" ]; then \
			if grep -q "tests_run:" "$$d/Makefile"; then \
				echo "==> Testing $$d"; \
				$(MAKE) -C $$d tests_run || true; \
			fi; \
		fi; \
	done

clean:
	@for d in $(PROJECTS); do \
		$(MAKE) -C $$d clean || true; \
	done

fclean:
	@for d in $(PROJECTS); do \
		$(MAKE) -C $$d fclean || true; \
	done

re: fclean all

list:
	@printf "Projects (detected *_roro):\n"; \
	for d in $(PROJECTS); do echo "  - $$d"; done

