void gene_deb(int bouffe, int dureevie, t_lab lab[X][Y], int i, t_fourmi fourmi[]);

int genelab(t_lab lab[X][Y]);

void decouvrir(int maxx, int maxy, t_lab lab[maxx][maxy]);

void afficher_lab(t_lab lab[X][Y]);

int verifvictoire(int maxx, int maxy, t_lab lab[maxx][maxy]);

void deplacement (t_lab lab[X][Y], int pos_x, int pos_y);

int actionUser(int maxx, int maxy, t_lab lab[maxx][maxy], int bouffe, int dureevie, t_fourmi fourmi[], int nb_ins);
