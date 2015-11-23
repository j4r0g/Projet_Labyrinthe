#include<stdio.h>
#include<stdlib.h>
#include<time.h> 
#define X 20 //Définit la taille du labyrinthe
#define Y 20

typedef enum {unseen=0, seen=1} t_discover;
typedef enum {vide=0, mur=1, food=2, insecte=3} t_etat;

typedef struct {t_discover decouvert; t_etat etat ; int insecte ;} t_lab ;
t_lab lab[X][Y];


//*			fonction qui renvoie un nombre aleatoire entre 0 et 99			*//
int nbr_rand(){
	int m=100; 
	int nombre;
	nombre = rand()%m;
	return nombre;
}


//*			initialisation du labyrinthe à partir d'un .txt			*//
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
				lab[i][j].decouvert = unseen;
			}
		}
	}
	fclose(fic1);
}


//*			initialisation pseudo-aléatoire du labyrinthe			*//
void init_lab_rand (t_lab lab[X][Y]){
	int i,j, x, y, x_tmp, y_tmp, compteur_ilot, branche, rand_branche;
	int nbr_ilot=0;
	
	for(i =0; i<X; i++){
		for(j =0; j<Y; j++){				
			if(i==0 || i==19 || j==0 || j==19){
				lab[i][j].etat = mur;
			}
			lab[i][j].decouvert = seen;
		}
	}
	
	nbr_ilot = (nbr_rand()/10) +4;
	for(compteur_ilot=0; compteur_ilot<nbr_ilot; compteur_ilot++){
		x = nbr_rand()/5;
		y = nbr_rand()/5;
		while( lab[x][y].etat != vide){
			x = nbr_rand()/5;
			y = nbr_rand()/5;
		}
		lab[x][y].etat = mur;
		
		for(i=-1; i<=1; i++){
			for(j=-1; j<=1; j++){
				x_tmp = x+i;
				y_tmp = y+j;
				branche = 1;
				while(branche == 1){
					if(lab[x_tmp][y_tmp].etat == mur){
						branche =0;
					}
					else{
						rand_branche = nbr_rand();
						if(rand_branche<50){
							lab[x_tmp][y_tmp].etat = mur;
							if(x_tmp<0){
								x_tmp--;
							}
							else if(x_tmp>0){
								x_tmp++;
							}
							if(y_tmp<0){
								y_tmp--;
							}
							else if(y_tmp>0){
								y_tmp++;
							}
						}
						else{
							branche = 0;
						}
					}
				}
			}
		}
		
	}
}

//*			affichage du labyrinthe en ASCII			*//
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


int main(){
	srand(time(NULL));
	init_lab_rand(lab);
	afficher_lab(lab);
	return 0;
}
