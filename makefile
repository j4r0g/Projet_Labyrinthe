PROG= VieLab
CC=gcc
CFLAG= -g -Wall
OBJ= ./fonctions/labyrinthe.o ./main.o ./fonctions/finpartie.o ./fonctions/utilisateur.o ./fonctions/generation.o ./fonctions/contigue.o ./fonctions/decouvert.o ./fonctions/dijkstra.o

all: ${PROG}

${PROG}: ${OBJ}
	${CC} ${CFLAG} ${OBJ} -o ${PROG}

main.o: ./main.c ./header/struct.h ./header/main.h
	${CC} ${CFLAG} -c ./main.c ./header/struct.h ./header/main.h

labyrinthe.o: ./fonctions/labyrinthe.c
	${CC} ${CFLAG} -c ./fonctions/labyrinthe.c

finpartie.o: ./fonctions/finpartie.c
	${CC} ${CFLAG} -c ./fonctions/finpartie.c

utilisateur.o: ./fonctions/utilisateur.c
	${CC} ${CFLAG} -c ./fonctions/utilisateur.c

generation.o: ./fonctions/generation.c
	${CC} ${CFLAG} -c ./fonctions/generation.c

contigue.o: ./fonctions/contigue.c
	${CC} ${CFLAG} -c ./fonctions/contigue.c

decouvert.o: ./fonctions/decouvert.c
	${CC} ${CFLAG} -c ./fonctions/decouvert.c

dijkstra.o: ./fonctions/dijkstra.c ./header/dijkstra.h
	${CC} ${CFLAG} -c ./fonctions/dijkstra.c ./header/dijkstra.h

#Supression des fichiers temporaires
clean:
	rm -f *.o
	rm -f ./fonctions/*.o

mrproper: clean
	rm -f VieLab.*
	rm -f VieLab
