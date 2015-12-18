/**
 * \file	  labyrinthe.c
 * \author    Boisson Léo
 * \version   1.0
 * \date      14 décembre 2015
 * \brief     génère un labyrinthe aléatoire
 * \details   Ce module génère un labyrinthe de manière aléatoire.
 * 				Sa taille est définie dans struct_lab.h
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "./../header/struct_lab.h"
#include "./../header/struct_ins.h"
#include "./../header/labyrinthe.h"


/**
 * \brief   affiche les statistiques des fourmis
 * \param 	lab[x][Y] 				Reçoie le labyrinthe de taille X, Y.
 * \param 	fourmi [] 				Reçoie le tableau de foumis.
 */
void afficherstats(t_lab lab[X][Y], t_fourmi fourmi[]) {
	int nb_ins=nb_insecte();
	int i;
	char male[10] = "male";
	char femelle[10] = "femelle";
	char sexe[10];
	printf("\nIl y a actuellement %i insecte dans le labyrinthe\n", nb_ins);
	for(i=0;i<nb_ins;i++){
		if(fourmi[i].sexe==0){
			strcpy(sexe, male);
		}
		else {
			strcpy(sexe, femelle);
		}
		int nourriture=fourmi[i].nourriture;
		int age = fourmi[i].age;
		int x=fourmi[i].x;
		int y=fourmi[i].y;
		printf("La fourmi %i est de sexe %s à encore pour %i tours de nourriture et %i tours de vie, elle est en x=%i et y=%i.\n", i, sexe, nourriture, age, x, y);
	}
}



/**
 * \brief   renvoie un nombre aléatoire entre 0 et max
 * \param 	max									borne haute
 * \return 	Le nombre aléatoire compris entre 0 et max
 */
int nbr_rand(int max){
	int nombre;
	nombre = rand()%max;
	return nombre;
}



/**
 * \brief   Vérifie que la case dans laquelle on regarde fait bien partie de la matrice
 * \param 	i									coordonnée en X
 * \param 	j									coordonnée en Y
 * \return 	renvoie un 1 si la coordonnée fait bien partie de la matrice, 0 autrement
 */
int coord_correctes( int i, int j){
	return (i<(X-1) && i>0 && j<(Y-1) && j>0);
}



/**
 * \brief   Initialise la matrice a partir d'un fichier texte  (utilisé pour tester le jeu au tout début)
 * \param 	lab[x][Y] 				Reçoie le labyrinthe de taille X, Y.
 * \return 	Un 1 si on a ajouté un insecte et un 0 sinon.
 */
void init_lab(t_lab lab[X][Y]){
	int tmp;
	int i,j;
	FILE * fic1;
	fic1 = fopen("../doc/lab_test.txt", "r");

	while(!feof(fic1))
	{
		for(i =0; i<X; i++){
			for(j =0; j<Y; j++){
				fscanf(fic1, "%d ", &tmp);
				lab[i][j].etat = tmp;
				lab[i][j].decouvert = unseen;
			}
		}
	}
	fclose(fic1);
}



/**
 * \brief   Compte le nombre de cases vide
 * \param 	lab[x][Y] 				Reçoie le labyrinthe de taille X, Y.
 * \return 	Renvoie le nombre de cases vides dans le labyrinthe
 */
int nbr_cases_vide(t_lab lab[X][Y]){
	int i, j;
	int nbr_cases_vide = 0;
	for (i=0; i<X; i++){
		for (j=0; j<Y; j++){
			if(lab[i][j].etat == vide){
				nbr_cases_vide++;
			}
		}
	}
	return nbr_cases_vide;
}



/**
 * \brief   Cette fonction "lisse" les murs. (supprime les blocs de murs isolés)
 * \param 	lab[x][Y] 				Reçoie le labyrinthe de taille X, Y.
 * \return  Renvoit 1 si elle a effectué des modifications, 0 sinon
 */
