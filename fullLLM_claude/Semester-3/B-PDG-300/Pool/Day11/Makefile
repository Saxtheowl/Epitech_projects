CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror

SOURCES = IDirectoryLister.cpp DirectoryLister.cpp SafeDirectoryLister.cpp \
          UniquePointer.cpp SharedPointer.cpp List.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f tests_run

re: fclean all

test: all test_main.cpp
	$(CXX) $(CXXFLAGS) test_main.cpp $(OBJECTS) -o test_runner
	./test_runner

tests_run: test

.PHONY: all clean fclean re tests_run