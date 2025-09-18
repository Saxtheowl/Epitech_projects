CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror
NAME = test_skat
SRCDIR = .
OBJDIR = .

SOURCES = Skat.cpp test_skat.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re