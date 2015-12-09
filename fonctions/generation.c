#include <stdio.h>
#include <stdlib.h>

typedef enum {MALE, FEMELLE} t_sexe;
typedef struct {t_sexe sexe; int nourriture; int age;} t_fourmi;
t_fourmi fourmi[];

typedef enum {unseen=0, seen=1} t_discover;
typedef enum {vide=0, mur=1, food=2, insecte=3} t_etat;
typedef struct {t_discover decouvert; t_etat etat; int insecte;} t_lab;

void gene_deb(int maxx, int maxy, int bouffe, int dureevie, t_lab lab[maxx][maxy]) {
	srand(time(NULL));
	int nombrex, nombrey, sexe;
	nombrex = rand()%maxx;
	nombrey = rand()%maxy;
	while(lab[nombrex][nombrey].etat!=vide){
		nombrex = rand()%maxx;
		nombrey = rand()%maxy;
	}
	lab[nombrex][nombrey].etat=insecte;
	sexe=rand()%100;
	if(sexe>=0 && sexe<50)
		fourmi[lab[nombrex][nombrey].insecte].sexe = MALE;
	else
		fourmi[lab[nombrex][nombrey].insecte].sexe = FEMELLE;

	fourmi[lab[nombrex][nombrey].insecte].nourriture = bouffe;
	fourmi[lab[nombrex][nombrey].insecte].age = dureevie;
}
