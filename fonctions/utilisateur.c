#include <stdio.h>
#include <stdlib.h>

//typedef enum t_sexe {MALE, FEMELLE};
//typedef struct {enum t_sexe sexe; int nourriture; int age;} t_fourmi[];
//typedef enum {unseen=0, seen=1} t_discover;
//typedef enum {vide=0, mur=1, food=2, insecte=3} t_etat;
//typedef struct {t_discover decouvert; t_etat etat; int insecte;} t_lab;

void actionUser(){
  char reponse;
  do {
    printf(" 1 - Ajouter trois nourritures\n");
    printf(" 2 - Ajouter un insecte\n");
    printf(" 3 - Abandonner la partie\n");
    printf("Votre choix : ");
    scanf("%d", &choix);

    switch(choix) {
      case 1 : ajoutNourriture() ; break;
      case 2 : ajoutInsecte() ; break;
      case 3 : {  printf("Souhaitez vous vraiment abandonner la partie ? (y/n) : ");
                  scanf("%c", reponse);
                  while(reponse!="y" && reponse!="n") {
                    printf("Souhaitez vous vraiment abandonner la partie ? (y/n) : ");
                    scanf("%c", reponse);
                  }
                  if(reponse=="n")
                    choix=4;
                } ; break;

    }
  }
  while(choix!=3);
}

void ajoutNourriture () {

}

void ajoutInsecte () {

}
