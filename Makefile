MAKEFLAGS += --jobs=$(shell nproc)
# make \
compile program
# make all \
compile and run program
# make clean \
removes executable, object files, saves, and docs

# developer commands:
# make docs \
generates the html docs using Doxygen
# make fix \
formats the code using clang-format, commits, and pushes the changes
# make goto \
proceed several rounds automatically and print the price history graph
# make msvc \
compile the program using the Microsoft Visual C++ compiler
# make check \
check the code for formatting and static analysis issues

CC = g++
INCLUDES = -Iinclude
FLAGS += -Wall -Wextra -pedantic -std=c++17 -Werror -g -pipe -fPIE -pie \
	-Wcast-qual -Wundef -Wduplicated-cond -Wduplicated-branches \
	-mtune=generic -Wswitch -Wshadow
	# -Wconversion -Wfloat-equal
	# -O3 -flto -march=nocona
	# -D_FORTIFY_SOURCE=2 -fstack-protector-all -Og
	# -fsanitize=address -fsanitize=undefined

# macOS uses clang++, which does not support these flag:
# -Wduplicated-cond -Wduplicated-branches
ifeq ($(shell uname),Darwin)
	FLAGS += -Wno-error=no-unknown-warning-option -Wno-error=no-unused-command-line-argument
else ifeq ($(CC),clang++)
	FLAGS += -Wno-error=no-unknown-warning-option -Wno-error=no-unused-command-line-argument
endif
# eric15342335 will use the static flag on Windows.
ifeq ("$(OS)","Windows_NT")
	FLAGS += -static
	ifeq ($(CC),clang++)
		FLAGS += -pthread
	endif
endif

release: clean
	FLAGS="-O3 -flto -D_FORTIFY_SOURCE=2 -fstack-protector-all -march=nocona" "$(MAKE)" stocksim

# The default target is to compile the program.
default: stocksim

random_price.o: src/random_price.cpp \
		include/random_price.h include/events.h include/stock.h
	$(CC) $(INCLUDES) $(FLAGS) -c $< -o $@

file_io.o: src/file_io.cpp \
		include/file_io.h include/stock.h
	$(CC) $(INCLUDES) $(FLAGS) -c $< -o $@

stock.o: src/stock.cpp \
		include/stock.h include/names.h include/random_price.h \
		include/events.h include/format.h
	$(CC) $(INCLUDES) $(FLAGS) -c $< -o $@

events.o: src/events.cpp \
		include/events.h include/random_price.h
	$(CC) $(INCLUDES) $(FLAGS) -c $< -o $@

names.o: src/names.cpp \
		include/names.h
	$(CC) $(INCLUDES) $(FLAGS) -c $< -o $@

format.o: src/format.cpp \
		include/format.h
	$(CC) $(INCLUDES) $(FLAGS) -c $< -o $@

draw.o: src/draw.cpp \
		include/draw.h include/format.h
	$(CC) $(INCLUDES) $(FLAGS) -c $< -o $@

graph.o: src/graph.cpp \
		include/graph.h
	$(CC) $(INCLUDES) $(FLAGS) -c $< -o $@

controls.o: src/controls.cpp \
		include/controls.h include/draw.h include/format.h include/stock.h
	$(CC) $(INCLUDES) $(FLAGS) -c $< -o $@

stocksim: src/main.cpp stock.o random_price.o events.o names.o \
		graph.o format.o draw.o file_io.o controls.o
	$(CC) $(INCLUDES) $(FLAGS) $^ -o $@

all: clean
	$(MAKE) stocksim
	./stocksim

goto: stocksim
	rm -r saves/ 2>/dev/null || true
	echo -e "0\nsave\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY" \
			"\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY" \
			"\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY" \
			"\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY\nN\nY\nX\nY" | ./stocksim
	echo -e "1\nsave\nT\n0\nX\nY\n" | ./stocksim

clean:
	rm *.o stocksim?* -r saves/ html/ latex/ *.obj *.pdb *.ilk *.dSYM/ 2>/dev/null || true

# Generate documentation using `Doxygen`.
docs: .github/Doxyfile src/*.cpp include/*.h
	cp .github/Doxyfile Doxyfile.temp
	echo PROJECT_NUMBER = $$(git branch --show-current) $$(git log -n1 --format="%h") >> Doxyfile.temp
	doxygen Doxyfile.temp
	rm Doxyfile.temp

fix:
	git pull
	clang-format --verbose -i src/*.cpp include/*.h
	git commit -a -m "Formatting: Run clang-format" -m "From Makefile: make fix"
	git push

msvc: src/*.cpp include/*.h
	# To compile the program using the Microsoft Visual C++ compiler,
	# Launch the Visual Studio Developer Command Prompt
	# and run the following command:
	#
	cl -std:c++17 -EHsc -utf-8 src/*.cpp -Iinclude -Fe:stocksim-msvc.exe

check:
	clang-format --dry-run --Werror src/*.cpp include/*.h
	clang-tidy src/*.cpp --checks=performance-*,-performance-avoid-endl,readability-*,bugprone-*,portability-*,cert-* \
		--fix-errors --fix-notes --format-style=file -- -Iinclude

.PHONY: all clean docs fix goto msvc check release
