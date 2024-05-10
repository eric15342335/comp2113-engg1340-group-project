# MAKEFILE USAGE:
# make - compiles the program
# make test - runs the program
# make clean - removes the compiled program and object files
# make docs - generates the documentation using Doxygen
# make fix - formats the code using clang-format and commits the changes to git
# make stats - shows the last 10 commits and the current branches
# make goto - proceed several rounds automatically and print the price history graph

# Compiler flags, consider removing `-Werror` before submitting.

FLAGS = -Wall -Wextra -std=c++17 -Werror -pedantic-errors -g -O0\
		-mtune=native
# -fsanitize=address -fsanitize=undefined

ifeq ("$(OS)","Windows_NT")
FLAGS += -static
endif

# The default target is to compile the program.
default: stocksim

random_price.o: random_price.h random_price.cpp events.h stock.h
	g++ $(FLAGS) -c random_price.cpp -o random_price.o
	
file_io.o: file_io.cpp file_io.h stock.h
	g++ $(FLAGS) -c file_io.cpp -o file_io.o

stock.o: stock.cpp stock.h names.h random_price.h events.h format.h
	g++ $(FLAGS) -c stock.cpp -o stock.o

events.o: events.h events.cpp random_price.h
	g++ $(FLAGS) -c events.cpp -o events.o

names.o: names.h names.cpp
	g++ $(FLAGS) -c names.cpp -o names.o

format.o: format.cpp format.h
	g++ $(FLAGS) -c format.cpp -o format.o

draw.o: draw.cpp draw.h format.h
	g++ $(FLAGS) -c draw.cpp -o draw.o

graph.o: graph.h graph.cpp
	g++ $(FLAGS) -c graph.cpp -o graph.o

controls.o: controls.cpp controls.h draw.h format.h stock.h
	g++ $(FLAGS) -c controls.cpp -o controls.o

stocksim: main.cpp stock.o random_price.o events.o names.o \
		  graph.o format.o draw.o file_io.o controls.o
	g++ $(FLAGS) main.cpp stock.o random_price.o events.o names.o \
				 graph.o format.o draw.o file_io.o controls.o\
				 -o stocksim

test: stocksim
	./stocksim

goto: stocksim
	rm -r saves/ 2>/dev/null || true
	echo -e "0\nsave\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY" \
	        "\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY" \
			"\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY" \
		    "\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY\nX\nY" | ./stocksim
	echo -e "1\nsave\nT\n0\nX\nY\n" | ./stocksim

clean:
	rm *.o stocksim -r saves/ html/ latex/ *.obj *.pdb *.ilk *.dSYM/ 2>/dev/null || true

# Generate documentation using `Doxygen`.
# Windows only: open the generated documentation in the default browser.
docs: Doxyfile
	cp Doxyfile Doxyfile.temp
	echo PROJECT_NUMBER = $$(git log -n1 --format="%h") >> Doxyfile.temp
	doxygen Doxyfile.temp
	@if [ "$(OS)" = "Windows_NT" ]; then \
		start "html/index.html"; \
	fi
	rm Doxyfile.temp

fix:
	clang-format --verbose -i *.cpp *.h
	git commit -a -m "Run clang-format" -m "make fix"
	git push

stats:
	git checkout main
	git remote prune origin
	git pull --ff
	git branch -av
	git --no-pager log --oneline --graph -10

msvc: *.cpp *.h
	clear
	# To compile the program using the Microsoft Visual C++ compiler,
	# Launch the Visual Studio Developer Command Prompt
	# and run the following command:
	#
	# cl -std:c++17 -EHsc -utf-8 *.cpp -Fe:stocksim.exe

.PHONY: test clean docs fix stats goto \
		msvc
