output: main.o
	g++ main.o -o main -O2 -Wall -lbox2d -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	./main

main.o: ../main.cpp
	g++ -c ../main.cpp

clean:
	rm ./*.o ./main