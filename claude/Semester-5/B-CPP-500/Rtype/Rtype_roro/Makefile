##
## EPITECH PROJECT, 2025
## R-Type
## File description:
## Fallback Makefile for R-Type project
##

CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -std=c++17 -Iinclude

# Directories
SRCDIR = src
OBJDIR = obj
TESTDIR = tests

# Common source files
COMMON_SOURCES = $(wildcard $(SRCDIR)/common/*.cpp) \
                 $(wildcard $(SRCDIR)/engine/*.cpp)

SERVER_SOURCES = $(wildcard $(SRCDIR)/server/*.cpp)
CLIENT_SOURCES = $(wildcard $(SRCDIR)/client/*.cpp)
TEST_SOURCES = $(wildcard $(TESTDIR)/*.cpp)

# Object files
COMMON_OBJS = $(COMMON_SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
SERVER_OBJS = $(SERVER_SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
CLIENT_OBJS = $(CLIENT_SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
TEST_OBJS = $(TEST_SOURCES:$(TESTDIR)/%.cpp=$(OBJDIR)/tests/%.o)

# Targets
SERVER_TARGET = r-type_server
CLIENT_TARGET = r-type_client
TEST_TARGET = rtype_tests

# Libraries
LIBS = -lpthread
CLIENT_LIBS = $(LIBS)

# Try to detect SFML
SFML_LIBS = $(shell pkg-config --libs sfml-all 2>/dev/null || echo "-lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio")
SFML_CFLAGS = $(shell pkg-config --cflags sfml-all 2>/dev/null)

# Check if SFML is available
SFML_AVAILABLE = $(shell pkg-config --exists sfml-all && echo "yes" || echo "no")

.PHONY: all clean fclean re server client tests

all: server client

server: $(SERVER_TARGET)

client: $(CLIENT_TARGET)

$(SERVER_TARGET): $(COMMON_OBJS) $(SERVER_OBJS)
	$(CXX) -o $@ $^ $(LIBS)

$(CLIENT_TARGET): $(COMMON_OBJS) $(CLIENT_OBJS)
ifeq ($(SFML_AVAILABLE),yes)
	$(CXX) $(SFML_CFLAGS) -o $@ $^ $(CLIENT_LIBS) $(SFML_LIBS)
else
	@echo "Warning: SFML not found - client cannot be built"
	@echo "Please install SFML development libraries"
endif

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(SFML_CFLAGS) -c $< -o $@

$(OBJDIR)/tests/%.o: $(TESTDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

tests: $(TEST_TARGET)

$(TEST_TARGET): $(COMMON_OBJS) $(TEST_OBJS)
	$(CXX) -o $@ $^ $(LIBS)

tests_run: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	$(RM) -rf $(OBJDIR)

fclean: clean
	$(RM) $(SERVER_TARGET) $(CLIENT_TARGET) $(TEST_TARGET)

re: fclean all

debug: CXXFLAGS += -g3 -DDEBUG
debug: all

install: all
	mkdir -p ~/.local/bin
	cp $(SERVER_TARGET) ~/.local/bin/
	if [ -f $(CLIENT_TARGET) ]; then cp $(CLIENT_TARGET) ~/.local/bin/; fi

help:
	@echo "R-Type Build System"
	@echo "Available targets:"
	@echo "  all       - Build server and client (if SFML available)"
	@echo "  server    - Build server only"
	@echo "  client    - Build client (requires SFML)"
	@echo "  tests     - Build test suite"
	@echo "  tests_run - Build and run tests"
	@echo "  clean     - Remove object files"
	@echo "  fclean    - Remove all generated files"
	@echo "  re        - Rebuild everything"
	@echo "  debug     - Build with debug symbols"
	@echo "  install   - Install binaries to ~/.local/bin"