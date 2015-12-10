PROG= VieLab
CC=gcc
CFLAG= -g -Wall
OBJ= ./fonctions/labyrinthe.o ./fonctions/menu.o ./fonctions/finpartie.o ./fonctions/utilisateur.o ./fonctions/generation.o ./fonctions/fourmis.o ./fonctions/contigue.o

all: ${PROG}

${PROG}: ${OBJ}
	${CC} ${CFLAG} ${OBJ} -o ${PROG}

menu.o: ./fonctions/menu.c
	${CC} ${CFLAG} -c ./fonctions/menu.c

labyrinthe.o: ./fonctions/labyrinthe.c
	${CC} ${CFLAG} -c ./fonctions/labyrinthe.c

finpartie.o: ./fonctions/finpartie.c
	${CC} ${CFLAG} ./fonctions/finpartie.c

utilisateur.o: ./fonctions/utilisateur.c
	${CC} ${CFLAG} ./fonctions/utilisateur.c

generation.o: ./fonctions/generation.c
	${CC} ${CFLAG} ./fonctions/generation.c

fourmis.o: ./fonctions/fourmis.c
	${CC} ${CFLAG} ./fonctions/fourmis.c

contigue.o: ./fonctions/contigue.c
	${CC} ${CFLAG} ./fonctions/contigue.c

#Supression des fichiers temporaires
clean:
	rm -f ./fonctions/*.o