int lissage_lab(t_lab lab[X][Y]){
	int i, j;
	int mur_adj=0;
	int a_lisse=0;
	for (i=0; i<X; i++){
		for (j=0; j<Y; j++){
			if(lab[i][j].etat == mur){
				mur_adj=0;

				if(lab[i][j-1].etat == vide){
					mur_adj++;
				}
				if(lab[i][j+1].etat == vide){
					mur_adj++;
				}
				if(lab[i-1][j].etat == vide){
					mur_adj++;
				}
				if(lab[i+1][j].etat == vide){
					mur_adj++;
				}
				if(mur_adj >= 3 ){
					lab[i][j].etat = vide;
					a_lisse=1;
				}

			}
		}
	}
	return a_lisse;
}



/**
 * \brief   Initialisation pseudo-aléatoire du labyrinthe	(1er essai, par "ilots")
 * \param 	lab[x][Y] 				Reçoie le labyrinthe de taille X, Y.
 */
/*void init_lab_rand (t_lab lab[X][Y]){
	int i,j, x, y, x_tmp, y_tmp, compteur_ilot, branche, rand_branche, a_lisse;
	int nbr_ilot=0;

	for(i =0; i<X; i++){		//Ce bloque place des murs tout autours du labyrinthe.
		for(j =0; j<Y; j++){
			if(i==0 || i==(X-1) || j==0 || j==(Y-1)){
				lab[i][j].etat = mur;
			}
			lab[i][j].decouvert = seen;		//Cette ligne initialise "discover" pour toutes les cases du labyrinthe (ici en "seen" pour tester, mais normalement "unseen"
		}
	}


	nbr_ilot = (nbr_rand()/10) + (X/5);			//Ce bloc là va créer les murs de manière aléatoire. Les "ilots" définissent des points sur lequels
	for(compteur_ilot=0; compteur_ilot<nbr_ilot; compteur_ilot++){ // une case est remplie avec un mur, puis les murs s'étendent de manière aléatoire depuis ce point.
		x = nbr_rand()/4;		//100 divisé par ... selon X et Y
		y = nbr_rand()/4;
		while( lab[x][y].etat != vide){		//Les ilots doivents être placés sur des emplacement vides
			x = nbr_rand()/5;
			y = nbr_rand()/5;
		}
		lab[x][y].etat = mur;

		for(i=-1; i<=1; i++){
			for(j=-1; j<=1; j++){		//Les "branches" sont les extensions des murs, qui vont dans toutes les directions
				x_tmp = x+i;
				y_tmp = y+j;
				branche = 1;
				while(branche == 1){
					if(lab[x_tmp][y_tmp].etat == mur){
						branche =0;
					}
					else{
						rand_branche = nbr_rand();
						if(rand_branche<40){
							lab[x_tmp][y_tmp].etat = mur;
							if(i<0){
								x_tmp--;
							}
							if(i>0){
								x_tmp++;
							}
							if(j<0){
								y_tmp--;
							}
							if(j>0){
								y_tmp++;
							}
						}
						else{
							branche = 0;
						}
					}
				}
			}
		}
		a_lisse = lissage_lab(lab);
		while(a_lisse !=0){
			a_lisse = lissage_lab(lab);
			printf("test\n");
		}
	}
}*/


/**
 * \brief   Initialisation pseudo-aléatoire du labyrinthe	(3eme essaie, de gauche a droite)
 * \param 	lab[x][Y] 				Reçoie le labyrinthe de taille X, Y.
 */
