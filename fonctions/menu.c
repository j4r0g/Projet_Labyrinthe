#include <stdio.h>
#include <stdlib.h>

typedef enum {MALE, FEMELLE} t_sexe;
typedef struct {t_sexe sexe; int nourriture; int age;} t_fourmi[];
typedef enum {unseen=0, seen=1} t_discover;
typedef enum {vide=0, mur=1, food=2, insecte=3} t_etat;
typedef struct {t_discover decouvert; t_etat etat; int insecte;} t_lab;

void menu(int maxx, int maxy, t_lab lab[maxx][maxy]) {
  int choix;
  // Affichage du menu
  do {
    printf("\nMenu : \n");
    printf(" 1 - Voir les règles du jeu\n");
    printf(" 2 - Lancer la partie\n");
    printf(" 3 - Quitter\n");
    printf("Votre choix : ");
    scanf("%d", &choix);

    switch(choix) {
      case 1 : fonc1() ; break;
      case 2 : fonc2() ; break;
      case 3 : break;

    }
  }
  while(choix!=3);
  printf("Au revoir !\n");
}

void fonc1() {

}

void fonc2() {

}
