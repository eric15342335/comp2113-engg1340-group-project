# MAKEFILE USAGE:
# make - compiles the program
# make test - runs the program
# make clean - removes the compiled program and object files
# make docs - generates the documentation using Doxygen
# make fix - formats the code using clang-format and commits the changes to git

# Compiler flags, consider removing `-Werror` before submitting.
FLAGS = -Wall -Wextra -std=c++11 -Werror -pedantic-errors -g -O0

# The default target is to compile the program.
default: stocksim

random_price.o: random_price.h random_price.cpp
	g++ $(FLAGS) -c random_price.cpp -o random_price.o

stock.o: stock.cpp stock.h names.h random_price.h events.h
	g++ $(FLAGS) -c stock.cpp -o stock.o

events.o: events.h events.cpp
	g++ $(FLAGS) -c events.cpp -o events.o

names.o: names.h names.cpp
	g++ $(FLAGS) -c names.cpp -o names.o

format.o: format.cpp format.h
	g++ $(FLAGS) -c format.cpp -o format.o

draw.o: draw.cpp draw.h format.h
	g++ $(FLAGS) -c draw.cpp -o draw.o

graph.o: graph.h graph.cpp
	g++ $(FLAGS) -c graph.cpp -o graph.o

stocksim: main.cpp stock.o random_price.o events.o names.o graph.o format.o draw.o
	g++ $(FLAGS) main.cpp stock.o random_price.o events.o names.o graph.o format.o draw.o -o stocksim

test: stocksim
	./stocksim

clean:
	rm *.o stocksim

# Generate documentation using `Doxygen`.
# Windows only: open the generated documentation in the default browser.
docs: Doxyfile
	doxygen Doxyfile
	@if [ "$(OS)" = "Windows_NT" ]; then \
		start "html/index.html"; \
	fi

fix:
	clang-format --verbose -i *.cpp *.h
	git commit -a -m "Run clang-format" -m "make fix"
	git push

all:
	make clean
	make
	make test
	make docs

.PHONY: test clean docs fix all
