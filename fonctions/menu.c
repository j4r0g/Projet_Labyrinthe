#include <stdio.h>
#include <stdlib.h>

#define X 30 //Définit la taille du labyrinthe
#define Y 60

typedef enum {MALE, FEMELLE} t_sexe;
typedef struct {t_sexe sexe; int nourriture; int age;} t_fourmi;
t_fourmi fourmi[10];

typedef enum {unseen=0, seen=1} t_discover;
typedef enum {vide=0, mur=1, food=2, insecte=3} t_etat;
typedef struct {t_discover decouvert; t_etat etat; int insecte;} t_lab;
t_lab lab[X][Y];

void main() {
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
      case 1 : regles() ; break;
      case 2 : lancement() ; break;
      case 3 : break;

    }
  }
  while(choix!=3);
  printf("Au revoir !\n");
}

int regles() {
  printf("\n Les règles sont les suivantes :\n");
  printf("A chaque tour vous pouvez choisir de :\n");
  printf("- Placer soit 0 ou 1 insecte (géré aléatoirement)\n");
  printf("- Placer entre 1 et 3 de nourriture (géré aléatoirement)");
  return 0;
}

int lancement() {
  int i;
  int bouffe=10;
  int dureevie=30;
  genelab(lab); //Génération du labyrinthe
  for(i=0;i<10;i++) {
    gene_deb(bouffe, dureevie, lab, i); //Génération de chaque insecte
  }
  while(!verifvictoire(X, Y, lab)){
    int i,j,nbre=0;
    // Il serait judicieux d'ajouter dans l'énumération l'emplacement de l'insecte afin de ne pas
    parcourir entièrement la matrice
    for(i=0;i<X;i++) {
      for(j=0;j<Y;j++) {
        if(lab[i][j].etat=insecte){
          nbre++;
          prochain_deplacement (i,j);
        }
      }
    }
    afficher_lab(lab);
    actionUser(X, Y, lab, bouffe, dureevie)
  }
  return 0;
}
