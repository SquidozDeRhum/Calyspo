output: main.o entity.o player.o
	g++ build/*.o -o build/main -O2 -Wall -lbox2d -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	build/main

main.o: main.cpp
	g++ -o build/main.o -c main.cpp

entity.o: lib/entity.cpp
	g++ -o build/entity.o -c lib/entity.cpp

player.o: lib/player.cpp
	g++ -o build/player.o -c lib/player.cpp