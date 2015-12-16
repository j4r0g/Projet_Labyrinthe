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

int nb_ins=0;

/**
 * \brief   Génère aléatoirement un insecte dans une case vide du labyrinthe mais qui doit être découverte.
 * \param   bouffe						Reçoie la durée de vie de la bouffe en nombre de tour.
 * \param   dureevie         	Reçoie la durée de vie en nombre de tour.
 * \param 	lab[x][Y] 				Reçoie le labyrinthe de taille X, Y.
 * \param   a                 Reçoie l'emplacement x où doit être placé l'insecte
 * \param   b                 Reçoie l'emplacement y où doit être placé l'insecte
 * \param 	fourmi [] 				Reçoie le tableau de foumis.
 * \return  Un 1 si on ne peut pas ajouter l'insecte à la case demandée, 0 si on peut.
 */
int gene_ins(int bouffe, int dureevie, t_lab lab[X][Y], int a, int b, t_fourmi fourmi[]) {
	srand(time(NULL));
  if(a<=0 || a>=X || b<=0 || b>=Y || lab[a][b].etat!=vide)
    return 1;
  else {
    lab[a][b].etat=insecte;
  	nb_ins++;
  	lab[a][b].insecte=nb_ins;
		int indice=lab[a][b].insecte;
  	int sexe=rand()%100;
  	if(sexe>=0 && sexe<50)
  		fourmi[indice].sexe = MALE;
  	else
  		fourmi[indice].sexe = FEMELLE;

  	fourmi[indice].nourriture = bouffe;
  	fourmi[indice].age = dureevie;
		fourmi[indice].x=a;
		fourmi[indice].y=b;
  }
  return 0;
}

/**
 * \brief   Génère aléatoirement un insecte dans une case vide du labyrinthe et qui n'a pas besoin d'être dévouverte.
 * \param   bouffe						Reçoie la durée de vie de la bouffe en nombre de tour.
 * \param   dureevie         	Reçoie la durée de vie en nombre de tour.
 * \param 	lab[x][Y] 				Reçoie le labyrinthe de taille X, Y.
 * \param 	fourmi [] 				Reçoie le tableau de foumis.
 */
void gene_ins_deb(int bouffe, int dureevie, t_lab lab[X][Y], t_fourmi fourmi[]) {
	int i;
	int nbr_ins_deb = 5;
	for(i=0;i<nbr_ins_deb;i++) {
		srand(time(NULL));
		int nombrex, nombrey, sexe;
		nombrex = rand()%X;
		nombrey = rand()%Y;
		while(lab[nombrex][nombrey].etat!=vide){
			nombrex = rand()%X;
			nombrey = rand()%Y;
		}
		gene_ins(bouffe, dureevie, lab, nombrex, nombrey, fourmi);
	}
}

/**
 * \brief      Génère aléatoirement un insecte dans une case vide du labyrinthe mais qui doit être découverte.
 * \param   bouffe						Reçoie la durée de vie de la bouffe en nombre de tour.
 * \param   dureevie         	Reçoie la durée de vie en nombre de tour.
 * \param 	lab[x][Y] 				Reçoie le labyrinthe de taille X, Y.
 * \param 	fourmi [] 				Reçoie le tableau de foumis.
 */
void bebe(int bouffe, int dureevie, t_lab lab[X][Y], t_fourmi fourmi[]) {
	srand(time(NULL));
	int nombrex, nombrey;
	nombrex = rand()%X;
	nombrey = rand()%Y;
	while(lab[nombrex][nombrey].etat!=vide && lab[nombrex][nombrey].decouvert!=seen){
		nombrex = rand()%X;
		nombrey = rand()%Y;
	}
	gene_ins(bouffe, dureevie, lab, nombrex, nombrey, fourmi);
}

/**
 * \brief   Génère un insecte dans une case vide du labyrinthe découverte
 *          à la demande de l'utilisateur.
 * \param 	lab[x][Y] 				Reçoie le labyrinthe de taille X, Y.
 * \param   bouffe						Reçoie la durée de vie de la bouffe en nombre de tour.
 * \param   dureevie         	Reçoie la durée de vie en nombre de tour.
 * \param 	fourmi [] 				Reçoie le tableau de foumis.
 * \return  Un 0 si aucun insecte n'est placé, un 1 sinon.
 */
int ajoutInsecte (t_lab lab[X][Y], int bouffe, int dureevie, t_fourmi fourmi[]) {
  int a, b;
  srand(time(NULL));
  int nombre = rand()%100;
  if(nombre<50){
    printf("Vous n'avez aucun insecte à placer");
    return 0;
  }
  else {
    printf("Vous pouvez placer un insecte\n");
    printf("Entrez les coordonnées x et y de l'insecte séparées par un espace : ");
    scanf("%i%i", &a, &b);
    while(a<=0 || a>=X || b<=0 || b>=Y || lab[a][b].etat!=vide || lab[a][b].decouvert!=seen){
      printf("Erreur, shame, recommencez\n");
      printf("Entrez les coordonnées x et y de l'insecte séparées par un espace : ");
      scanf("%i%i", &a, &b);
    }
    gene_ins(bouffe, dureevie, lab, a, b, fourmi);
  }
  return 1;
}

/**
 * \brief   Modifie la position d'un insecte ainsi que le temps qu'il lui reste à vivre.
 * \param 	lab[x][Y] 				Reçoie le labyrinthe de taille X, Y.
 * \param 	fourmi [] 				Reçoie le tableau de foumis.
 * \param 	a									emplacement de la fourmi en x
 * \param 	b									emplacement de la fourmi en y
 * \param 	a									emplacement à donner à la fourmi en x
 * \param 	b									emplacement à donner à la fourmi en y
 * \param   bouffe						Reçoie la durée de vie de la bouffe en nombre de tour.
 * \param   dureevie         	Reçoie la durée de vie en nombre de tour.
 * \return  Un 0 si la fonction s'est exécutée avec succès, 1 si erreur.
 */
int modifpos(t_lab lab[X][Y], t_fourmi fourmi[], int x, int y, int a, int b, int bouffe, int dureevie){
	if(a<=0 || a>=X || b<=0 || b>=Y || (lab[a][b].etat!=vide && lab[a][b].etat!=food) || lab[x][y].etat!=insecte)
    return 1;
	else{
		int indice=lab[x][y].insecte;
		// On décrémente la nourriture de l'insecte
		fourmi[indice].nourriture--;
		fourmi[indice].age--;
		// On vérifie si on va sur une case de nourriture
		if(lab[a][b].etat==food)
			fourmi[indice].nourriture=bouffe;

		if(fourmi[indice].nourriture!=0 && fourmi[indice].age!=0) {
			// modif de l'état de la case
			lab[a][b].etat=insecte;
			lab[x][y].etat=vide;
			// modif de l'indice de l'insecte dans la case
			lab[a][b].insecte=indice;
			lab[x][y].insecte=-1;
			// maj de la position de l'insecte
			fourmi[indice].x=a;
			fourmi[indice].y=b;
		}
		else {
			lab[x][y].etat=food;
			lab[x][y].insecte=-1;
		}
	}
	return 0;
}
