#include <stdio.h>
#include <stdlib.h>

typedef enum {MALE, FEMELLE} t_sexe;
typedef struct {t_sexe sexe; int nourriture; int age;} t_fourmi;

typedef enum {unseen=0, seen=1} t_discover;
typedef enum {vide=' ', mur='#', food='*', insecte='%'} t_etat;

typedef struct {t_discover decouvert; t_etat etat ; int insecte ;} t_lab ;

//t_fourmi fourmis[MAXFOURMI];

void decouvrir(int maxx, int maxy, t_lab lab[maxx][maxy]) {
  int i, j;
  for(i=0;i<maxx;i++) {
    for(j=0;j<maxy;j++){
      if(lab[i][j].etat==insecte) {
          lab[i][j].decouvert=seen;
          /* Découverte suivant l'axe des x*/
          if(i+1<maxx)
            lab[i+1][j].decouvert=seen;
          if(i+2<maxx)
            lab[i+2][j].decouvert=seen;
          if(i-1>0)
            lab[i-1][j].decouvert=seen;
          if(i-2>0)
            lab[i-2][j].decouvert=seen;

          /*Découverte suivant l'axe des y*/
          if(j+1<maxy)
            lab[i][j+1].decouvert=seen;
          if(j+2<maxy)
            lab[i][j+2].decouvert=seen;
          if(i-1>0)
            lab[i][j-1].decouvert=seen;
          if(j-2>0)
            lab[i][j-2].decouvert=seen;

          /* Découverte dans les diagonales */
          if(i+1<maxx && j+1<maxy)
            lab[i+1][j+1].decouvert=seen;
          if(i-1>0 && j-1>0)
            lab[i-1][j-1].decouvert=seen;
          if(i+1<maxx && j-1>0)
            lab[i+1][j-1].decouvert=seen;
          if(i-1>0 && j+1<maxy)
            lab[i-0][j+1].decouvert=seen;
      }
    }
  }
}
