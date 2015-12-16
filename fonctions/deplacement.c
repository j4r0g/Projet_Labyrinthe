/**
 * \file 			deplacement.c
 * \author    Boisson Léo, Bussereau Keryann, Ciron Fabien
 * \version   1.0
 * \date      14 décembre 2015
 * \brief     Gère les déplcement des fourmis
 * \details   Ce module à pour but de gérer les déplacements des fourmis.
 * 						ainsi que leurs actions lorsqu'elles croisent d'autres insectes
 * 						elle gère aussi les défloutage des cases.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./../header/struct_lab.h"
#include "./../header/struct_ins.h"
#include "./../header/deplacement.h"

/**
 * \brief   Gère la rencontre entre deux fourmis
 * \param 	x									Reçoie l'emplacement x du premier insecte.
 * \param 	y									Reçoie l'emplacement y du premier insecte.
 * \param 	a									Reçoie l'emplacement x du deuxième insecte.
 * \param 	b									Reçoie l'emplacement y du deuxième insecte.
 * \param   bouffe						Reçoie la durée de vie de la bouffe en nombre de tour.
 * \param   dureevie         	Reçoie la durée de vie en nombre de tour.
 * \param 	lab[x][Y] 				Reçoie le labyrinthe de taille X, Y.
 * \param 	fourmi [] 				Reçoie le tableau de foumis.
 * \return 	Un 1 si on a ajouté un insecte et un 0 sinon.
 */
int combat(int x, int y, int a, int b, int bouffe, int dureevie, t_lab lab[X][Y], t_fourmi fourmi[]) {
	if(fourmi[lab[x][y].insecte].sexe!=fourmi[lab[a][b].insecte].sexe){
		bebe(bouffe, dureevie, lab, fourmi);
		return 1;
	}
	else {
		if(fourmi[lab[x][y].insecte].age>fourmi[lab[a][b].insecte].age)
			deleteinsecte(lab, fourmi, x, y);
		else if(fourmi[lab[x][y].insecte].age<fourmi[lab[a][b].insecte].age)
			deleteinsecte(lab, fourmi, a, b);
		else if(fourmi[lab[x][y].insecte].age==fourmi[lab[a][b].insecte].age && fourmi[lab[x][y].insecte].nourriture>fourmi[lab[a][b].insecte].nourriture)
			deleteinsecte(lab, fourmi, a, b);
		else if(fourmi[lab[x][y].insecte].age==fourmi[lab[a][b].insecte].age && fourmi[lab[x][y].insecte].nourriture<fourmi[lab[a][b].insecte].nourriture)
			deleteinsecte(lab, fourmi, x, y);
		else
			deleteinsecte(lab, fourmi, x, y);
		return 0;
	}
}

/**
 * \brief   Gère la découverte de certaines case du labyrinthe
 * \param 	lab[x][Y] 				Reçoie le labyrinthe de taille X, Y.
 */
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
    }
  }
}
