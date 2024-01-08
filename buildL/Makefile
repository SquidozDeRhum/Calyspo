output: main.o player.o entity.o
	g++ main.o player.o entity.o ../include/raylib.h ../include/box2d/box2d.h -o main -O2 -Wall -lbox2d -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	cp main ../
	cd ../ && ./main
	cd ./buildL

main.o: ../main.cpp
	g++ -c ../main.cpp

player.o: ../lib/player.cpp ../include/player.hpp
	g++ -c ../lib/player.cpp

entity.o: ../lib/entity.cpp ../include/entity.hpp
	g++ -c ../lib/entity.cpp

clean:
	rm ./*.o ./main.exe