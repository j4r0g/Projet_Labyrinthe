#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define X 30 //Définit la taille du labyrinthe
#define Y 60

typedef enum {MALE, FEMELLE} t_sexe;
typedef struct {t_sexe sexe; int nourriture; int age;} t_fourmi;

typedef enum {haut = 0, bas = 1, gauche = 2, droite = 3} t_direction;
typedef enum {unseen=0, seen=1} t_discover;
typedef enum {vide=' ', mur='#', food='*', insecte='%'} t_etat;

typedef struct {t_discover decouvert; t_etat etat; int insecte;} t_lab;

void gene_deb(int bouffe, int dureevie, t_lab lab[X][Y], int i, t_fourmi fourmi[]) {
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
