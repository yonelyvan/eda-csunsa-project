#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "omni.h"
#include "heap.c"


counter cont; /*numero total de objetos*/
matrix_kf _matrix_kf;

/*
void search(v_feature vf , radio r){
	for (t_entero_loop i = 0; i < D; ++i){
		for (t_entero_loop i = 0; i < cont; ++i){
			//f_compute_distance(vf,_matrix_kf);
		}
	}
}
*/


void insert(t_id id,v_feature vf, matrix_kf Ks){
	node n;
	v_distance vd=f_compute_distance( vf, Ks);
	n.id=id;
	for (int i = 0; i < Kn; ++i){
		n.vd[i]=vd[i];
	}
	push_record(&n);
}


v_distance f_compute_distance(v_feature vf, matrix_kf mK){
	v_distance vd = ( v_distance )malloc(Kn);
	for (t_entero_loop i = 0; i < Kn; ++i){
		t_distancia d=0;
		for (t_entero_loop j = 0; j < D; ++j){
			d+=pow( fabs(mK[i][j]-vf[j]) ,2.0);
		}
		vd[i]=sqrt(d);
	}
	return vd;
}





void push_record(node *n){ //se inserta un record al final
	FILE *file;
	file = fopen("index.dat", "a");
	fseek( file, sizeof(node), SEEK_END);
	fwrite( n, sizeof(node), 1,file );
	fclose(file);
}


void f_read(t_id id){
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