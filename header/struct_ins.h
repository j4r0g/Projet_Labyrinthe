/** \enum t_sexe
 * \struct t_fourmi ./header/struct_ins.h
*/
typedef enum {MALE, FEMELLE} t_sexe;
typedef struct {t_sexe sexe; int nourriture; int age; int x; int y;} t_fourmi;
#define Z 40
