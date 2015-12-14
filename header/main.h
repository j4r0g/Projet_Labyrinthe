void gene_ins(int bouffe, int dureevie, t_lab lab[X][Y], int i, t_fourmi fourmi[]);

void gene_nour(t_lab lab[X][Y]);

int genelab(t_lab lab[X][Y]);

void decouvrir(t_lab lab[X][Y]);

void afficher_lab(t_lab lab[X][Y]);

int verifvictoire(t_lab lab[X][Y]);

void deplacement (t_lab lab[X][Y], int pos_x, int pos_y);

int actionUser(t_lab lab[X][Y], int bouffe, int dureevie, t_fourmi fourmi[], int nb_ins);

int prochain_deplacement (int pos_x, int pos_y, t_lab lab[X][Y], t_fourmi fourmi[], int bouffe, int dureevie, int nb_ins);
