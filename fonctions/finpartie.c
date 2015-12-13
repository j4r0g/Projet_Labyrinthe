#include <stdio.h>
#include <stdlib.h>
#include "./../header/struct.h"

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
