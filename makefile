PROG= VieLab
CC=gcc
CFLAG= -g -Wall
OBJ= ./fonctions/labyrinthe.o ./fonctions/menu.o ./fonctions/finpartie.o ./fonctions/utilisateur.o ./fonctions/generation.o ./fonctions/fourmis.o ./fonctions/contigue.o ./fonctions/decouvert.o ./fonctions/dijkstra.o

all: ${PROG}

${PROG}: ${OBJ}
	${CC} ${CFLAG} ${OBJ} -o ${PROG}

menu.o: ./fonctions/menu.c
	${CC} ${CFLAG} -c ./fonctions/menu.c

labyrinthe.o: ./fonctions/labyrinthe.c
	${CC} ${CFLAG} -c ./fonctions/labyrinthe.c

finpartie.o: ./fonctions/finpartie.c
	${CC} ${CFLAG} -c ./fonctions/finpartie.c

utilisateur.o: ./fonctions/utilisateur.c
	${CC} ${CFLAG} -c ./fonctions/utilisateur.c

generation.o: ./fonctions/generation.c
	${CC} ${CFLAG} -c ./fonctions/generation.c

fourmis.o: ./fonctions/fourmis.c
	${CC} ${CFLAG} -c ./fonctions/fourmis.c

contigue.o: ./fonctions/contigue.c
	${CC} ${CFLAG} -c ./fonctions/contigue.c

decouvert.o: ./fonctions/decouvert.c
	${CC} ${CFLAG} -c ./fonctions/decouvert.c

dijkstra.o: ./fonctions/dijkstra.c
	${CC} ${CFLAG} -c ./fonctions/dijkstra.c

#Supression des fichiers temporaires
clean:
	rm -f ./fonctions/*.o
