CCOPTS=-Wall -std=c++11 -O3

all: bin/gcoloration

bin/gcoloration: obj/graphe_tool.o obj/sommet.o src/main.cpp
	g++ $(CCOPTS) -o $@ $^

obj/graphe_tool.o: src/graphe_tool.cpp src/header/graphe_tool.h
	g++ $(CCOPTS) -o $@ -c src/graphe_tool.cpp

obj/sommet.o: src/sommet.cpp src/header/sommet.h
	g++ $(CCOPTS) -o $@ -c src/sommet.cpp

clear:
	rm obj/* bin/gcoloration