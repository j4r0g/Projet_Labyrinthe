#define INFINI 10000

void deplacement (t_lab lab[X][Y], int pos_x, int pos_y);

int pluscourte_dist(t_lab labyrinthe[X][Y], int xdep, int ydep, int xarr, int yarr);

void gene_ins(int bouffe, int dureevie, t_lab lab[X][Y], t_fourmi fourmi[], int nb_ins);

int combat(int x, int y, int a, int b, int bouffe, int dureevie, t_lab lab[X][Y], t_fourmi fourmi[], int nb_ins);
