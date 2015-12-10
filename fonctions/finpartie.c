#include <stdio.h>
#include <stdlib.h>

//typedef enum t_sexe {MALE, FEMELLE};
//typedef struct {t_sexe sexe; int nourriture; int age;} t_fourmi[];
typedef enum {unseen=0, seen=1} t_discover;
typedef enum {vide=0, mur=1, food=2, insecte=3} t_etat;
typedef struct {t_discover decouvert; t_etat etat; int insecte;} t_lab;

// renvoie 0 si rien, 1 si victoire, 2 si défaite
int verifvictoire (int maxx, int maxy, t_lab lab[maxx][maxy]) {
  int i, j;
  int victoire = 1;
  int defaite = 1;
  for(i=0;i<maxx;i++) {
    for(j=0;j<maxy;j++) {
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
}
