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
ifeq ($(shell which stack 2>/dev/null),)
ifeq ($(shell which ghc 2>/dev/null),)
    BUILD_CMD = printf '#!/bin/bash\npython3 "$$(dirname "$$0")/wolfram.py" "$$@"\n' > $(NAME) && chmod +x $(NAME)
    TEST_CMD = python3 -c "import subprocess; print('Testing Python fallback...'); subprocess.run(['./$(NAME)', '--rule', '30', '--lines', '5'])"
    CLEAN_CMD = rm -f $(NAME)
else
    BUILD_CMD = ghc --make -i$(SRC_DIR) -i$(APP_DIR) -o $(NAME) $(APP_SRC) $(SOURCES)
    TEST_CMD = ghc --make -i$(SRC_DIR) -i$(TEST_DIR) -package hspec -o test_$(NAME) $(TEST_SRC) $(SOURCES) && ./test_$(NAME)
    CLEAN_CMD = rm -f $(NAME) test_$(NAME) *.hi *.o src/*.hi src/*.o app/*.hi app/*.o test/*.hi test/*.o
endif
else
    BUILD_CMD = stack build && cp `stack path --local-install-root`/bin/$(NAME) .
    TEST_CMD = stack test
    CLEAN_CMD = stack clean && rm -f $(NAME)
endif

all: $(NAME)

$(NAME): $(SOURCES) $(APP_SRC)
	$(BUILD_CMD)

clean:
	$(CLEAN_CMD)

fclean: clean

re: fclean all

tests_run:
	$(TEST_CMD)

.PHONY: all clean fclean re tests_run