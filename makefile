PROG= VieLab
CC=gcc
CFLAG= -g -Wall
OBJ= ./fonctions/labyrinthe_test.o ./fonctions/menu.o

all: ${PROG}

${PROG}: ${OBJ}
	${CC} ${CFLAG} ${OBJ} -o ${PROG}

menu.o: ./fonctions/menu.c
	${CC} ${CFLAG} -c ./fonctions/menu.c

labyrinthe_test.o: ./fonctions/labyrinthe_test.c
	${CC} ${CFLAG} -c ./fonctions/labyrinthe_test.c

#Supression des fichiers temporaires
clean:
	rm -f ./fonctions/*.o
