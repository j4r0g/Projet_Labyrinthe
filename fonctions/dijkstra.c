/**
 * \file		dijkstra.c
 * \author		Boisson Léo, Bussereau Keryann, Ciron Fabien
 * \version		1.0
 * \date		15 décembre 2015
 * \brief		Gère les déplacements des fourmis
 * \details		Ce module gère les déplacements des fourmis grâce à une matrice
 *				des distances fourmis-nourriture qui permet de repérer ou la fourmi
 *				doit aller pour se rapprocher de les nourriture
 */


#include <stdio.h>
#include <stdlib.h>
#include "./../header/struct_lab.h"
#include "./../header/struct_ins.h"
#include "./../header/deplacement.h"
#include "./../header/labyrinthe.h"


void deplacement (t_lab lab[X][Y], int pos_x, int pos_y, t_fourmi fourmi[], int bouffe, int dureevie) {
	int i, j, xdir, ydir;
	int nb_nourr = 0;
	typedef struct {int dist; int x; int y;} nourr;
	nourr plusproche;
	nourr manger[15];
	for (i=0; i<X; i++) {									//on parcourt la matrice pour trouver toutes les cases de nourriture
		for (j=0; j<Y; j++) {
			if (lab[i][j].etat==food){
				manger[nb_nourr].dist=pluscourte_dist(lab, pos_x, pos_y, i, j, &xdir, &ydir);
				printf("%i", manger[nb_nourr].dist);
				manger[nb_nourr].x=xdir;
				manger[nb_nourr].y=ydir;
				nb_nourr++;
			}
		}
	}
	plusproche=manger[0];
	for (i=1; i<nb_nourr; i++){									//on parcourt le tableau pour trouver la nourriture la plus proche
		if (manger[i].dist<plusproche.dist){
			plusproche=manger[i];
		}
	}

	modifpos(lab, fourmi, pos_x, pos_y, plusproche.x, plusproche.y, bouffe, dureevie);
	/*if ((plusproche.x - pos_x) < 0 && (plusproche.y - pos_y) < 0 && lab[pos_x-1][pos_y].etat!=mur) {
		//deplacement au nord (nord ouest)
		modifpos(lab, fourmi, pos_x, pos_y, pos_x-1, pos_y);
	} else if ((plusproche.x - pos_x) > 0 && (plusproche.y - pos_y) < 0 && lab[pos_x][pos_y-1].etat!=mur) {
		//deplacement a l'ouest (sud ouest)
		modifpos(lab, fourmi, pos_x, pos_y, pos_x, pos_y-1);
	} else if ((plusproche.x - pos_x) > 0 && (plusproche.y - pos_y) > 0 && lab[pos_x+1][pos_y].etat!=mur) {
		//deplacement au sud (sud est)
		modifpos(lab, fourmi, pos_x, pos_y, pos_x+1, pos_y);
	} else if ((plusproche.x - pos_x) < 0 && (plusproche.y - pos_y) > 0 && lab[pos_x][pos_y+1].etat!=mur) {
		//deplacement a l'est (nord est)
		modifpos(lab, fourmi, pos_x, pos_y, pos_x, pos_y+1);
	} else {
		printf("Erreur lors du déplacement\n");
	}*/
}


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
//	matr_dist[xarr][yarr]='#'-'0';
	for (i=0; i<X; i++){
		for (j=0; j<Y; j++){
			printf("%2d ", matr_dist[i][j]);
		}
		printf("\n");
	}
	printf("%i %i\n\n", xarr, yarr);
	xcur = xarr; ycur=yarr;
	i = 0;
	while(matr_dist[xcur][ycur] != 1){
		printf("on est en %d %d/n", xcur, ycur);
		// chercher matr_dist[xcur][ycur]-1
		if(coord_correctes(xcur-1,ycur) && (matr_dist[xcur-1][ycur] == matr_dist[xcur][ycur]-1))
			xcur--;
		else if(coord_correctes(xcur+1,ycur) && (matr_dist[xcur+1][ycur] == matr_dist[xcur][ycur]-1))
			xcur++;
		else if(coord_correctes(xcur,ycur-1) && (matr_dist[xcur][ycur-1] == matr_dist[xcur][ycur]-1))
			ycur--;
		else if(coord_correctes(xcur,ycur+1) && (matr_dist[xcur][ycur+1] == matr_dist[xcur][ycur]-1))
			ycur++;
		i++;
		if(i>100) break;
	}
	printf("il faut se deplacer en %i %i\n\n", xcur, ycur);
	*xdir = xcur; *ydir=ycur;
	return matr_dist[xarr][yarr];
}
