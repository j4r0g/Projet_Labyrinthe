#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum {MALE, FEMELLE} t_sexe;
typedef struct {t_sexe sexe; int nourriture; int age;} t_fourmi[];
typedef enum {unseen=0, seen=1} t_discover;
typedef enum {vide=0, mur=1, food=2, insecte=3} t_etat;
typedef struct {t_discover decouvert; t_etat etat; int insecte;} t_lab;

t_fourmi fourmi;

// maxx et maxy représentent la taille du labyrinthe
void generation(int maxx, int maxy, int bouffe, int dureevie, t_lab lab[maxx][maxy]) {
	srand(time(NULL));
	int nombrex, nombrey, sexe;
	nombrex = rand()%maxx;
	nombrey = rand()%maxy;
	while(lab[nombrex][nombrey].etat!=vide && lab[nombrex][nombrey].decouvert!=seen){
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

// x et y correspondent à l'emplacement de la première fourmi et a et b à l'emplacement de la deuxième
void combat(int x, int y, int a, int b, int maxx, int maxy, int bouffe, int dureevie, t_lab lab[maxx][maxy]) {
	if(fourmi[lab[x][y].insecte].sexe!=fourmi[lab[a][b].insecte].sexe)
		generation(maxx, maxy, bouffe, dureevie, lab);
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
	}
}
