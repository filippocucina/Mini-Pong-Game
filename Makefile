build:
	gcc -Wall -std=c99 -lSDL2 -o game /software/programming/lenguajeC/game/src/*.c

run:
	./game /software/programming/lenguajeC/game/src/game

clean:
	rm game

