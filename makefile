PROG = VieLab
CC = gcc
CFLAGS = -g -Wall

${PROG} : main.o labyrinthe.o
	${CC} ${FLAGS} -c ./fonctions/labyrinthe.o main.o ${PROG}

main.o : main.c Outils.h
	${CC} *{FLAGS} main.c ./fonctions/Outils.h

labyrinthe.o : labyrinthe.c
	${CC} *{FLAGS} ./fonctions/labyrinthe.c

#Supression des fichiers temporaires
clean :
	rm -i *.o

mrproper : clean
	rm -i ${PROG}


