#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define X 30 //Définit la taille du labyrinthe
#define Y 60

typedef enum {haut = 0, bas = 1, gauche = 2, droite = 3} t_direction;
typedef enum {unseen=0, seen=1} t_discover;
typedef enum {vide=' ', mur='#', food='*', insecte='%'} t_etat;

typedef struct {t_discover decouvert; t_etat etat ; int insecte ;} t_lab ;
//t_lab lab[X][Y];


//*			fonction qui renvoie un nombre aleatoire entre 0 et max			*//
int nbr_rand(int max){
	int nombre;
	nombre = rand()%max;
	return nombre;
}

//*			fonctions qui vérifient que les coordonnées mise en arguments font parties de la matrice		*//
int coord_correctes(t_lab lab[X][Y], int i, int j){
	return (i<(X-1) && i>0 && j<(Y-1) && j>0);
}

//*			initialisation du labyrinthe à partir d'un .txt			*//
void init_lab(t_lab lab[X][Y]){
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

//*			Cette fonction compte le nombre de cases vide			*//
int nbr_cases_vide(t_lab lab[X][Y]){
	int i, j;
	int nbr_cases_vide = 0;
	for (i=0; i<X; i++){
		for (j=0; j<Y; j++){
			if(lab[i][j].etat == vide){
				nbr_cases_vide++;
			}
		}
	}
	return nbr_cases_vide;
}

//*			Cette fonction "lisse" les murs. elle renvoit 1 si elle a effectué des modifications, 0 sinon		*//
int lissage_lab(t_lab lab[X][Y]){
	int i, j;
	int mur_adj=0;
	int a_lisse=0;
	for (i=0; i<X; i++){
		for (j=0; j<Y; j++){
			if(lab[i][j].etat == mur){
				mur_adj=0;

				if(lab[i][j-1].etat == vide){
					mur_adj++;
				}
				if(lab[i][j+1].etat == vide){
					mur_adj++;
				}
				if(lab[i-1][j].etat == vide){
					mur_adj++;
				}
				if(lab[i+1][j].etat == vide){
					mur_adj++;
				}
				if(mur_adj >= 3 ){
					lab[i][j].etat = vide;
					a_lisse=1;
				}

			}
		}
	}
	return a_lisse;
}


//*			initialisation pseudo-aléatoire du labyrinthe	(1er essai, par "ilots")		*//
/*void init_lab_rand (t_lab lab[X][Y]){
	int i,j, x, y, x_tmp, y_tmp, compteur_ilot, branche, rand_branche, a_lisse;
	int nbr_ilot=0;

	for(i =0; i<X; i++){		//Ce bloque place des murs tout autours du labyrinthe.
		for(j =0; j<Y; j++){
			if(i==0 || i==(X-1) || j==0 || j==(Y-1)){
				lab[i][j].etat = mur;
			}
			lab[i][j].decouvert = seen;		//Cette ligne initialise "discover" pour toutes les cases du labyrinthe (ici en "seen" pour tester, mais normalement "unseen"
		}
	}


	nbr_ilot = (nbr_rand()/10) + (X/5);			//Ce bloc là va créer les murs de manière aléatoire. Les "ilots" définissent des points sur lequels
	for(compteur_ilot=0; compteur_ilot<nbr_ilot; compteur_ilot++){ // une case est remplie avec un mur, puis les murs s'étendent de manière aléatoire depuis ce point.
		x = nbr_rand()/4;		//100 divisé par ... selon X et Y
		y = nbr_rand()/4;
		while( lab[x][y].etat != vide){		//Les ilots doivents être placés sur des emplacement vides
			x = nbr_rand()/5;
			y = nbr_rand()/5;
		}
		lab[x][y].etat = mur;

		for(i=-1; i<=1; i++){
			for(j=-1; j<=1; j++){		//Les "branches" sont les extensions des murs, qui vont dans toutes les directions
				x_tmp = x+i;
				y_tmp = y+j;
				branche = 1;
				while(branche == 1){
					if(lab[x_tmp][y_tmp].etat == mur){
						branche =0;
					}
					else{
						rand_branche = nbr_rand();
						if(rand_branche<40){
							lab[x_tmp][y_tmp].etat = mur;
							if(i<0){
								x_tmp--;
							}
							if(i>0){
								x_tmp++;
							}
							if(j<0){
								y_tmp--;
							}
							if(j>0){
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
		a_lisse = lissage_lab(lab);
		while(a_lisse !=0){
			a_lisse = lissage_lab(lab);
			printf("test\n");
		}
	}
}*/


//			initialisation pseudo-aléatoire du labyrinthe	(2nd essaie, par extrudage, en partant du centre)	*//
void init_lab_rand (t_lab lab[X][Y]){
	int i, j, direction, i_tmp, j_tmp, a_lisse;
	int cases_extrude = 0;
	int ite_gauche = 0;
	int ite_droite = 0;
	int orientation = 0;
	for(i =0; i<X; i++){		//Ce bloque place des murs partout
		for(j =0; j<Y; j++){
			lab[i][j].etat = mur;
			lab[i][j].decouvert = seen;		//Cette ligne initialise "discover" pour toutes les cases du labyrinthe (ici en "seen" pour tester, mais normalement "unseen"
		}
	}
	i = X/2;
	j = Y/2;
	while(cases_extrude < (X*Y)/2){
		lab[i][j].etat = vide;
		direction = nbr_rand(100);

		if(direction > 75 + orientation){
			i_tmp = i;
			j_tmp = j-1;
			if(coord_correctes(lab, i_tmp, j_tmp)){
				if(lab[i_tmp][j_tmp].etat == mur){
					lab[i_tmp][j_tmp].etat = vide;
					cases_extrude++;
				}
				i = i_tmp;
				j = j_tmp;
			}
		}
		else if(direction >50){
			i_tmp = i;
			j_tmp = j+1;
			if(coord_correctes(lab, i_tmp, j_tmp)){
				if(lab[i_tmp][j_tmp].etat == mur){
					lab[i_tmp][j_tmp].etat = vide;
					cases_extrude++;
				}
				i = i_tmp;
				j = j_tmp;
			}
		}
		else if(direction >25){
			i_tmp = i-1;
			j_tmp = j;
			if(coord_correctes(lab, i_tmp, j_tmp)){
				if(lab[i_tmp][j_tmp].etat == mur){
					lab[i_tmp][j_tmp].etat = vide;
					cases_extrude++;
				}
				i = i_tmp;
				j = j_tmp;

			}
		}
		else{
			i_tmp = i+1;
			j_tmp = j;
			if(coord_correctes(lab, i_tmp, j_tmp)){
				if(lab[i_tmp][j_tmp].etat == mur){
					lab[i_tmp][j_tmp].etat = vide;
					cases_extrude++;
				}
				j = j_tmp;
				i = i_tmp;
			}
		}
		if(j>3*(Y/5)){
			ite_droite++;
		}
		else if(j<(Y/5)){
			ite_gauche++;
		}
		if(ite_droite> (X*Y)/4 ){
			i = X/2;
			j = Y/2;
			ite_gauche = 0;
			ite_droite = 0;
			orientation = -10;
		}
		else if(ite_gauche> (X*Y)/4 ){
			i = X/2;
			j = Y/2;
			ite_gauche = 0;
			ite_droite = 0;
			orientation = 10;
		}
	}
	a_lisse = lissage_lab(lab);
	while(a_lisse){
		a_lisse = lissage_lab(lab);
		//printf("test\n");
	}
}

//*			initialisation pseudo-aléatoire du labyrinthe	(3eme essaie, de gauche a droite)			*//
/*void init_lab_rand_2 (t_lab lab[X][Y]){
	int i, j, direction, i_tmp, j_tmp, a_lisse;
	int cases_extrude = 0;

	for(i =0; i<X; i++){		//Ce bloque place des murs partout
		for(j =0; j<Y; j++){
			lab[i][j].etat = mur;
			lab[i][j].decouvert = seen;		//Cette ligne initialise "discover" pour toutes les cases du labyrinthe (ici en "seen" pour tester, mais normalement "unseen"
		}
	}

	i = X/2;
	j = 1;
	while(j<(Y-2)){
		lab[i][j].etat = vide;
		direction = nbr_rand(100);
		if(direction >60){
			i_tmp = i;
			j_tmp = j+1;
			if(coord_correctes(lab, i_tmp, j_tmp)){
				if(lab[i_tmp][j_tmp].etat == mur){
					lab[i_tmp][j_tmp].etat = vide;
					cases_extrude++;
				}
				j=j_tmp;
			}
		}
		else if(direction >35){
			i_tmp = i-1;
			j_tmp = j;
			if(coord_correctes(lab, i_tmp, j_tmp)){
				if(lab[i_tmp][j_tmp].etat == mur){
					lab[i_tmp][j_tmp].etat = vide;
					cases_extrude++;
				}
				i = i_tmp;
			}
		}
		else if(direction > 10){
			i_tmp = i+1;
			j_tmp = j;
			if(coord_correctes(lab, i_tmp, j_tmp)){
				if(lab[i_tmp][j_tmp].etat == mur){
					lab[i_tmp][j_tmp].etat = vide;
					cases_extrude++;
				}
				i = i_tmp;

			}
		}
		else {
			i_tmp = i;
			j_tmp = j-1;
			if(coord_correctes(lab, i_tmp, j_tmp)){
				if(lab[i_tmp][j_tmp].etat == mur){
					lab[i_tmp][j_tmp].etat = vide;
					cases_extrude++;
				}
				j = j_tmp;
			}
		}


	}

	a_lisse = lissage_lab(lab);
	while(a_lisse){
		a_lisse = lissage_lab(lab);
		printf("test\n");
	}

	printf("gauche : %d\n", gauche);
	printf("droite : %d\n", droite);
	printf("haut : %d\n", haut);
	printf("bas : %d\n", bas);
}*/


//			affichage du labyrinthe en ASCII
void afficher_lab(t_lab lab[X][Y]){

	int char_unseen = '?';

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
				printf("%c ", etat_tmp);
			}
		}
		printf("\n");
	}
	printf("\n\n");
}


int /*main(){*/genelab(t_lab lab[X][Y]){
	srand(time(NULL));
	init_lab_rand(lab);
	//afficher_lab(lab);
	return 0;
}
