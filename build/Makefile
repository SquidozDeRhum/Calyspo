output: main.o entity.o player.o
	g++ main.o entity.o player.o -o main -O2 -Wall -lbox2d -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	./main

main.o: ../main.cpp
	g++ -c ../main.cpp

entity.o: ../entity.cpp
	g++ -c ../entity.cpp

player.o: ../player.cpp
	g++ -c ../player.cpp

clean:
	rm ./*.o ./main