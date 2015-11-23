#include <stdio.h>
#include <stdlib.h>
#include <maths.h>

typedef enum t_sexe {MALE, FEMELLE};
typedef struct {int num;  t_sexe sexe; int nourriture; int age;} t_fourmi;

void prochain_deplacement (t_fourmi fourmi, int pos_x, int pos_y) {
	if (t_lab[pos_x-1][pos_y-1] == 
