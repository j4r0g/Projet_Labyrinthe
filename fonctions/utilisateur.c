#include <stdio.h>
#include <stdlib.h>

typedef enum {MALE, FEMELLE} t_sexe;
typedef struct {t_sexe sexe; int nourriture; int age;} t_fourmi[];
typedef enum {unseen=0, seen=1} t_discover;
typedef enum {vide=0, mur=1, food=2, insecte=3} t_etat;
typedef struct {t_discover decouvert; t_etat etat; int insecte;} t_lab;

t_fourmi fourmi;

void actionUser(int maxx, int maxy, t_lab lab[maxx][maxy], int bouffe, int dureevie){
  int choix;
  char reponse;
  do {
    printf(" 1 - Ajouter trois nourritures\n");
    printf(" 2 - Ajouter un insecte\n");
    printf(" 3 - Abandonner la partie\n");
    printf("Votre choix : ");
    scanf("%d", &choix);

    switch(choix) {
      case 1 : ajoutNourriture(maxx, maxy, lab) ; break;
      case 2 : ajoutInsecte(maxx, maxy, lab, bouffe, dureevie) ; break;
      case 3 : {  printf("Souhaitez vous vraiment abandonner la partie ? (y/n) : ");
                  scanf("%c ", &reponse);
                  while(reponse!='y' && reponse!='n') {
                    printf("Souhaitez vous vraiment abandonner la partie ? (y/n) : ");
                    scanf("%c ", &reponse);
                  }
                  if(reponse=='n')
                    choix=4;
                } ; break;

    }
  }
  while(choix!=3);
}

void ajoutNourriture (int maxx, int maxy, t_lab lab[maxx][maxy]) {
  int x, y, i;
  srand(time(NULL));
  int nombre = rand()%3 + 1;
  printf("Vous avez le droit à %i cases de nourriture\n", nombre);
  for(i=0;i<nombre;i++) {
    printf("Entrez les coordonnées x et y de la nourriture %i séparées par un espace : ", i+1);
    scanf("%i%i", x, y);
    while(x<0 || x>maxx || y<0 || y>maxy || lab[x][y].etat!=vide || lab[x][y].decouvert!=seen){
      printf("Erreur, shame, recommencez\n");
      printf("Entrez les coordonnées x et y de la nourriture %i séparées par un espace : ", i+1);
      scanf("%i%i", x, y);
    }
    lab[x][y].etat=food;
  }
}

void ajoutInsecte (int maxx, int maxy, t_lab lab[maxx][maxy], int bouffe, int dureevie) {
  int x, y, i;
  srand(time(NULL));
  int nombre = rand()%100;
  if(nombre<50){
    printf("Vous n'avez aucun insecte à placer");
  }
  else {
    printf("Vous pouvez placer un insecte");
    printf("Entrez les coordonnées x et y de l'insecte séparées par un espace : ");
    scanf("%i%i", x, y);
    while(x<0 || x>maxx || y<0 || y>maxy || lab[x][y].etat!=vide || lab[x][y].decouvert!=seen){
      printf("Erreur, shame, recommencez\n");
      printf("Entrez les coordonnées x et y de l'insecte séparées par un espace : ");
      scanf("%i%i", x, y);
    }
    lab[x][y].etat=insecte;
    int sexe=rand()%100;
  	if(sexe<50)
  		fourmi[lab[x][y].insecte].sexe = MALE;
  	else
  		fourmi[lab[x][y].insecte].sexe = FEMELLE;

  	fourmi[lab[x][y].insecte].nourriture = bouffe;
  	fourmi[lab[x][y].insecte].age = dureevie;
  }
}
