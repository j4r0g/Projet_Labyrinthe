#include <stdio.h>
#include <stdlib.h>
#include "./header/struct_lab.h"
#include "./header/struct_ins.h"
#include "./header/main.h"

t_lab lab[X][Y];
t_fourmi fourmi[40];

// renvoie 0 si rien, 1 si victoire, 2 si défaite
int verifvictoire (t_lab lab[X][Y]) {
  int i, j;
  int victoire = 1;
  int defaite = 1;
  for(i=0;i<X;i++) {
    for(j=0;j<Y;j++) {
      if(victoire && lab[i][j].decouvert==unseen && lab[i][j].etat!=mur){
        victoire=0;
      }
      if(defaite && lab[i][j].etat==insecte){
        defaite=0;
      }
      if(!defaite && !victoire)
        return 0;
    }
  }
  if(victoire)
    return 1;
  else if(defaite)
    return 2;
  else
    return 4;
}

int regles() {
  printf("\n Les règles sont les suivantes :\n\n");
  printf("A chaque tour vous pouvez choisir de :\n");
  printf("- Placer soit 0 ou 1 insecte (géré aléatoirement)\n");
  printf("- Placer entre 1 et 3 de nourriture (géré aléatoirement)\n\n");
  printf("Vous gagnez si vous découvrez tout le labyrinthe.\n");
  printf("Vous perdez si tout vos insectes sont morts.\n");
  printf("Vous avez un certain nombre de tour de réserve de nourriture, il en va de même pour la durée de vie.\n");
  printf("Deux insectes sur des cases adjacentes se batent ou se reproduisent.\n");
  return 0;
}

int lancement() {
  int i, j, vic, res=5;
  int nbre=0;
  int bouffe=10;
  int dureevie=30;
  genelab(lab); //Génération du labyrinthe
  for(nbre=0;nbre<10;nbre++) {
    gene_ins(bouffe, dureevie, lab, fourmi, nbre); //Génération de chaque insecte
  }

  for(i=0;i<10;i++) {
    gene_nour(lab); //Génération de chaque case de nourriture
  }

  decouvrir(lab);
  afficher_lab(lab);
  vic=verifvictoire(lab);
  while(vic==0){
    /* Il serait judicieux d'ajouter dans l'énumération l'emplacement de l'insecte afin de ne pas
    parcourir entièrement la matrice*/
    res=actionUser(lab, bouffe, dureevie, fourmi, nbre);
    if(res==0) // Si on force l'abandon
      return 1;
    else if(res==2) // Si on a ajouté un insecte
      nbre++;
    for(i=0;i<X;i++) {
      for(j=0;j<Y;j++) {
        if(lab[i][j].etat==insecte){
          prochain_deplacement(i, j, lab, fourmi, bouffe, dureevie, nbre);//deplacement(lab, i, j);
          decouvrir(lab);
        }
      }
    }
    afficher_lab(lab);
    vic=verifvictoire(lab);
  }
  if(vic==1)
    printf("Vous avez gagné");
  else if(vic==2)
    printf("Vous avez perdu");
  else
    printf("Erreur");
  return 0;
}

int main() {
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
  return 0;
}
