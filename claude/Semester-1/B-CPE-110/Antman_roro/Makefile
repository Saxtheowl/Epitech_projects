##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Root Makefile for Antman project - compiles both binaries
##

.PHONY: all clean fclean re tests_run

all:
	$(MAKE) -C antman
	$(MAKE) -C giantman

clean:
	$(MAKE) -C antman clean
	$(MAKE) -C giantman clean
	rm -f shared/*.o

fclean:
	$(MAKE) -C antman fclean
	$(MAKE) -C giantman fclean
	rm -f shared/*.o

re: fclean all

tests_run: all
	@echo "Testing compression and decompression..."
	@echo "Maiha hi Maiha hou Maiha ha Maiha ha ha" > test_file.txt
	@echo "Compressing file..."
	./antman/antman test_file.txt 1 > compressed.data
	@echo "Decompressing file..."
	./giantman/giantman compressed.data 1 > decompressed.txt
	@echo "Checking round-trip integrity..."
	@diff test_file.txt decompressed.txt && echo "SUCCESS: Files identical" || echo "FAILED: Files differ"
	@rm -f test_file.txt compressed.data decompressed.txt