/*void init_lab_rand_2 (t_lab lab[X][Y]){
	int i, j, direction, i_tmp, j_tmp, a_lisse;
	int cases_extrude = 0;

	for(i =0; i<X; i++){		//Ce bloque place des murs partout
		for(j =0; j<Y; j++){
			lab[i][j].etat = mur;
			lab[i][j].decouvert = seen;		//Cette ligne initialise "discover" pour toutes les cases du labyrinthe (ici en "seen" pour tester, mais normalement "unseen"
		}
	}

	i = X/2;
	j = 1;
	while(j<(Y-2)){
		lab[i][j].etat = vide;
		direction = nbr_rand(100);
		if(direction >60){
			i_tmp = i;
			j_tmp = j+1;
			if(coord_correctes( i_tmp, j_tmp)){
				if(lab[i_tmp][j_tmp].etat == mur){
					lab[i_tmp][j_tmp].etat = vide;
					cases_extrude++;
				}
				j=j_tmp;
			}
		}
		else if(direction >35){
			i_tmp = i-1;
			j_tmp = j;
			if(coord_correctes( i_tmp, j_tmp)){
				if(lab[i_tmp][j_tmp].etat == mur){
					lab[i_tmp][j_tmp].etat = vide;
					cases_extrude++;
				}
				i = i_tmp;
			}
		}
		else if(direction > 10){
			i_tmp = i+1;
			j_tmp = j;
			if(coord_correctes( i_tmp, j_tmp)){
				if(lab[i_tmp][j_tmp].etat == mur){
					lab[i_tmp][j_tmp].etat = vide;
					cases_extrude++;
				}
				i = i_tmp;

			}
		}
		else {
			i_tmp = i;
			j_tmp = j-1;
			if(coord_correctes( i_tmp, j_tmp)){
				if(lab[i_tmp][j_tmp].etat == mur){
					lab[i_tmp][j_tmp].etat = vide;
					cases_extrude++;
				}
				j = j_tmp;
			}
		}


	}

	a_lisse = lissage_lab(lab);
	while(a_lisse){
		a_lisse = lissage_lab(lab);
		printf("test\n");
	}

	printf("gauche : %d\n", gauche);
	printf("droite : %d\n", droite);
	printf("haut : %d\n", haut);
	printf("bas : %d\n", bas);
}*/



/**
 * \brief   Initialisation pseudo-aléatoire du labyrinthe	(2nd essaie, par extrudage, en partant du centre)
 * \param 	lab[x][Y] 				Reçoie le labyrinthe de taille X, Y.
 */
