#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./../header/struct_lab.h"
#include "./../header/struct_ins.h"


// Y et Y représentent la taille du labyrinthe
void generation(int bouffe, int dureevie, t_lab lab[X][Y], t_fourmi fourmi[], int nb_ins) {
	srand(time(NULL));
	int nombrex, nombrey, sexe;
	nombrex = rand()%X;
	nombrey = rand()%Y;
	while(lab[nombrex][nombrey].etat!=vide && lab[nombrex][nombrey].decouvert!=seen){
		nombrex = rand()%X;
		nombrey = rand()%Y;
	}
	lab[nombrex][nombrey].etat=insecte;
	nb_ins++;
	lab[nombrex][nombrey].insecte=nb_ins;
	sexe=rand()%100;
	if(sexe>=0 && sexe<50)
		fourmi[lab[nombrex][nombrey].insecte].sexe = MALE;
	else
		fourmi[lab[nombrex][nombrey].insecte].sexe = FEMELLE;

	fourmi[lab[nombrex][nombrey].insecte].nourriture = bouffe;
	fourmi[lab[nombrex][nombrey].insecte].age = dureevie;
}

// x et y correspondent à l'emplacement de la première fourmi et a et b à l'emplacement de la deuxième
int combat(int x, int y, int a, int b, int bouffe, int dureevie, t_lab lab[X][Y], t_fourmi fourmi[], int nb_ins) {
	if(fourmi[lab[x][y].insecte].sexe!=fourmi[lab[a][b].insecte].sexe){
		generation(bouffe, dureevie, lab, fourmi, nb_ins);
		return 1;
	}
	else {
		if(fourmi[lab[x][y].insecte].age>fourmi[lab[a][b].insecte].age)
			lab[x][y].etat=food;
		else if(fourmi[lab[x][y].insecte].age<fourmi[lab[a][b].insecte].age)
			lab[a][b].etat=food;
		else if(fourmi[lab[x][y].insecte].age==fourmi[lab[a][b].insecte].age && fourmi[lab[x][y].insecte].nourriture>fourmi[lab[a][b].insecte].nourriture)
			lab[a][b].etat=food;
		else if(fourmi[lab[x][y].insecte].age==fourmi[lab[a][b].insecte].age && fourmi[lab[x][y].insecte].nourriture<fourmi[lab[a][b].insecte].nourriture)
			lab[x][y].etat=food;
		else
			lab[x][y].etat=food;
		return 0;
	}
}

// découverte du labyrinthe
void decouvrir(t_lab lab[X][Y]) {
  int i, j;
  for(i=0;i<X;i++) {
    for(j=0;j<Y;j++){
      if(lab[i][j].etat==insecte) {
          lab[i][j].decouvert=seen;
          /* Découverte suivant l'axe des x*/
          if(i+1<X)
            lab[i+1][j].decouvert=seen;
          if(i+2<X)
            lab[i+2][j].decouvert=seen;
          if(i-1>0)
            lab[i-1][j].decouvert=seen;
          if(i-2>0)
            lab[i-2][j].decouvert=seen;

          /*Découverte suivant l'axe des y*/
          if(j+1<Y)
            lab[i][j+1].decouvert=seen;
          if(j+2<Y)
            lab[i][j+2].decouvert=seen;
          if(i-1>0)
            lab[i][j-1].decouvert=seen;
          if(j-2>0)
            lab[i][j-2].decouvert=seen;

          /* Découverte dans les diagonales */
          if(i+1<X && j+1<Y)
            lab[i+1][j+1].decouvert=seen;
          if(i-1>0 && j-1>0)
            lab[i-1][j-1].decouvert=seen;
          if(i+1<X && j-1>0)
            lab[i+1][j-1].decouvert=seen;
          if(i-1>0 && j+1<Y)
            lab[i-1][j+1].decouvert=seen;
      }
      /* Découverte des cases de nourriture */
      else if(lab[i][j].etat==food) {
        lab[i][j].decouvert=seen;
      }
    }
  }
}
