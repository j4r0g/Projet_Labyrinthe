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

/**
 * \brief	Fait se déplacer les insectes
 * \param	lab									Récupère le labyrinthe
 * \param	pos_x								La coordonnée x de l'insecte
 * \param	pos_y								La coordonnée y de l'insecte
 * \param	fourmi								Récupère le tableau de fourmis
 * \param	bouffe								La durée de vie en nombre de tours avant la mort par inanition
 * \param	dureevie							La durée de vie en âge avant la mort
 */

void deplacement (t_lab lab[X][Y], int pos_x, int pos_y, t_fourmi fourmi[], int bouffe, int dureevie) {
	int i, j, xdir, ydir;
	int nb_nourr = 0;
	typedef struct {int dist; int x; int y;} nourr;
	nourr plusproche;
	nourr interet[15];
	for (i=0; i<X; i++) {									//on parcourt la matrice pour trouver toutes les cases de nourriture ou les insectes proches
		for (j=0; j<Y; j++) {
			if (lab[i][j].etat==food && (pluscourte_dist(lab, pos_x, pos_y, i, j, &xdir, &ydir)<30)){
				interet[nb_nourr].dist=pluscourte_dist(lab, pos_x, pos_y, i, j, &xdir, &ydir);
				interet[nb_nourr].x=xdir;
				interet[nb_nourr].y=ydir;
				nb_nourr++;
			} /*else if (lab[i][j].etat==insecte && (pluscourte_dist(lab, pos_x, pos_y, i, j, &xdir, &ydir)<30)) {
				interet[nb_nourr].dist=pluscourte_dist(lab, pos_x, pos_y, i, j, &xdir, &ydir);
				interet[nb_nourr].x=xdir;
				interet[nb_nourr].y=ydir;
				nb_nourr++;
			}*/
		}
	}
	plusproche=interet[0];
	for (i=1; i<nb_nourr; i++){									//on parcourt le tableau pour trouver la nourriture la plus proche
		if (interet[i].dist<plusproche.dist){
			plusproche=interet[i];
		}
	}
	if (lab[pos_x-1][pos_y].etat==insecte) {
		combat(pos_x, pos_y, pos_x-1, pos_y, bouffe, dureevie, lab, fourmi);
	} else if (lab[pos_x][pos_y-1].etat==insecte ) {
		combat(pos_x, pos_y, pos_x, pos_y-1, bouffe, dureevie, lab, fourmi);
	} else if (lab[pos_x+1][pos_y].etat==insecte){
		combat(pos_x, pos_y, pos_x+1, pos_y, bouffe, dureevie, lab, fourmi);
	} else if (lab[pos_x][pos_y+1].etat==insecte) {
		combat(pos_x, pos_y, pos_x, pos_y+1, bouffe, dureevie, lab, fourmi);
	}
	if (pluscourte_dist(lab, pos_x, pos_y, plusproche.x, plusproche.y, &xdir, &ydir)<30) {
		modifpos(lab, fourmi, pos_x, pos_y, plusproche.x, plusproche.y, bouffe, dureevie);
	} else {
		prochain_deplacement(pos_x, pos_y, lab, bouffe, dureevie, fourmi);
	}
}

/**
 * \brief	Calcule la matrice des distances
 * \param	labyrinthe								Récupère le labyrinthe
 * \param	xdep									La coordonnée x du point d'origine
 * \param	ydep									La coordonnée y du point d'origine
 * \param	xarr									La coordonnée x d'arrivée
 * \param	yarr									La coordonnée y d'arrivée
 * \param	*xdir									La coordonnée x du prochain déplacement
 * \param	*ydir									La coordonnée y du prochain déplacement
 * \return	La distance de la nourriture la plus proche
 */

int pluscourte_dist(t_lab labyrinthe[X][Y], int xdep, int ydep, int xarr, int yarr, int* xdir, int *ydir)  {
	int matr_dist[X][Y];
	int i, j;
	int xcur, ycur;
	int dist = 0;
	int parcouru=0;
	for(i=0; i<X; i++){				//initialisation de la matrice
		for(j=0; j<Y; j++){
			matr_dist[i][j]=-2;
		}
	}
	matr_dist[xdep][ydep]=0;
	while (parcouru==0){
		dist++;
		parcouru=1;
		for (i=0; i<X; i++){
			for(j=0; j<Y; j++){
				if (labyrinthe[i][j].etat==mur){
					matr_dist[i][j]=-1;
				}
				if (i==xdep && j==ydep && dist==1) {		//si on est au début, on fixe la distance à 0
					if (matr_dist[i-1][j]==-2){
						matr_dist[i-1][j]=dist;
					}if (matr_dist[i][j-1]==-2){
						matr_dist[i][j-1]=dist;
					}if (matr_dist[i][j+1]==-2){
						matr_dist[i][j+1]=dist;
					}if (matr_dist[i+1][j]==-2) {
						matr_dist[i+1][j]=dist;
					}
				} else if (matr_dist[i][j]==dist-1 && dist>1){		//sinon on indique la distance en cercles concentriques
					if (matr_dist[i-1][j]==-2 && i-1>=0){
						matr_dist[i-1][j]=dist;
					}if (matr_dist[i][j-1]==-2 && j-1>=0){
						matr_dist[i][j-1]=dist;
					}if (matr_dist[i][j+1]==-2 && j+1<Y){
						matr_dist[i][j+1]=dist;
					}if (matr_dist[i+1][j]==-2 && i+1<X) {
						matr_dist[i+1][j]=dist;
					}
				}
				if (matr_dist[i][j]==-2){							//si on a parcouru toute la matrice, on sort de la boucle
					parcouru=0;
				}
			}
		}
	}
	xcur = xarr; ycur=yarr;
	i = 0;
	while(matr_dist[xcur][ycur] != 1){
		if(coord_correctes(xcur-1,ycur) && (matr_dist[xcur-1][ycur] == matr_dist[xcur][ycur]-1)){
			xcur--;
		}else if(coord_correctes(xcur+1,ycur) && (matr_dist[xcur+1][ycur] == matr_dist[xcur][ycur]-1)){
			xcur++;
		}else if(coord_correctes(xcur,ycur-1) && (matr_dist[xcur][ycur-1] == matr_dist[xcur][ycur]-1)){
			ycur--;
		}else if(coord_correctes(xcur,ycur+1) && (matr_dist[xcur][ycur+1] == matr_dist[xcur][ycur]-1)){
			ycur++;
		}
		i++;
		if(i>100) break;
	}
	*xdir = xcur; *ydir=ycur;
	return matr_dist[xarr][yarr];
}
