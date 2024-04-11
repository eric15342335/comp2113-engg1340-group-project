# Not finished yet
default: stocksim

random_price.o: random_price.h random_price.cpp
	g++ -Wall -Wextra -std=c++11 -c random_price.cpp -o random_price.o

stock.o: stock.cpp stock.h names.h random_price.h events.h
	g++ -Wall -Wextra -std=c++11 -c stock.cpp -o stock.o

events.o: events.h events.cpp
	g++ -Wall -Wextra -std=c++11 -c events.cpp -o events.o

names.o: names.h names.cpp
	g++ -Wall -Wextra -std=c++11 -c names.cpp -o names.o

graph.o: graph_plotting.h graph_plotting.cpp
	g++ -Wall -Wextra -std=c++11 -c graph_plotting.cpp -o graph.o

stocksim: main.cpp stock.o random_price.o events.o names.o
	g++ -Wall -Wextra -std=c++11 main.cpp stock.o random_price.o events.o names.o -o stocksim

test: stocksim
	./stocksim

clean: 
	rm *.o stocksim

.PHONY: test clean
