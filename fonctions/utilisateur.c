/**
 * \file 			utilisateur.c
 * \author    Boisson Léo, Bussereau Keryann, Ciron Fabien
 * \version   1.0
 * \date      14 décembre 2015
 * \brief     Gère l'interface avec l'utilisateur à chaque tour
 * \details   Ce module à pour but de demander à l'utilisateur via un menu
 *            l'action qu'il souhaite effectuer à chaque tour il permet
 *            également d'ajouter de la nourriture ou un insecte si l'utilisateur le demande
 */



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "./../header/struct_lab.h"
#include "./../header/struct_ins.h"
#include "./../header/utilisateur.h"


/**
 * \brief   Génère de la nourriture dans une case vide du labyrinthe découverte
 *          à la demande de l'utilisateur.
 * \param 	lab[x][Y] 				Reçoie le labyrinthe de taille X, Y.
 * \param 	fourmi    				Reçoie le tableau de foumis.
 * \return  0 à la réussite de la fonction
 */
int ajout_nourriture (t_lab lab[X][Y]) {
  int a, b, i;
  srand(time(NULL));
  int nombre = rand()%3 + 1;
  printf("Vous avez le droit à %i cases de nourriture\n", nombre);
  for(i=0;i<nombre;i++) {
    printf("Entrez les coordonnées x et y de la nourriture %i séparées par un espace (doit être découvert) : ", i+1);
    scanf("%i%i", &a, &b);
    while(a<=0 || a>=X || b<=0 || b>=Y || lab[a][b].etat!=vide || lab[a][b].decouvert!=seen){
      printf("Erreur, shame, recommencez\n");
      printf("Entrez les coordonnées x et y de la nourriture %i séparées par un espace : ", i+1);
      scanf("%i%i", &a, &b);
    }
    lab[a][b].etat=food;
  }
  return 0;
}



/**
 * \brief   Permet de sauvegarder la partie en cours
 * \param 	lab[x][Y] 				Reçoie le labyrinthe de taille X, Y.
 * \param 	fourmi    				Reçoie le tableau de foumis.
 */
void sauver_lab(t_lab lab[X][Y], t_fourmi fourmi[]){
	FILE * fic1;
	int tmp;
	int seen;
	int i,j;
	fic1 = fopen("SAVED_GAME", "w");
	for(i =0; i<X; i++){
		for(j =0; j<Y; j++){
			tmp = lab[i][j].etat;
			seen = lab[i][j].decouvert;
			fprintf(fic1, "%c", tmp);
			fprintf(fic1, "%d", seen);
		}
	}
	int nb_ins = nb_insecte();
	fprintf(fic1, "%d ", nb_ins);
	/*for(i=0; i<nb_ins; i++){
		fprintf(fic1, "%d ", fourmi[i].sexe);
		fprintf(fic1, "%d ", fourmi[i].nourriture);
		fprintf(fic1, "%d ", fourmi[i].age);
		fprintf(fic1, "%d ", fourmi[i].x);
		fprintf(fic1, "%d ", fourmi[i].y);
	}*/

	fclose(fic1);
}



/**
 * \brief   Permet de charger une partie sauvegardée
 * \param 	lab[x][Y]        Reçoie le labyrinthe de taille X, Y.
 * \param 	fourmi  				 Reçoie le tableau de foumis.
 */
void charger_lab(t_lab lab[X][Y], t_fourmi fourmi[]){
	FILE * fic2;
	char tmp;
	int seen;
	int nb_ins;
	int i,j;
	fic2 = fopen("SAVED_GAME", "r");
	if(fic2 == 0){
		printf("Pas de partie sauvegardee.\n\n");
	}
	else{
		while(!feof(fic2))
		{
			for(i =0; i<X; i++){
				for(j =0; j<Y; j++){
					fscanf(fic2, "%c", &tmp);
					fscanf(fic2, "%d", &seen);
					lab[i][j].etat = tmp;
					lab[i][j].decouvert = seen;

				}
			}
			fscanf(fic2, "%i ", &nb_ins);
			printf("%i", nb_ins);
			chang_nb_ins(nb_ins);
			for(i = 0; i<nb_ins; i++){
				fscanf(fic2, "%i ", &tmp);
				fourmi[i].sexe = tmp;
				fscanf(fic2, "%i ", &tmp);
				fourmi[i].nourriture = tmp;
				fscanf(fic2, "%i ", &tmp);
				fourmi[i].age = tmp;
				fscanf(fic2, "%i ", &tmp);
				fourmi[i].x = tmp;
				fscanf(fic2, "%i ", &tmp);
				fourmi[i].y = tmp;
			}
		}
		fclose(fic2);
	}
}



/**
 * \brief   Gére le menu d'interface utilisateur à chaque tour.
 * \param 	lab[x][Y] 				Reçoie le labyrinthe de taille X, Y.
 * \param   bouffe						Reçoie la durée de vie de la bouffe en nombre de tour.
 * \param   dureevie         	Reçoie la durée de vie en nombre de tour.
 * \param 	fourmi    				Reçoie le tableau de foumis.
 * \return  Un 0 si on force l'abandon, un 1 sinon.
 */
int action_user(t_lab lab[X][Y], int bouffe, int dureevie, t_fourmi fourmi[]){
  int choix, i, j;
  char reponse='\0';
  do {
    printf(" 1 - Ajouter de la nourriture\n");
    printf(" 2 - Ajouter un insecte\n");
    printf(" 3 - Passer\n");
    printf(" 4 - Abandonner la partie\n");
    printf(" 5 - Sauvegarder la partie\n");
    printf(" 6 - Charger la partie\n");
    printf("Votre choix : ");
    scanf("%i%*c", &choix);

    switch(choix) {
		case 1 : ajout_nourriture(lab) ; break;
		case 2 : ajout_insecte(lab, bouffe, dureevie, fourmi) ; break;
		case 3 : break;
		case 4 : {  printf("Souhaitez vous vraiment abandonner la partie ? (y/n) : ");
					scanf("%c%*c", &reponse);
					if(reponse!='y' || reponse!='n') {
						while(reponse!='y' && reponse!='n') {
							printf("Souhaitez vous vraiment abandonner la partie ? (y/n) : ");
							scanf("%c%*c", &reponse);
						}
						if(reponse=='n')
							choix=7;
						}
				 } ; break;
		case 5 :{
					sauver_lab(lab, fourmi);
				}  ; break;
		case 6 :{
					charger_lab(lab, fourmi);
				} ; break;
		case 666 : decouvrir_lab(lab); break;
    default : printf("\nErreur retentez\n\n"); choix=7; break;

    }
  }
  while(choix==7);
  if(choix==4)
    return 0;
  else
    return 1;
}
