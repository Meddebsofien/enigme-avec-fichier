prog:Enigme.o main.o 
	gcc Enigme.o main.o  -o prog -lSDL -lSDL_ttf -lSDL_image -lSDL_mixer -g
main.o:main.c
	gcc -c main.c -g
Enigme.o:Enigme.c
	gcc -c Enigme.c -g
