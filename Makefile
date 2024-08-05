all:
	gcc -I include -L lib -o sdl.exe main.c src/*.c -lmingw32 -lSDL2main -lSDL2