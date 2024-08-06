all:
	gcc -I src/include -L src/lib -o trab.exe main.c src/*.c -lmingw32 -lSDL2main -lSDL2