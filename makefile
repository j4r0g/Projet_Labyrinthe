PROG = VieLab
CC = gcc -I-

${PROG} : main.o labyrinthe.o 
	${CC} ./fonctions/labyrinthe.o  main.o -o ${PROG} -lm

main.o : main.c 
	${CC} -c main.c  -Wall

labyrinthe.o : labyrinthe.c
	${CC} -c ./fonctions/labyrinthe.c -Wall

#Supression des fichiers temporaires



