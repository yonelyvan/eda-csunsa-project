#define D 3
#define K 3

typedef double t_distancia;
typedef double t_feature;
typedef double radio;
typedef unsigned int t_id;
typedef unsigned int count;
typedef unsigned int t_int_loop;
typedef unsigned int t_integer;

typedef double type;

/* distancias entre un Objeto y un Ki */
typedef double* v_distance;
/* vector caracteristico */
typedef double* v_feature;
/*vector de los ids de cada imagen*/
typedef unsigned int* v_id;
/*index*/
typedef double** omni_matrix; 
/* vectores caracteristicos de cada K */
typedef double vector_features_k[K][D];
/* nodeo a guardar en indice */
typedef struct _node node;
struct _node{
	t_id id; //identificador de objeto
	t_distancia vd[K]; //distancias a los K
};


void cargar_index_omni( t_integer num_imgs );
v_distance f_compute_distance(v_feature vf, vector_features_k vfk);
void insert_img(t_id id,v_feature vf, vector_features_k _vfk);
v_id search(v_feature vf , radio r);


/*registros*/
void push_record(node *n);
node get_record(t_id id);

/* utilities*/
type** new_matrix(t_integer rows, t_integer cols);
type* new_vector(t_integer n);
t_id* new_vector_ids(t_id n);

