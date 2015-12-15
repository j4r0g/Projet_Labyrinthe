#define INFINI 10000

void deplacement (t_lab lab[X][Y], int pos_x, int pos_y, t_fourmi fourmi[]);

int pluscourte_dist(t_lab labyrinthe[X][Y], int xdep, int ydep, int xarr, int yarr, int *, int*);

void gene_ins_deb(int bouffe, int dureevie, t_lab lab[X][Y], t_fourmi fourmi[]);

int gene_ins(int bouffe, int dureevie, t_lab lab[X][Y], int nb_ins, int a, int b, t_fourmi fourmi[]);

int combat(int x, int y, int a, int b, int bouffe, int dureevie, t_lab lab[X][Y], t_fourmi fourmi[]);

void bebe(int bouffe, int dureevie, t_lab lab[X][Y], t_fourmi fourmi[]);

int modifpos(t_lab lab[X][Y], t_fourmi fourmi[], int x, int y, int a, int b);
