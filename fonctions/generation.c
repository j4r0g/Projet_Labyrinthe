#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./../header/struct.h"

void gene_ins(int bouffe, int dureevie, t_lab lab[X][Y], int i, t_fourmi fourmi[]) {
	srand(time(NULL));
	int nombrex, nombrey, sexe;
	nombrex = rand()%X;
	nombrey = rand()%Y;
	while(lab[nombrex][nombrey].etat!=vide){
		nombrex = rand()%X;
		nombrey = rand()%Y;
	}
	lab[nombrex][nombrey].etat=insecte;
  lab[nombrex][nombrey].insecte=i;
  sexe=rand()%100;
	if(sexe>=0 && sexe<50)
		fourmi[lab[nombrex][nombrey].insecte].sexe = MALE;
	else
		fourmi[lab[nombrex][nombrey].insecte].sexe = FEMELLE;

	fourmi[lab[nombrex][nombrey].insecte].nourriture = bouffe;
	fourmi[lab[nombrex][nombrey].insecte].age = dureevie;
}

void gene_nour(t_lab lab[X][Y]) {
	srand(time(NULL));
	int nombrex, nombrey;
	nombrex = rand()%X;
	nombrey = rand()%Y;
	while(lab[nombrex][nombrey].etat!=vide){
		nombrex = rand()%X;
		nombrey = rand()%Y;
	}
	lab[nombrex][nombrey].etat=food;
}
