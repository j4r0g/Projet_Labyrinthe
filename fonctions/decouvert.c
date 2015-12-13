#include <stdio.h>
#include <stdlib.h>
#include "./../header/struct.h"

void decouvrir(t_lab lab[X][Y]) {
  int i, j;
  for(i=0;i<X;i++) {
    for(j=0;j<Y;j++){
      if(lab[i][j].etat==insecte) {
          lab[i][j].decouvert=seen;
          /* Découverte suivant l'axe des x*/
          if(i+1<X)
            lab[i+1][j].decouvert=seen;
          if(i+2<X)
            lab[i+2][j].decouvert=seen;
          if(i-1>0)
            lab[i-1][j].decouvert=seen;
          if(i-2>0)
            lab[i-2][j].decouvert=seen;

          /*Découverte suivant l'axe des y*/
          if(j+1<Y)
            lab[i][j+1].decouvert=seen;
          if(j+2<Y)
            lab[i][j+2].decouvert=seen;
          if(i-1>0)
            lab[i][j-1].decouvert=seen;
          if(j-2>0)
            lab[i][j-2].decouvert=seen;

          /* Découverte dans les diagonales */
          if(i+1<X && j+1<Y)
            lab[i+1][j+1].decouvert=seen;
          if(i-1>0 && j-1>0)
            lab[i-1][j-1].decouvert=seen;
          if(i+1<X && j-1>0)
            lab[i+1][j-1].decouvert=seen;
          if(i-1>0 && j+1<Y)
            lab[i-1][j+1].decouvert=seen;
      }
    }
  }
}
