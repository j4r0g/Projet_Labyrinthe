PROG= VieLab
CC=gcc
CFLAG= -g -Wall
OBJ= ./fonctions/labyrinthe.o ./main.o ./fonctions/utilisateur.o ./fonctions/generation.o ./fonctions/deplacement.c ./fonctions/dijkstra.o ./fonctions/fourmis.c

all: ${PROG}

${PROG}: ${OBJ}
	${CC} ${CFLAG} ${OBJ} -o ${PROG}

main.o: ./main.c
	${CC} ${CFLAG} -c ./main.c

labyrinthe.o: ./fonctions/labyrinthe.c
	${CC} ${CFLAG} -c ./fonctions/labyrinthe.c

utilisateur.o: ./fonctions/utilisateur.c
	${CC} ${CFLAG} -c ./fonctions/utilisateur.c

generation.o: ./fonctions/generation.c
	${CC} ${CFLAG} -c ./fonctions/generation.c

deplacement.o: ./fonctions/deplacement.c
	${CC} ${CFLAG} -c ./fonctions/deplacement.c

dijkstra.o: ./fonctions/dijkstra.c
	${CC} ${CFLAG} -c ./fonctions/dijkstra.c

fourmis.o: ./fonctions/fourmis.c
	${CC} ${CFLAG} -c ./fonctions/fourmis.c

#Supression des fichiers temporaires
clean:
	rm -f *.o
	rm -f ./fonctions/*.o
	rm -f ./header/*.gch

mrproper: clean
	rm -f VieLab.*
	rm -f VieLab
