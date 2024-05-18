output: main.o entity.o player.o
	g++ main.o entity.o player.o -o calypso -O2 -Wall -lbox2d -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	./calypso

main.o: ../main.cpp
	g++ -c ../main.cpp

entity.o: ../lib/entity.cpp
	g++ -c ../lib/entity.cpp

player.o: ../lib/player.cpp
	g++ -c ../lib/player.cpp

clean:
	rm ./*.o ./main