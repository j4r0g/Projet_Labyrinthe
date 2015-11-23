#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum t_sexe {MALE, FEMELLE};
typedef struct {t_sexe sexe; int nourriture; int age;} t_fourmi[];

int insecte_adjacent(int px, int py) {
	if (lab[px-1][py].etat == insecte) {
		return 1;
	} else if (lab[px][py-1].etat == insecte) {
	   return 2;
	} else if (lab[px][py+1].etat == insecte) {
	   return 3;
	} else if (lab[px+1][py].etat == insecte){
		return 4;
	}
	return 0;
}

void prochain_deplacement (int num_fourmi, int pos_x, int pos_y) {
	int ins_adj = insecte_adjacent();
	time_t t;
	srand((unsigned) time(&t));
	int random = rand()%100;

	if (ins_adj == 1) {
		combat(pos_x, pos_y, pos_x-1, pos_y);
	} else if (ins_adj == 2) {
		combat(pos_x, pos_y, pos_x, pos_y-1);
	} else if (ins_adj == 3) {
		combat(pos_x, pos_y, pos_x, pos_y+1);
	} else if (ins_adj == 4) {
		combat(pos_x, pos_y, pos_x+1, pos_y);
	} else {
		if (random >= 0 && random < 25) {
			lab[pos_x-1][pos_y].etat = 3;
			lab[pos_x][pos_y].etat = 0;
			lab[pos_x-1][pos_y].insecte = lab[pos_x][pos_y].insecte;
			lab[pos_x][pos_y].insecte = 0;
		} else if (random >= 25 && random < 50) {
			lab[pos_x][pos_y-1].etat = 3;
			lab[pos_x][pos_y].etat = 0;
			lab[pos_x][pos_y-1].insecte = lab[pos_x][pos_y].insecte;
			lab[pos_x][pos_y].insecte = 0;
		} else if (random >= 50 && random < 75) {
			lab[pos_x][pos_y+1].etat = 3;
			lab[pos_x][pos_y].etat = 0;
			lab[pos_x][pos_y+1].insecte = lab[pos_x][pos_y].insecte;
			lab[pos_x][pos_y].insecte = 0;
		} else if (random >= 75 && random < 100) {
			lab[pos_x+1][pos_y].etat = 3;
			lab[pos_x][pos_y].etat = 0;
			lab[pos_x+1][pos_y].insecte = lab[pos_x][pos_y].insecte;
			lab[pos_x][pos_y].insecte = 0;
		}
	}
}
