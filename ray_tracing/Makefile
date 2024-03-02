all: create_bin color
	g++ main.cpp ./bin/*.o -o ./bin/main

color: create_bin
	g++ color.cpp -c -o ./bin/color.o

create_bin:
	mkdir -p bin

clean:
	rm -rf bin
