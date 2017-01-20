#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define D 2  	// x,y
#define Kn 3 	//numero Ks
#define c 20 	//numero de caracteres nombre de la imagen
/*
	t_ dipo de dato
*/
typedef double t_distancia;
typedef char t_name;
typedef unsigned int t_id;
typedef unsigned int t_entero_loop;
typedef double t_feature;

typedef struct{
	t_distancia vector[Kn]; 
}v_distances;

typedef struct{
	t_distancia vector[D]; 
}v_features;

typedef struct{
	t_distancia matrix[Kn][D];
}VKn;

typedef struct _node node;
struct _node{
	t_id id; //identificador de objeto
	t_distancia vd[Kn]; //distancias a los K
};


void push_record(node *n); /*se inserta un record al final del archivo*/
void read(t_id id);/*lee un registro dado una clave id*/
v_distances f_compute_distance(v_features vf, VKn mK);/*retorna listancia del objeto a cada k*/
void insert(t_id id,v_features vf, VKn Ks);/*inserar en registro*/
void search(v_features vf);/*busqueda por radio*/




void insert(t_id id,v_features vf, VKn Ks){
	node n;
	v_distances vd=f_compute_distance( vf, Ks);
	n.id=id;
	for (int i = 0; i < Kn; ++i){
		n.vd[i]=vd.vector[i];
	}
	push_record(&n);
}

v_distances f_compute_distance(v_features vf, VKn mK){
	v_distances vd;
	for (t_entero_loop i = 0; i < Kn; ++i){
		t_distancia d=0;
		for (t_entero_loop j = 0; j < D; ++j){
			d+=pow( fabs(mK.matrix[i][j]-vf.vector[j]) ,2.0);
		}
		vd.vector[i]=sqrt(d);
	}
	return vd;
}

void push_record(node *n){ /*se inserta un record al final*/
	FILE *file;
	file = fopen("index.dat", "a");
	fseek( file, sizeof(node), SEEK_END);
	fwrite( n, sizeof(node), 1,file );
	fclose(file);
}

void read(t_id id){
	node node_;
	FILE* file;
	file = fopen("index.dat", "r");
	fseek( file, id*sizeof(node), SEEK_SET);
	fread( &node_, sizeof(node), 1,file );
	fclose(file);

	printf("id:%d\n", node_.id );
	for ( t_entero_loop i = 0; i < Kn; ++i ){
		printf("%f ", node_.vd[i] );	
	}
	printf("\n");
}