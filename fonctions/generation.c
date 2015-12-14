/**
 * \file 			generation.c
 * \author    Boisson Léo, Bussereau Keryann, Ciron Fabien
 * \version   1.0
 * \date      14 décembre 2015
 * \brief     Gère la génération des insectes et nourritures au début du programme
 * \details   Ce module à pour but de générer un insecte de façon aléatoire dans le labyrinthe
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./../header/struct_lab.h"
#include "./../header/struct_ins.h"

/**
 * \brief   Génère aléatoirement un insecte dans une case vide du labyrinthe et qui n'a pas besoin d'être dévouverte.
 * \param   bouffe						Reçoie la durée de vie de la bouffe en nombre de tour.
 * \param   dureevie         	Reçoie la durée de vie en nombre de tour.
 * \param 	lab[x][Y] 				Reçoie le labyrinthe de taille X, Y.
 * \param 	fourmi[] 					Reçoie le tableau d'insectes.
 * \param 	nb_ins 						Reçoie le nombre d'insectes du labyrinthe.
 */
void gene_ins(int bouffe, int dureevie, t_lab lab[X][Y], t_fourmi fourmi[], int nb_ins) {
	srand(time(NULL));
	int nombrex, nombrey, sexe;
	nombrex = rand()%X;
	nombrey = rand()%Y;
	while(lab[nombrex][nombrey].etat!=vide){
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

/**
 * \brief   Génère aléatoirement de la nourriture dans une case
 * 					vide du labyrinthe et qui n'a pas besoin d'être dévouverte.
 * \param 	lab[x][Y] 				Reçoie le labyrinthe de taille X, Y.
 */

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
