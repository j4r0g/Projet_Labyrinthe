PROG = VieLab
CC = gcc
CFLAG = -g -Wall
OBJ = ./fonctions/labyrinthe.o  main.o

${PROG} : ${OBJ} 
	${CC} ${CFLAG} ${OBJ} -o ${PROG} -lm

main.o : main.c 
	${CC} ${CFLAG} -c main.c

labyrinthe.o : ./fonctions/labyrinthe.c
	${CC} ${CFLAG} -c ./fonctions/labyrinthe.c

#Supression des fichiers temporaires
clean
	rm -i ./fonctions/*.o