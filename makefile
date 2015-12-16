PROG= VieLab
CC=gcc
CFLAG= -g -Wall
OBJ= ./fonctions/labyrinthe.o ./main.o ./fonctions/utilisateur.o ./fonctions/deplacement.o ./fonctions/depl1.o ./fonctions/insecte.o

all: ${PROG}

${PROG}: ${OBJ}
	${CC} ${CFLAG} ${OBJ} -o ${PROG}

main.o: ./main.c
	${CC} ${CFLAG} -c ./main.c

labyrinthe.o: ./fonctions/labyrinthe.c
	${CC} ${CFLAG} -c ./fonctions/labyrinthe.c

utilisateur.o: ./fonctions/utilisateur.c
	${CC} ${CFLAG} -c ./fonctions/utilisateur.c

deplacement.o: ./fonctions/deplacement.c
	${CC} ${CFLAG} -c ./fonctions/deplacement.c

depl1.o: ./fonctions/depl1.c
	${CC} ${CFLAG} -c ./fonctions/depl1.c

insecte.o: ./fonctions/insecte.c
	${CC} ${CFLAG} -c ./fonctions/insecte.c

#Supression des fichiers temporaires
clean:
	rm -f *.o
	rm -f ./fonctions/*.o
	rm -f ./header/*.gch

mrproper: clean
	rm -f VieLab.*
	rm -f VieLab
