#include<stdio.h>
#include<stdlib.h>
#define X 20 //Définit la taille du labyrinthe
#define Y 20


typedef enum {unseen=0, seen=1} t_discover;
typedef enum {vide=0, mur=1, food=2, insecte=3} t_etat;

typedef struct {t_discover decouvert; t_etat etat ; int insecte ;} t_lab ;
t_lab lab[X][Y];


void init_lab (t_lab lab[X][Y]){
	
	int tmp;
	int i,j;
	FILE * fic1;
	fic1 = fopen("../doc/lab_test.txt", "r");
	
	
	while(!feof(fic1))
	{	
		for(i =0; i<X; i++){
			for(j =0; j<Y; j++){	
				fscanf(fic1, "%d ", &tmp);
				lab[i][j].etat = tmp;
			}
		}
	}
	fclose(fic1);
}

void afficher_lab(t_lab lab[X][Y]){
	int tmp;
	int i,j;
	for(i =0; i<X; i++){
		for(j =0; j<Y; j++){
			tmp = lab[i][j].etat;
			printf("%d", tmp);
		}
		printf("\n");
	}
}

int main(){
	init_lab(lab);
	afficher_lab(lab);
	return 0;
}
