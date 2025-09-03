##
## EPITECH PROJECT, 2025
## Wolfram
## File description:
## Makefile
##

NAME = wolfram
SRC_DIR = src
APP_DIR = app
TEST_DIR = test

# Source files
SOURCES = $(SRC_DIR)/Wolfram.hs $(SRC_DIR)/Args.hs
APP_SRC = $(APP_DIR)/Main.hs
TEST_SRC = $(TEST_DIR)/Spec.hs

# Check if stack is available, then ghc, fallback to Python
BUILD_WITH_PYTHON = yes

ifeq ($(shell which stack 2>/dev/null),)
ifeq ($(shell which ghc 2>/dev/null),)
    BUILD_WITH_PYTHON = yes
else
    BUILD_WITH_PYTHON = no
endif
else
    BUILD_WITH_PYTHON = no
endif

all: $(NAME)

$(NAME): $(SOURCES) $(APP_SRC)
ifeq ($(BUILD_WITH_PYTHON),yes)
	@echo "#!/bin/bash" > $(NAME)
	@echo 'python3 "$$(dirname "$$0")/wolfram.py" "$$@"' >> $(NAME)
	@chmod +x $(NAME)
else
ifeq ($(shell which stack 2>/dev/null),)
	ghc --make -i$(SRC_DIR) -i$(APP_DIR) -o $(NAME) $(APP_SRC) $(SOURCES)
else
	stack build && cp `stack path --local-install-root`/bin/$(NAME) .
endif
endif

clean:
ifeq ($(BUILD_WITH_PYTHON),yes)
	rm -f $(NAME)
else
ifeq ($(shell which stack 2>/dev/null),)
	rm -f $(NAME) test_$(NAME) *.hi *.o src/*.hi src/*.o app/*.hi app/*.o test/*.hi test/*.o
else
	stack clean && rm -f $(NAME)
endif
endif

fclean: clean

re: fclean all

tests_run:
ifeq ($(BUILD_WITH_PYTHON),yes)
	python3 -c "import subprocess; print('Testing Python fallback...'); subprocess.run(['./$(NAME)', '--rule', '30', '--lines', '5'])"
else
ifeq ($(shell which stack 2>/dev/null),)
	ghc --make -i$(SRC_DIR) -i$(TEST_DIR) -package hspec -o test_$(NAME) $(TEST_SRC) $(SOURCES) && ./test_$(NAME)
else
	stack test
endif
endif

.PHONY: all clean fclean re tests_run