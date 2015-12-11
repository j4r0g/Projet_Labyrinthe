#include <stdio.h>
#include <stdlib.h>

#define X 30 //Définit la taille du labyrinthe
#define Y 60

typedef enum {MALE, FEMELLE} t_sexe;
typedef struct {t_sexe sexe; int nourriture; int age;} t_fourmi;
t_fourmi fourmi[40];

typedef enum {unseen=0, seen=1} t_discover;
typedef enum {vide=' ', mur='#', food='*', insecte='%'} t_etat;

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
  printf("- Placer entre 1 et 3 de nourriture (géré aléatoirement)\n");
  return 0;
}

int lancement() {
  int i, j, vic, res, issue=2;
  int nbre=0;
  int bouffe=10;
  int dureevie=30;
  genelab(lab); //Génération du labyrinthe
  for(nbre=0;nbre<10;nbre++) {
    gene_deb(bouffe, dureevie, lab, i, fourmi); //Génération de chaque insecte
  }
  decouvrir(X, Y, lab);
  afficher_lab(lab);
  vic=verifvictoire(X, Y, lab);
  while(vic==0){
    /* Il serait judicieux d'ajouter dans l'énumération l'emplacement de l'insecte afin de ne pas
    parcourir entièrement la matrice*/
    for(i=0;i<X;i++) {
      for(j=0;j<Y;j++) {
        if(lab[i][j].etat=insecte){
          deplacement (lab, i, j);
          /*if (issue==1)
            nbre++;*/
        }
      }
    }
    afficher_lab(lab);
    res=actionUser(X, Y, lab, bouffe, dureevie);
    if(res==0) // Si on force l'abandon
      return 1;
    if(res==2) // Si on a ajouté un insecte
      nbre++;
    vic=verifvictoire(X, Y, lab);
  }
  /*if(vic==1)
    printf("Vous avez gagné");
  else if(vic==2)
    printf("Vous avez perdu");
  else
    printf("Erreur");
  return 0;*/
}
