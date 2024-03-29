linux: main.o
	g++ main.o ../include/raylib.h ../include/box2d/box2d.h -o main -O2 -Wall -lbox2d -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	./main

main.o: ../main.cpp
	g++ -c ../main.cpp

clean:
	rm ./*.o ./main