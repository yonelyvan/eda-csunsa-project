/*********************
*	t_ dipo de dato
**********************/
#define D 2  	// x,y
#define Kn 3 	//numero Ks

typedef double t_distancia;
typedef char t_name;
typedef unsigned int t_id;
typedef unsigned int t_entero_loop;
typedef unsigned int counter;
typedef double t_feature;
typedef unsigned int radio;

/* distancias entre un Objeto y un Ki */
typedef int* v_distance;
/* vector caracteristico */
typedef int* v_feature;
/* vectores caracteristicos de cada K */
typedef int matrix_kf[Kn][D];
/* nodeo a guardar en indice */
typedef struct _node node;
struct _node{
	t_id id; //identificador de objeto
	t_distancia vd[Kn]; //distancias a los K
};


void push_record(node *n); /*se inserta un record al final del archivo*/
void f_read(t_id id);/*lee un registro dado una clave id*/
v_distance f_compute_distance(v_feature vf, matrix_kf mK);/*retorna listancia del objeto a cada k*/
void insert(t_id id,v_feature vf, matrix_kf Ks);/*inserar en registro*/
void search( v_feature vf , radio r);/*busqueda k mas sercanos*/