void init_lab_rand (t_lab lab[X][Y]){
	srand(time(NULL));
	int i, j, direction, i_tmp, j_tmp, a_lisse;
	int cases_extrude = 0;
	int ite_gauche = 0;
	int ite_droite = 0;
	int orientation = 0;
	for(i =0; i<X; i++){		//Ce bloc place des murs partout
		for(j =0; j<Y; j++){
			lab[i][j].etat = mur;
			lab[i][j].insecte = -1;
			if(j==0 || i==0 || j==(Y-1) || i==(X-1)){
				lab[i][j].decouvert = seen;
			}
			else{
				lab[i][j].decouvert = unseen;		//Cette ligne initialise "discover" pour toutes les cases du labyrinthe (au début, rien n'est découvert)
			}
		}
	}
	i = X/2;
	j = Y/2;
	while(cases_extrude < (X*Y)/2){			//Ce while va "extruder" des cases avec des murs, tant que la moitié du labyrinthe n'as pas été extrudé.
		lab[i][j].etat = vide;
		direction = nbr_rand(100);

		if(direction > 75 + orientation){	//le "+orientation" sert a faire partir le curseur qui va extruder vers la droite ou la gauche, lorsqu'on le replace au centre
			i_tmp = i;
			j_tmp = j-1;
			if(coord_correctes( i_tmp, j_tmp)){
				if(lab[i_tmp][j_tmp].etat == mur){
					lab[i_tmp][j_tmp].etat = vide;
					cases_extrude++;
				}
				i = i_tmp;
				j = j_tmp;
			}
		}
		
		else if(direction >50){
			i_tmp = i;
			j_tmp = j+1;
			if(coord_correctes( i_tmp, j_tmp)){
				if(lab[i_tmp][j_tmp].etat == mur){
					lab[i_tmp][j_tmp].etat = vide;
					cases_extrude++;
				}
				i = i_tmp;
				j = j_tmp;
			}
		}
		
		else if(direction >25){					//Envoie vers le haut le curseur.
			i_tmp = i-1;
			j_tmp = j;
			if(coord_correctes( i_tmp, j_tmp)){
				if(lab[i_tmp][j_tmp].etat == mur){
					lab[i_tmp][j_tmp].etat = vide;
					cases_extrude++;
				}
				i = i_tmp;
				j = j_tmp;

			}
		}
		
		else{							//Envoie le curseur vers le bas
			i_tmp = i+1;
			j_tmp = j;
			if(coord_correctes( i_tmp, j_tmp)){
				if(lab[i_tmp][j_tmp].etat == mur){
					lab[i_tmp][j_tmp].etat = vide;
					cases_extrude++;
				}
				j = j_tmp;
				i = i_tmp;
			}
		}
		
		if(j>3*(Y/5)){			//Ici, on regarde à chaques itérations si le curseur  est plutot du côté droit ou gauche (on incrémente ite_droite ou gauche en conséquence)
			ite_droite++;
		}
		else if(j<(Y/5)){
			ite_gauche++;
		}
		
		if(ite_droite> (X*Y)/4 ){	//Lorsque le curseur a extrudé plus d'un quart des murs a droite ou a gauche, on le remet au centre. On remet les statistiques a 0, mais on va utiliser la variable orientation
			i = X/2;				//Pour le faire partir préférentiellement du côté ou il a le moins "extrudé"
			j = Y/2;
			ite_gauche = 0;
			ite_droite = 0;
			orientation = -10;
		}
		else if(ite_gauche> (X*Y)/4 ){
			i = X/2;
			j = Y/2;
			ite_gauche = 0;
			ite_droite = 0;
			orientation = 10;
		}
	}
	
	a_lisse = lissage_lab(lab);	//Enfin, une fois que l'on a "extrudé" la moitié des murs, on utilise la fonction de "lissage", pour supprimer les murs trop abrupts
	while(a_lisse){
		a_lisse = lissage_lab(lab);
	}
}



/**
 * \brief   Affichage du labyrinthe en ASCII
 * \param 	lab[x][Y] 				Reçoie le labyrinthe de taille X, Y.
 * \param 	fourmi [] 				Reçoie le tableau de foumis.
 */			
