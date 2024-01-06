output: main.o player.o
	g++ main.o player.o ./include/raylib.h -o main.exe -O2 -Wall -I ./include/ -L ./lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

main.o: main.cpp
	g++ -c main.cpp

player.o: player.cpp player.hpp
	g++ -c player.cpp

clean:
	rm ./*.o ./main.exe