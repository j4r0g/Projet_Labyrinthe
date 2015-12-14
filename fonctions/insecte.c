/**
 * \file 			insecte.c
 * \author    Boisson Léo, Bussereau Keryann, Ciron Fabien
 * \version   1.0
 * \date      14 décembre 2015
 * \brief     Gère les insectes
 * \details
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./../header/struct_lab.h"
#include "./../header/struct_ins.h"

//t_fourmi fourmi[40];

/**
 * \brief      Génère aléatoirement un insecte dans une case vide du labyrinthe mais qui doit être découverte.
 * \param   bouffe						Reçoie la durée de vie de la bouffe en nombre de tour.
 * \param   dureevie         	Reçoie la durée de vie en nombre de tour.
 * \param 	lab[x][Y] 				Reçoie le labyrinthe de taille X, Y.
 * \param 	fourmi[] 					Reçoie le tableau d'insectes.
 * \param 	nb_ins 						Reçoie le nombre d'insectes du labyrinthe.
 * \param   a                 Reçoie l'emplacement x où doit être placé l'insecte
 * \param   b                 Reçoie l'emplacement y où doit être placé l'insecte
 * \return  Un 1 si on ne peut pas ajouter l'insecte à la case demandée, 0 si on peut.
 */
int gene_ins(int bouffe, int dureevie, t_lab lab[X][Y], t_fourmi fourmi[], int nb_ins, int a, int b) {
	srand(time(NULL));
  if(a<=0 || a>=X || b<=0 || b>=Y || lab[a][b].etat!=vide)
    return 1;
  else {
    lab[a][b].etat=insecte;
  	nb_ins++;
  	lab[a][b].insecte=nb_ins;
  	int sexe=rand()%100;
  	if(sexe>=0 && sexe<50)
  		fourmi[lab[a][b].insecte].sexe = MALE;
  	else
  		fourmi[lab[a][b].insecte].sexe = FEMELLE;

  	fourmi[lab[a][b].insecte].nourriture = bouffe;
  	fourmi[lab[a][b].insecte].age = dureevie;
  }
  return 0;
}

/**
 * \brief   Génère aléatoirement un insecte dans une case vide du labyrinthe et qui n'a pas besoin d'être dévouverte.
 * \param   bouffe						Reçoie la durée de vie de la bouffe en nombre de tour.
 * \param   dureevie         	Reçoie la durée de vie en nombre de tour.
 * \param 	lab[x][Y] 				Reçoie le labyrinthe de taille X, Y.
 * \param 	fourmi[] 					Reçoie le tableau d'insectes.
 * \param 	nb_ins 						Reçoie le nombre d'insectes du labyrinthe.
 */
void gene_ins_deb(int bouffe, int dureevie, t_lab lab[X][Y], t_fourmi fourmi[]) {
	int nbre;
	for(nbre=0;nbre<10;nbre++) {
		srand(time(NULL));
		int nombrex, nombrey, sexe;
		nombrex = rand()%X;
		nombrey = rand()%Y;
		while(lab[nombrex][nombrey].etat!=vide){
			nombrex = rand()%X;
			nombrey = rand()%Y;
		}
		gene_ins(bouffe, dureevie, lab, fourmi, nbre, nombrex, nombrey);
	}
}

/**
 * \brief      Génère aléatoirement un insecte dans une case vide du labyrinthe mais qui doit être découverte.
 * \param   bouffe						Reçoie la durée de vie de la bouffe en nombre de tour.
 * \param   dureevie         	Reçoie la durée de vie en nombre de tour.
 * \param 	lab[x][Y] 				Reçoie le labyrinthe de taille X, Y.
 * \param 	fourmi[] 					Reçoie le tableau d'insectes.
 * \param 	nb_ins 						Reçoie le nombre d'insectes du labyrinthe.
 */
void bebe(int bouffe, int dureevie, t_lab lab[X][Y], t_fourmi fourmi[], int nb_ins) {
	srand(time(NULL));
	int nombrex, nombrey;
	nombrex = rand()%X;
	nombrey = rand()%Y;
	while(lab[nombrex][nombrey].etat!=vide && lab[nombrex][nombrey].decouvert!=seen){
		nombrex = rand()%X;
		nombrey = rand()%Y;
	}
	gene_ins(bouffe, dureevie, lab, fourmi, nb_ins, nombrex, nombrey);
}
