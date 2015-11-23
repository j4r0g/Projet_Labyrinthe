#include <stdio.h>
#include <stdlib.h>

//typedef enum t_sexe {MALE, FEMELLE};
//typedef struct {enum t_sexe sexe; int nourriture; int age;} t_fourmi[];
//typedef enum {unseen=0, seen=1} t_discover;
//typedef enum {vide=0, mur=1, food=2, insecte=3} t_etat;
//typedef struct {t_discover decouvert; t_etat etat; int insecte;} t_lab;

void combat(int x, int y, int a, int b) {
	if(fourmi[lab[x][y].insecte].sexe!=fourmi[lab[a][b].insecte].sexe)

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