PHOENIX_LIB = lib/phoenix/libphoenix.a
PROGRAMS = \
	Day03/task04/show_params \
	Day03/task05/sorted_params \
	Day04/task02/concat_parameters \
	Day05/star

all: $(PHOENIX_LIB) $(PROGRAMS)

$(PHOENIX_LIB):
	$(MAKE) -C lib/phoenix

Day03/task04/show_params:
	$(MAKE) -C Day03/task04

Day03/task05/sorted_params:
	$(MAKE) -C Day03/task05

Day04/task02/concat_parameters:
	$(MAKE) -C Day04/task02

Day05/star:
	$(MAKE) -C Day05

test: all
	$(MAKE) -C tests test
	./tests/test_star.py

clean:
	$(MAKE) -C lib/phoenix clean
	$(MAKE) -C Day03/task04 clean
	$(MAKE) -C Day03/task05 clean
	$(MAKE) -C Day04/task02 clean
	$(MAKE) -C Day05 clean
	$(RM) -f tests/*.gcno tests/*.gcda tests/unit_tests

fclean: clean
	$(MAKE) -C lib/phoenix fclean
	$(MAKE) -C Day03/task04 fclean
	$(MAKE) -C Day03/task05 fclean
	$(MAKE) -C Day04/task02 fclean
	$(MAKE) -C Day05 fclean
	$(RM) -f $(PROGRAMS)

re: fclean all

.PHONY: all test clean fclean re
