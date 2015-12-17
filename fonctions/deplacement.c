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
#include "./../Boite_outils/Outil.h"

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
	printf("combat\n");
	if(fourmi[lab[x][y].insecte].sexe!=fourmi[lab[a][b].insecte].sexe){
		bebe(bouffe, dureevie, lab, fourmi);
		return 1;
	}
	else {
		if(fourmi[lab[x][y].insecte].age<fourmi[lab[a][b].insecte].age)
			deleteinsecte(lab, fourmi, x, y);
		else if(fourmi[lab[x][y].insecte].age>fourmi[lab[a][b].insecte].age)
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
	printf("decouvrir\n");
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
 * \brief	Détecte si un insecte est adjacent, si c'est le cas lance un combat.
 * 				Si il y a un combat on ne décrémente pas la vie de l'insecte c'est
 * 				sa récompense de victoire.
 * \param	px									La coordonnée x de l'insecte
 * \param	py									La coordonnée y de l'insecte
 * \param	lab									Récupère le labyrinthe
 * \param   bouffe									Reçoie la durée de vie de la bouffe en nombre de tour.
 * \param   dureevie							 	Reçoie la durée de vie en nombre de tour.
 * \param 	fourmi []								Reçoie le tableau de foumis.
 * \return  Renvoie 1 si il y a un insecte adjacent, 0 sinon
 */

int insecte_adjacent(int px, int py, t_lab lab[X][Y], int bouffe, int dureevie, t_fourmi fourmi[]) {
	printf("insecte_adjacent\n");
	if (lab[px-1][py].etat == insecte) {
		combat(px, py, px-1, py, bouffe, dureevie, lab, fourmi);
	} else if (lab[px][py-1].etat == insecte) {
	   combat(px, py, px, py-1, bouffe, dureevie, lab, fourmi);
	} else if (lab[px][py+1].etat == insecte) {
	   combat(px, py, px, py+1, bouffe, dureevie, lab, fourmi);
	} else if (lab[px+1][py].etat == insecte){
		combat(px, py, px+1, py, bouffe, dureevie, lab, fourmi);
	}
	else {
		return 0;
	}
	return 1;
}


/**
 * \brief	Opère un déplacement aléatoire
 * \param	pos_x									La coordonnée x d'origine
 * \param	pos_y									La coordonnée y d'origine
 * \param	lab										Récupère le labyrinthe
 * \param   bouffe									Reçoie la durée de vie de la bouffe en nombre de tour.
 * \param   dureevie							 	Reçoie la durée de vie en nombre de tour.
 * \param 	fourmi []								Reçoie le tableau de foumis.
 * \return	Retourne 0 si tout s'est bien déroulé, 1 sinon
 */

int prochain_deplacement (int pos_x, int pos_y, t_lab lab[X][Y], int bouffe, int dureevie, t_fourmi fourmi[]) {
	printf("prochain_deplacement\n");
	int ins_adj = insecte_adjacent(pos_x, pos_y, lab, bouffe, dureevie, fourmi);
	time_t t;
	srand((unsigned) time(&t));
	int random = rand()%100;

	if (lab[pos_x-1][pos_y].etat != mur || lab[pos_x][pos_y-1].etat != mur || lab[pos_x][pos_y+1].etat != mur || lab[pos_x+1][pos_y].etat != mur && ins_adj==0) {
		if (random >= 0 && random < 25 && lab[pos_x-1][pos_y].etat!=mur) {
			modifpos(lab, fourmi, pos_x, pos_y, pos_x-1, pos_y, bouffe, dureevie);
		}
		else if (random >= 25 && random < 50 && lab[pos_x][pos_y-1].etat!=mur) {
			modifpos(lab, fourmi, pos_x, pos_y, pos_x, pos_y-1, bouffe, dureevie);
		}
		else if (random >= 50 && random < 75 && lab[pos_x][pos_y+1].etat!=mur) {
			modifpos(lab, fourmi, pos_x, pos_y, pos_x, pos_y+1, bouffe, dureevie);
		}
		else if (random >= 75 && random < 100 && lab[pos_x+1][pos_y].etat!=mur) {
			modifpos(lab, fourmi, pos_x, pos_y, pos_x+1, pos_y, bouffe, dureevie);
		}
	} else {
		printf("erreur prochain_deplacement\n");
		return 1;
	}
	return 0;
}

int nourriture_pres(t_lab lab[X][Y]){
	int i, j;
	for(i=0; i<X; i++) {
		for(j=0; j<Y; j++) {
			if(lab[i][j].etat=food)
				return 1;
		}
	}
	return 0;
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
	printf("deplacement\n");
	int i, j, xdir, ydir, dist;
	int ins_adj = insecte_adjacent(pos_x, pos_y, lab, bouffe, dureevie, fourmi);
	if(ins_adj==0) {
		int nb_nourr = 0;
		typedef struct {int dist; int x; int y;} nourr;
		nourr plusproche;
		nourr interet[50];
		for (i=0; i<X; i++) {									/*on parcourt la matrice pour trouver toutes les cases de nourriture ou les insectes proches*/
			for (j=0; j<Y; j++) {
				if (lab[i][j].etat==food){
					dist=pluscourte_dist(lab, pos_x, pos_y, i, j, &xdir, &ydir);
					if(dist<20) {
						interet[nb_nourr].dist=dist;
						interet[nb_nourr].x=xdir;
						interet[nb_nourr].y=ydir;
						nb_nourr++;
					}
				}
			}
		}
		plusproche=interet[0];
		for (i=1; i<nb_nourr; i++){									/*on parcourt le tableau pour trouver la nourriture la plus proche*/
			if (interet[i].dist<plusproche.dist){
				plusproche=interet[i];
			}
		}
		if (nourriture_pres(lab) && pluscourte_dist(lab, pos_x, pos_y, plusproche.x, plusproche.y, &xdir, &ydir)<20) {
			modifpos(lab, fourmi, pos_x, pos_y, plusproche.x, plusproche.y, bouffe, dureevie);
		} else {
			prochain_deplacement(pos_x, pos_y, lab, bouffe, dureevie, fourmi);
		}
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
	printf("pluscourte_dist\n");
	int matr_dist[X][Y];
	int i, j;
	int xcur, ycur;
	int dist = 0;
	int parcouru=0;
	for(i=0; i<X; i++){				/*initialisation de la matrice*/
		for(j=0; j<Y; j++){
			matr_dist[i][j]=-2;
		}
	}
	matr_dist[xdep][ydep]=0;
	printf("matrice initialisée\n");
	while (parcouru==0){
		dist++;
		parcouru=1;
		for (i=0; i<X; i++){
			for(j=0; j<Y; j++){
				if (labyrinthe[i][j].etat==mur){
					matr_dist[i][j]=-1;
				}
				if (i==xdep && j==ydep && dist==1) {		/*si on est au début, on fixe la distance à 0*/
					if (matr_dist[i-1][j]==-2){
						matr_dist[i-1][j]=dist;
					}if (matr_dist[i][j-1]==-2){
						matr_dist[i][j-1]=dist;
					}if (matr_dist[i][j+1]==-2){
						matr_dist[i][j+1]=dist;
					}if (matr_dist[i+1][j]==-2) {
						matr_dist[i+1][j]=dist;
					}
				} else if (matr_dist[i][j]==dist-1 && dist>1){		/*sinon on indique la distance en cercles concentriques*/
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
				if (matr_dist[i][j]==-2){							/*si on a parcouru toute la matrice, on sort de la boucle*/
					parcouru=0;
				}
			}
		}
	}
	printf("matrice remplie\n");
	xcur = xarr; ycur=yarr;
	i = 0;
	while(matr_dist[xcur][ycur] != 1 && i<100){								/*On parcourt le chemin en sens inverse pour trouver le prochain déplacement*/
		Assert2("while incorrect", matr_dist[xcur][ycur]!=1, i<100);
		if(coord_correctes(xcur-1,ycur) && (matr_dist[xcur-1][ycur] == matr_dist[xcur][ycur]-1)){
			Assert2("x1 incorrect", coord_correctes(xcur-1,ycur), (matr_dist[xcur-1][ycur]==matr_dist[xcur][ycur]-1));
			xcur--;
		}else if(coord_correctes(xcur+1,ycur) && (matr_dist[xcur+1][ycur] == matr_dist[xcur][ycur]-1)){
			Assert2("x2 incorrect", coord_correctes(xcur+1,ycur), (matr_dist[xcur+1][ycur]==matr_dist[xcur][ycur]-1));
			xcur++;
		}else if(coord_correctes(xcur,ycur-1) && (matr_dist[xcur][ycur-1] == matr_dist[xcur][ycur]-1)){
			Assert2("x3 incorrect", coord_correctes(xcur,ycur-1), (matr_dist[xcur][ycur-1]==matr_dist[xcur][ycur]-1));
			ycur--;
		}else if(coord_correctes(xcur,ycur+1) && (matr_dist[xcur][ycur+1] == matr_dist[xcur][ycur]-1)){
			Assert2("x4 incorrect", coord_correctes(xcur,ycur+1), (matr_dist[xcur][ycur+1]==matr_dist[xcur][ycur]-1));
			ycur++;
		}
		i++;
		/*if(i>20){
			break;
		}*/
	}
	printf("while fini\n");
	*xdir = xcur; *ydir=ycur;
	return matr_dist[xarr][yarr];
}
