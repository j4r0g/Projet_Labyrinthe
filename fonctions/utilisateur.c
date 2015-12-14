#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./../header/struct_lab.h"
#include "./../header/struct_ins.h"

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

int ajoutInsecte (t_lab lab[X][Y], int bouffe, int dureevie, t_fourmi fourmi[], int nb_ins) {
  int a, b;
  srand(time(NULL));
  int nombre = rand()%100;
  if(nombre<50){
    printf("Vous n'avez aucun insecte à placer");
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
  return 0;
}

int actionUser(t_lab lab[X][Y], int bouffe, int dureevie, t_fourmi fourmi[], int nb_ins){
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
      case 2 : ajoutInsecte(lab, bouffe, dureevie, fourmi, nb_ins) ; break;
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
  else if (choix==2)
    return 2;
  else
    return 1;
}
