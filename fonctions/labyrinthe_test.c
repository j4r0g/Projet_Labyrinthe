#include<stdio.h>
#include<stdlib.h>
#define X 20 //Définit la taille du labyrinthe
#define Y 20

typedef enum {unseen=0, seen=1} t_discover;
typedef enum {vide=0, mur=1, food=2, insecte=3} t_etat;

typedef struct {t_discover decouvert; t_etat etat ; int insecte ;} t_lab ;
t_lab lab[X][Y];


/*			affichage du labyrinthe en ASCII			*/
void afficher_lab(t_lab lab[X][Y]){
	
	int char_unseen = 63;
	int char_mur = 35;
	int char_insecte = 37;
	int char_rien = 32;
	int char_food = 42;
	
	t_etat etat_tmp;
	t_discover decouvert_tmp;
	int i,j;
	
	printf("\n\n");
	for(i =0; i<X; i++){
		for(j =0; j<Y; j++){
			etat_tmp = lab[i][j].etat;
			decouvert_tmp = lab[i][j].decouvert;
			if(decouvert_tmp == 0){ 
				printf("%c ", char_unseen);
			}
			else{
				switch (etat_tmp){
					case vide:
						printf("%c ", char_rien);
						break;
					case mur:
						printf("%c ", char_mur);
						break;
					case food:
						printf("%c ", char_food);
						break;
					case insecte:
						printf("%c ", char_insecte);
						break;
					default:
						printf("x ");
				} 
			}
		}
		printf("\n");
	}
	printf("\n\n");
}

void init_lab(t_lab lab[X][Y]){
	int tmp;
	int i,j;
	FILE * fic1;
	fic1 = fopen("../doc/lab_test.txt", "r");
	
	while(!feof(fic1)){	
		for(i =0; i<X; i++){
			for(j =0; j<Y; j++){				
				fscanf(fic1, "%d ", &tmp);
				lab[i][j].etat = tmp;
				lab[i][j].decouvert = seen;
			}
		}
	}
	fclose(fic1);
}


int main(){
	init_lab(lab);
	afficher_lab(lab);
	printf("coucou\n");
	return 0;
}
