#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./../header/struct_lab.h"
#include "./../header/struct_ins.h"
#include "./../header/deplacement.h"

int insecte_adjacent(int px, int py, t_lab lab[X][Y]) {
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

int prochain_deplacement (int pos_x, int pos_y, t_lab lab[X][Y], t_fourmi fourmi[], int bouffe, int dureevie, int nb_ins) {
	int ins_adj = insecte_adjacent(pos_x, pos_y, lab);
	int issue = 2;
	time_t t;
	srand((unsigned) time(&t));
	int random = rand()%100;

	if (ins_adj == 1) {
		issue=combat(pos_x, pos_y, pos_x-1, pos_y, bouffe, dureevie, lab, fourmi, nb_ins);
	}
	else if (ins_adj == 2) {
		issue=combat(pos_x, pos_y, pos_x, pos_y-1, bouffe, dureevie, lab, fourmi, nb_ins);
	}
	else if (ins_adj == 3) {
		issue=combat(pos_x, pos_y, pos_x, pos_y+1, bouffe, dureevie, lab, fourmi, nb_ins);
	}
	else if (ins_adj == 4) {
		issue=combat(pos_x, pos_y, pos_x+1, pos_y, bouffe, dureevie, lab, fourmi, nb_ins);
	}
	else if (lab[pos_x-1][pos_y].etat != mur && lab[pos_x][pos_y-1].etat != mur && lab[pos_x][pos_y+1].etat != mur && lab[pos_x+1][pos_y].etat != mur) {
		if (random >= 0 && random < 25 && lab[pos_x-1][pos_y].etat!=mur) {
			lab[pos_x-1][pos_y].etat = insecte;
			lab[pos_x][pos_y].etat = vide;
			lab[pos_x-1][pos_y].insecte = lab[pos_x][pos_y].insecte;
			lab[pos_x][pos_y].insecte = -1;
		}
		else if (random >= 25 && random < 50 && lab[pos_x][pos_y-1].etat!=mur) {
			lab[pos_x][pos_y-1].etat = insecte;
			lab[pos_x][pos_y].etat = vide;
			lab[pos_x][pos_y-1].insecte = lab[pos_x][pos_y].insecte;
			lab[pos_x][pos_y].insecte = -1;
		}
		else if (random >= 50 && random < 75 && lab[pos_x][pos_y+1].etat!=mur) {
			lab[pos_x][pos_y+1].etat = insecte;
			lab[pos_x][pos_y].etat = vide;
			lab[pos_x][pos_y+1].insecte = lab[pos_x][pos_y].insecte;
			lab[pos_x][pos_y].insecte = -1;
		}
		else if (random >= 75 && random < 100 && lab[pos_x+1][pos_y].etat!=mur) {
			lab[pos_x+1][pos_y].etat = insecte;
			lab[pos_x][pos_y].etat = vide;
			lab[pos_x+1][pos_y].insecte = lab[pos_x][pos_y].insecte;
			lab[pos_x][pos_y].insecte = -1;
		}
	}
	if(issue==1)
		return 1;
	else
		return 0;
}
