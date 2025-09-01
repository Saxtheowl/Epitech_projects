##
## EPITECH PROJECT, 2025
## Automakefile
## File description:
## Makefile for automakefile project
##

NAME = automakefile

all: $(NAME)

$(NAME):
	@echo "Scripts are already executable"

clean:
	@echo "No object files to clean"

fclean: clean
	@echo "No binaries to clean"

re: fclean all

install:
	@echo "Installing scripts..."
	chmod +x skip-synthesis.sh
	chmod +x automakefile
	@echo "Installation complete"

test:
	@echo "Testing skip-synthesis.sh..."
	@echo -e "drwxr-xr-x 2 Zeus Zeus 4096 Jan 01 00:00 totoTest\n-rw-r--r-- 1 Zeus Zeus 1024 Jan 01 00:00 tomatoKetchup\n-rw-r--r-- 1 pierre.perret staff 2048 Jan 01 00:00 toutToutTout\ndrwxr-xr-x 2 Stallman users 4096 Jan 01 00:00 torus4d" | ./skip-synthesis.sh "to"
	@echo "Testing automakefile..."
	@echo "Check test_project for generated Makefile"

.PHONY: all clean fclean re install test