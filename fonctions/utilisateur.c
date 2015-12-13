#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./../header/struct.h"

int ajoutNourriture (int maxx, int maxy, t_lab lab[maxx][maxy]) {
  int x, y, i;
  srand(time(NULL));
  int nombre = rand()%3 + 1;
  printf("Vous avez le droit à %i cases de nourriture\n", nombre);
  for(i=0;i<nombre;i++) {
    printf("Entrez les coordonnées x et y de la nourriture %i séparées par un espace : ", i+1);
    scanf("%i%i", &x, &y);
    while(x<0 || x>maxx || y<0 || y>maxy || lab[x][y].etat!=vide || lab[x][y].decouvert!=seen){
      printf("Erreur, shame, recommencez\n");
      printf("Entrez les coordonnées x et y de la nourriture %i séparées par un espace : ", i+1);
      scanf("%i%i", &x, &y);
    }
    lab[x][y].etat=food;
  }
  return 0;
}

int ajoutInsecte (int maxx, int maxy, t_lab lab[maxx][maxy], int bouffe, int dureevie, t_fourmi fourmi[], int nb_ins) {
  int x, y;
  srand(time(NULL));
  int nombre = rand()%100;
  if(nombre<50){
    printf("Vous n'avez aucun insecte à placer");
  }
  else {
    printf("Vous pouvez placer un insecte");
    printf("Entrez les coordonnées x et y de l'insecte séparées par un espace : ");
    scanf("%i%i", &x, &y);
    while(x<0 || x>maxx || y<0 || y>maxy || lab[x][y].etat!=vide || lab[x][y].decouvert!=seen){
      printf("Erreur, shame, recommencez\n");
      printf("Entrez les coordonnées x et y de l'insecte séparées par un espace : ");
      scanf("%i%i", &x, &y);
    }
    lab[x][y].etat=insecte;
    nb_ins++;
    lab[x][y].insecte=nb_ins;
    int sexe=rand()%100;
  	if(sexe<50)
  		fourmi[lab[x][y].insecte].sexe = MALE;
  	else
  		fourmi[lab[x][y].insecte].sexe = FEMELLE;

  	fourmi[lab[x][y].insecte].nourriture = bouffe;
  	fourmi[lab[x][y].insecte].age = dureevie;
  }
  return 0;
}

int actionUser(int maxx, int maxy, t_lab lab[maxx][maxy], int bouffe, int dureevie, t_fourmi fourmi[], int nb_ins){
  int choix;
  char reponse='\0';
  do {
    printf(" 1 - Ajouter trois nourritures\n");
    printf(" 2 - Ajouter un insecte\n");
    printf(" 3 - Abandonner la partie\n");
    printf("Votre choix : ");
    scanf("%d", &choix);

    switch(choix) {
      case 1 : ajoutNourriture(maxx, maxy, lab) ; break;
      case 2 : ajoutInsecte(maxx, maxy, lab, bouffe, dureevie, fourmi, nb_ins) ; break;
      case 3 : {  scanf("%c", &reponse);
                  while(reponse!='y' && reponse!='n') {
                    printf("Souhaitez vous vraiment abandonner la partie ? (y/n) : ");
                    scanf("%c", &reponse);
                  }
                  if(reponse=='n')
                    choix=4;
                } ; break;

    }
  }
  while(choix==4);
  if(choix==3)
    return 0;
  else if (choix==2)
    return 2;
  else
    return 1;
}
