#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./../header/struct_lab.h"
#include "./../header/struct_ins.h"
#include "./../header/deplacement.h"

void sauver_lab(t_lab lab[X][Y]){
	int tmp;
	int i,j;
	FILE * fic1;
	fic1 = fopen("../doc/SAVED_GAME.txt", "w");

	while(!feof(fic1))
	{
		for(i =0; i<X; i++){
			for(j =0; j<Y; j++){
				lab[i][j].etat = tmp;
				lab[i][j].decouvert = unseen;
				fprintf(fic1, "%c %c ", &tmp, &unseen);

			}
			fprintf(fic1, "\n");
		}
	}
	fclose(fic1);
}
