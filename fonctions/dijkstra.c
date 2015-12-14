#include <stdio.h>
#include <stdlib.h>
#include "./../header/struct_lab.h"
#include "./../header/struct_ins.h"
#include "./../header/deplacement.h"

/*
#define INFINI 10000
#define X 30
#define Y 60

typedef enum {MALE, FEMELLE} t_sexe;
typedef struct {t_sexe sexe; int nourriture; int age;} t_fourmi;

typedef enum {haut = 0, bas = 1, gauche = 2, droite = 3} t_direction;
typedef enum {unseen=0, seen=1} t_discover;
typedef enum {vide=' ', mur='#', food='*', insecte='%'} t_etat;

typedef struct {t_discover decouvert; t_etat etat; int insecte;} t_lab;


typedef struct noeud {t_noeud * pred; int dist_dep; int ponderation; int parcouru;}t_noeud;
t_noeud matr_dest[X][Y];

void dijkstra(t_lab labyrinthe, int xdep, int ydep) {
	int i, j;
	for (i=0; i<X; i++){
		for(j=0; j<Y; j++) {
			if(labyrinthe[i][j].etat==mur) {
				matr_dest[i][j].dist_dep=INFINI;
				matr_dest[i][j]->pred=NULL;
				matr_dest[i][j].ponderation=-1;
				matr_dest[i][j].
			} else if (labyrinthe[i][j]==food) {
				if (i-xdep>0 && j-ydep>0) {
					matr_dest[i][j].dist_dep=(i-xdep)+(j-ydep);
				} else if (i-xdep <0 && j-ydep<0) {
					matr_dest[i][j].dist_dep=(xdep-i)+(ydep-j);
				} else if (i-xdep>0 && j-ydep<0) {
					matr_dest[i][j].dist_dep=(i-xdep)+(ydep-j);
				} else if (i-xdep<0 && j-ydep>0) {
					matr_dest[i][j].dist_dep=(xdep-i)+(j-ydep);
				}
				matr_dest[i][j].ponderation=10;
				matr_dest[i][j].parcouru=1;
}
*/

void deplacement (t_lab lab[X][Y], int pos_x, int pos_y) {
	int i, j;
	int nb_nourr = 0;
	typedef struct {int dist; int x; int y;} nourr;
	nourr plusproche;
	nourr manger[15];
	for (i=0; i<X; i++) {
		for (j=0; j<Y; j++) {
			if (lab[i][j].etat==food){
				manger[nb_nourr].dist=pluscourte_dist(lab, pos_x, pos_y, i, j);
				manger[nb_nourr].x=i;
				manger[nb_nourr].y=j;
				nb_nourr++;
			}
		}
	}
	plusproche=manger[0];
	for (i=1; i<15; i++){
		if (manger[i-1].dist<manger[i].dist){
			plusproche=manger[i-1];
		}
	}
	if ((plusproche.x - pos_x) < 0 && (plusproche.y - pos_y) < 0) {
		//deplacement au nord (nord ouest)
		lab[pos_x-1][pos_y].etat = insecte;
		lab[pos_x][pos_y].etat = vide;
		lab[pos_x-1][pos_y].insecte = lab[pos_x][pos_y].insecte;
		lab[pos_x][pos_y].insecte = -1;
	} else if ((plusproche.x - pos_x) > 0 && (plusproche.y - pos_y) < 0) {
		//deplacement a l'ouest (sud ouest)
		lab[pos_x][pos_y-1].etat = insecte;
		lab[pos_x][pos_y].etat = vide;
		lab[pos_x][pos_y-1].insecte = lab[pos_x][pos_y].insecte;
		lab[pos_x][pos_y].insecte = -1;
	} else if ((plusproche.x - pos_x) > 0 && (plusproche.y - pos_y) > 0) {
		//deplacement au sud (sud est)
		lab[pos_x+1][pos_y].etat = insecte;
		lab[pos_x][pos_y].etat = vide;
		lab[pos_x+1][pos_y].insecte = lab[pos_x][pos_y].insecte;
		lab[pos_x][pos_y].insecte = -1;
	} else if ((plusproche.x - pos_x) < 0 && (plusproche.y - pos_y) > 0) {
		//deplacement a l'est (nord est)
		lab[pos_x][pos_y+1].etat = insecte;
		lab[pos_x][pos_y].etat = vide;
		lab[pos_x][pos_y+1].insecte = lab[pos_x][pos_y].insecte;
		lab[pos_x][pos_y].insecte = -1;
	} else {
		printf("Erreur lors du déplacement\n");
	}
}


int pluscourte_dist(t_lab labyrinthe[X][Y], int xdep, int ydep, int xarr, int yarr)  {
	int matr_dist[X][Y];
	int i, j;
	int dist = 0;
	int parcouru=0;
	for(i=0; i<X; i++){
		for(j=0; j<Y; j++){
			matr_dist[i][j]=0;
		}
	}
	matr_dist[xdep][ydep]=-1;
	while (parcouru==0){
		dist++;
		parcouru=1;
		for (i=0; i<X; i++){
			for(j=0; j<Y; j++){
				if (labyrinthe[i][j].etat==mur){
					matr_dist[i][j]=-1;
				}
				if (i==xdep && j==ydep && dist==1) {
					if (matr_dist[i-1][j]==0){
						matr_dist[i-1][j]=dist;
					}if (matr_dist[i][j-1]==0){
						matr_dist[i][j-1]=dist;
					}if (matr_dist[i][j+1]==0){
						matr_dist[i][j+1]=dist;
					}if (matr_dist[i+1][j]==0) {
						matr_dist[i+1][j]=dist;
					}
				} else if (matr_dist[i][j]==dist-1 && dist>1){
					if (matr_dist[i-1][j]==0 && i-1>=0){
						matr_dist[i-1][j]=dist;
					}if (matr_dist[i][j-1]==0 && j-1>=0){
						matr_dist[i][j-1]=dist;
					}if (matr_dist[i][j+1]==0 && j+1<Y){
						matr_dist[i][j+1]=dist;
					}if (matr_dist[i+1][j]==0 && i+1<X) {
						matr_dist[i+1][j]=dist;
					}
				}
				if (matr_dist[i][j]==0){
					parcouru=0;
				}
			}
		}
	}
	return matr_dist[xarr][yarr];
}
