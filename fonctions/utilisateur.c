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
#include "./../header/struct_lab.h"
#include "./../header/struct_ins.h"
#include "./../header/utilisateur.h"

/**
 * \brief   Génère de la nourriture dans une case vide du labyrinthe découverte
 *          à la demande de l'utilisateur.
 * \param 	lab[x][Y] 				Reçoie le labyrinthe de taille X, Y.
 * \return  0 à la réussite de la fonction
 */
int ajoutNourriture (t_lab lab[X][Y]) {
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
 */
/*void sauver_lab(t_lab lab[X][Y]){
	int tmp;
	int i,j;
	FILE * fic1;
	fic1 = fopen("../doc/SAVED_GAME.txt", "w");

	while(!feof(fic1))
	{
		for(i =0; i<X; i++){
			for(j =0; j<Y; j++){
				lab[i][j].etat = tmp;
				lab[i][j].decouvert = unseen;
				fprintf(fic1, "%c %c ", &tmp, &unseen);

			}
			fprintf(fic1, "\n");
		}
	}
	fclose(fic1);
}*/

/**
 * \brief   Gére le menu d'interface utilisateur à chaque tour.
 * \param 	lab[x][Y] 				Reçoie le labyrinthe de taille X, Y.
 * \param   bouffe						Reçoie la durée de vie de la bouffe en nombre de tour.
 * \param   dureevie         	Reçoie la durée de vie en nombre de tour.
 * \return  Un 0 si on force l'abandon, un 1 sinon.
 */
int actionUser(t_lab lab[X][Y], int bouffe, int dureevie, t_fourmi fourmi[]){
  int choix;
  char reponse='\0';
  do {
    printf(" 1 - Ajouter de la nourriture\n");
    printf(" 2 - Ajouter un insecte\n");
    printf(" 3 - Passer\n");
    printf(" 4 - Abandonner la partie\n");
    printf("Votre choix : ");
    scanf("%i%*c", &choix);

    switch(choix) {
      case 1 : ajoutNourriture(lab) ; break;
      case 2 : ajoutInsecte(lab, bouffe, dureevie, fourmi) ; break;
      case 3 : break;
      case 4 : {  printf("Souhaitez vous vraiment abandonner la partie ? (y/n) : ");
                  scanf("%c%*c", &reponse);
                  if(reponse!='y' || reponse!='n') {
                    while(reponse!='y' && reponse!='n') {
                      printf("Souhaitez vous vraiment abandonner la partie ? (y/n) : ");
                      scanf("%c%*c", &reponse);
                    }
                    if(reponse=='n')
                      choix=5;
                  }
                } ; break;

    }
  }
  while(choix==5);
  if(choix==4)
    return 0;
  else
    return 1;
}
