output: main.o player.o entity.o
	g++ main.o player.o entity.o ../include/raylib.h -o main.exe -O2 -Wall -I ../include/ -L ../lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

main.o: ../main.cpp
	g++ -c ../main.cpp

player.o: ../lib/player.cpp ../include/player.hpp
	g++ -c ../lib/player.cpp

entity.o: ../lib/entity.cpp ../include/entity.hpp
	g++ -c ../lib/entity.cpp

clean:
	rm ./*.o ./main.exe