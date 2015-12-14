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
 * \brief   Génère un insecte dans une case vide du labyrinthe découverte
 *          à la demande de l'utilisateur.
 * \param 	lab[x][Y] 				Reçoie le labyrinthe de taille X, Y.
 * \param   bouffe						Reçoie la durée de vie de la bouffe en nombre de tour.
 * \param   dureevie         	Reçoie la durée de vie en nombre de tour.
 * \param 	fourmi[] 					Reçoie le tableau d'insectes.
 * \param 	nb_ins 						Reçoie le nombre d'insectes du labyrinthe.
 * \return  Un 0 si aucun insecte n'est placé, un 1 sinon.
 */
int ajoutInsecte (t_lab lab[X][Y], int bouffe, int dureevie, t_fourmi fourmi[], int nb_ins) {
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
    lab[a][b].etat=insecte;
    nb_ins++;
    lab[a][b].insecte=nb_ins;
    int sexe=rand()%100;
  	if(sexe<50)
  		fourmi[lab[a][b].insecte].sexe = MALE;
  	else
  		fourmi[lab[a][b].insecte].sexe = FEMELLE;

  	fourmi[lab[a][b].insecte].nourriture = bouffe;
  	fourmi[lab[a][b].insecte].age = dureevie;
  }
  return 1;
}

/**
 * \brief   Gére le menu d'interface utilisateur à chaque tour.
 * \param 	lab[x][Y] 				Reçoie le labyrinthe de taille X, Y.
 * \param   bouffe						Reçoie la durée de vie de la bouffe en nombre de tour.
 * \param   dureevie         	Reçoie la durée de vie en nombre de tour.
 * \param 	fourmi[] 					Reçoie le tableau d'insectes.
 * \param 	nb_ins 						Reçoie le nombre d'insectes du labyrinthe.
 * \return  Un 0 si on force l'abandon, un 2 si on a ajouté un insecte et un 1 sinon.
 */
int actionUser(t_lab lab[X][Y], int bouffe, int dureevie, t_fourmi fourmi[], int nb_ins){
  int choix, res;
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
      case 2 : res=ajoutInsecte(lab, bouffe, dureevie, fourmi, nb_ins) ; break;
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
  else if (choix==2 && res==1)
    return 2;
  else
    return 1;
}
