OBJ = main.o
CFLAGS = -std=c++11 -Wall -g -c
LFLAGS = -lm

all: $(OBJ)
	g++ -o rnd229 $(LFLAGS) $(OBJ)

main.o: main.cpp
	g++ $(CFLAGS) main.cpp

clean:
	rm -rf rnd229
	rm -rf *.o
