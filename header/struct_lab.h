/**\enum t_discover
 * \enum t_etat
 * \struct t_lab ./header/struct_lab.h
*/
#define X 30
#define Y 60

typedef enum {unseen=0, seen=1} t_discover;
typedef enum {vide=' ', mur='#', food='*', insecte='%'} t_etat;

typedef struct {t_discover decouvert; t_etat etat; int insecte;} t_lab;
