void gene_ins_deb(int bouffe, int dureevie, t_lab lab[X][Y], t_fourmi fourmi[]);

void gene_nour(t_lab lab[X][Y]);

int genelab(t_lab lab[X][Y]);

void decouvrir(t_lab lab[X][Y]);

void afficher_lab(t_lab lab[X][Y]);

void deplacement (t_lab lab[X][Y], int pos_x, int pos_y,  t_fourmi fourmi[]);

int actionUser(t_lab lab[X][Y], int bouffe, int dureevie, t_fourmi fourmi[]);

int prochain_deplacement (int pos_x, int pos_y, t_lab lab[X][Y], int bouffe, int dureevie, t_fourmi fourmi[]);

void sauver_lab(t_lab lab[X][Y]);
