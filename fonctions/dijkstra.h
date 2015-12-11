#define INFINI 10000
#define X 30
#define Y 60

typedef enum {MALE, FEMELLE} t_sexe;
typedef struct {t_sexe sexe; int nourriture; int age;} t_fourmi;

typedef enum {haut = 0, bas = 1, gauche = 2, droite = 3} t_direction;
typedef enum {unseen=0, seen=1} t_discover;
typedef enum {vide=' ', mur='#', food='*', insecte='%'} t_etat;

typedef struct {t_discover decouvert; t_etat etat; int insecte;} t_lab;

void deplacement (t_lab lab[X][Y], int pos_x, int pos_y);

int pluscourte_dist(t_lab labyrinthe[X][Y], int xdep, int ydep, int xarr, int yarr);
