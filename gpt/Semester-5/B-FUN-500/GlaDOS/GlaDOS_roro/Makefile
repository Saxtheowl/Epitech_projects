##
## EPITECH PROJECT, 2025
## GLaDOS_roro
## File description:
##   Minimal tests harness
##

TEST_DIR	=	tests

all:
	@echo "Nothing to build for GLaDOS_roro"

clean:
	rm -f $(TEST_DIR)/*.o unit_tests *.gcno *.gcda *.gcov

fclean: clean
	@true

re: fclean all

unit_tests: CFLAGS += --coverage
unit_tests: LDFLAGS += -lcriterion
unit_tests:	$(TEST_DIR)/test_basic.o
	$(CC) -o $@ $(TEST_DIR)/test_basic.o $(LDFLAGS)

tests_run: unit_tests
	./unit_tests || true

.PHONY: all clean fclean re tests_run unit_tests