void afficher_lab(t_lab lab[X][Y], t_fourmi fourmi[]){
	int char_unseen = '?';
	int indice;
	t_etat etat_tmp;
	t_discover decouvert_tmp;
	int i,j;

	printf("\n\n");
	for(i =-1; i<(X+1); i++){					//*Toute la partie qui suit gère l'affichage des bordures (avec les espacements	*//
		for(j =-1; j<(Y+1); j++){					//*particuliers pour que tout soit aligné)
			if(i == -1 && j != -1 ){							//*nombres de l'axe horizontal du haut
				if(j==0){										//*affichage du "Y" sur l'axe horizontal
					printf("\033[1;33;40m Y\033[00m");
				}
				else if(j == 58){
					printf("\033[1;33;40m Y\033[00m");
				}
				if((j%2)!=0){
					if(j == 9){
						printf("%i ", j);
					}
					else if(j < 10 ){
						printf("%i ", j);
					}
					else if(j == (Y-1) && i == -1){
					printf(" ");
					}
					else{
						printf("%i", j);
					}
				}
				else{
					printf("  ");
				}
			}
			else if(i == (X) && j!= -1 ){						//*nombres de l'axe horizontal du bas
				if((j%2)==0){
					if(j == 0){
						printf("\033[1;33;40m  Y  \033[00m");
					}
					else if( j == 60){
						printf(" ");
					}
					else if(j < 10 ){
						printf(" %i  ", j);
					}
					else if(j == (Y-1) && i == -1){
						printf(" ");
					}
					else{
						printf(" %i ", j);
					}
				}

				else if(j == 59){
					printf("\033[1;33;40mY \033[00m");
				}
			}
			else if(j == -1 && i != -1 && i != X){				//*nombres de l'axe vertical, a gauche
				if(i == 0){									//*affichage du "X" sur l'axe vertical
					printf("\033[1;33;40m X \033[00m");
				}
				else if(i == 29){									//*affichage du "X" sur l'axe vertical
					printf("\033[1;33;40m X \033[00m");
				}
				else if(i < 10 ){
					printf(" %i ", i);
				}
				else if(j == -1 && i == (X-1)){
				printf("   ");
				}
				else{
					printf("%i ", i);
				}
			}
			else if(j == Y && i != -1 && i != X){				//*nombres de l'axe vertical, a droite
				if(i == 0){
					printf("\033[1;33;40m X \033[00m");
				}
				else if(i ==29){
					printf("\033[1;33;40m X \033[00m");
				}
				else if(i < 10 ){
					printf(" %i ", i);
				}
				else if(j == -1 && i == (X-1) && i == (X)){
				printf("  ");
				}
				else{
					printf(" %i ", i);
				}
			}
			else if(j == -1 && i == -1){						//*coin supérieur gauche
				printf("  ");
			}
			else if(j == -1 && i == (X)){						//*pas de nombre en bas a gauche
				printf(" ");
			}
			else if(j == -1 && i == (X)){						//*pas de nombre en bas a gauche
				printf(" ");
			}
			else{									//*le else gère tout ce qui est a l'intérieur des bordures (insectes, nourriture)
				etat_tmp = lab[i][j].etat;
				decouvert_tmp = lab[i][j].decouvert;

				if(decouvert_tmp == 0){
				printf("\033[0;30;40m%c \033[00m", char_unseen);
				}
				else{
					if(etat_tmp == vide){
						printf("\033[0;33;43m%c \033[00m", etat_tmp);
					}
					else if(etat_tmp == mur){
						printf("\033[0;37;47m%c \033[00m", etat_tmp);
					}
					else if(etat_tmp == insecte){
						indice = lab[i][j].insecte;
						if(fourmi[indice].age <= 1 || fourmi[indice].nourriture <= 1){
							printf("\033[1;30;43m%c \033[00m", etat_tmp);
						}
						else if(fourmi[indice].age < 5 ){
							printf("\033[1;31;43m%c \033[00m", etat_tmp);
						}
						else if(fourmi[indice].nourriture < 5){
							printf("\033[1;32;43m%c \033[00m", etat_tmp);
						}
						else{
							printf("\033[1;36;43m%c \033[00m", etat_tmp);
						}
					}
					else if(etat_tmp == food){
						printf("\033[1;34;43m%c \033[00m", etat_tmp);
					}
					else{
						printf("%c ", etat_tmp);
					}
				}
			}


		}
		printf("\n");
	}
	printf("\n\n");
}



/**
 * \brief   Génère aléatoirement de la nourriture dans une case vide du labyrinthe et qui n'a pas besoin d'être dévouverte.	
 * \param 	lab[x][Y] 				Reçoie le labyrinthe de taille X, Y.
 */
void gene_nour(t_lab lab[X][Y]) {
	int nombrex, nombrey;
	srand(time(NULL));
	int i, nb_nourr=10;
	for(i=0; i<nb_nourr; i++) {
		nombrex = rand()%X;
		nombrey = rand()%Y;
		while(lab[nombrex][nombrey].etat!=vide || !coord_correctes(nombrex, nombrey)){
			nombrex = rand()%X;
			nombrey = rand()%Y;
		}
		lab[nombrex][nombrey].etat=food;
	}
}



/**
 * \brief   Découvre toutes les cases du labyrinthe (utilisé pour le débuggage)
 * \param 	lab[x][Y] 				Reçoie le labyrinthe de taille X, Y.
 */
void decouvrirlab(t_lab lab[X][Y]) {
	int i, j;
	for(i=0; i<X; i++) {
		for(j=0; j<Y; j++) {
			lab[i][j].decouvert=seen;
		}
	}
}
