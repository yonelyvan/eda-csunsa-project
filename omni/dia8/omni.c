/*
cargar indice en variables globales
ejecutar insert y busqueda
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "omni.h"

t_integer total_imgs;//numero total de imagenes o contador de imagenes
v_id vid;//
vector_features_k vfk;//vectores caracteristicos de cada K
omni_matrix omni_m; //dicatncias de cada imagen a cada K
count total_result;

void cargar_index_omni( t_integer num_imgs ){
	total_imgs = num_imgs;
	/*cargar index*/
	vid = new_vector_ids(num_imgs);
	omni_m = new_matrix(num_imgs,K);
	node n;
	printf("cargando ...\n");
	for (int i = 0; i < num_imgs; ++i){
		n=get_record(i);
		vid[i]=n.id;
		printf("id: %d :",n.id);
		for (int j = 0; j < K; ++j){
			omni_m[i][j]=n.vd[j];
			printf("%f ", n.vd[j]);
		}
		printf("\n");
	}
	printf("fin..............\n");
}




/*
distancias [k1, k2, k3] dado [D1, D2] y [[k1.x, k1y] [k2][k3]]
*/
v_distance f_compute_distance(v_feature vf, vector_features_k v_fk){
	v_distance vd = new_vector(K);
	for ( t_int_loop i = 0; i < K; ++i ){
		t_distancia d=0.0;
		for (t_int_loop j = 0; j < D; ++j){
			d+=pow( v_fk[i][j]-vf[j] ,2.0); //fabs()
			//printf("vc de k:::::%f\n", v_fk[i][j]);
			//printf("df image::::%f\n", vf[j]);
		}
		vd[i]=sqrt(d);
	}
	return vd;
}

void insert_img(t_id id,v_feature vf, vector_features_k _vfk){
	node n;
	v_distance vd=f_compute_distance( vf, _vfk);
	n.id=id;
	for (int i = 0; i < K; ++i){
		n.vd[i]=vd[i];
	}
	push_record(&n);
}

v_id search(v_feature vf , radio r){
	total_result=0;
	v_id vids=new_vector_ids(total_imgs);
	v_distance vd;
	vd=f_compute_distance(vf,vfk);//distancia del objeto consulta a cada K  
	printf("distancias k1:%f  k2:%f  k3:%f\n", vd[0], vd[1], vd[2] );

	for (t_int_loop i = 0; i < total_imgs; ++i){
		int b=1;
		for (t_int_loop j = 0; j < K; ++j){	
			if(  !((vd[j]-r <= omni_m[i][j]) &&  (omni_m[i][j] <= vd[j]+r)) ){
				b=0;
				break;
			}	
		}
		if( b ){
			vids[total_result]=i;
			total_result=total_result+1;
			printf("img id=%d\n", i );
			printf("%f  %f  %f \n",omni_m[i][0], omni_m[i][1], omni_m[i][2] );
		}
	}
	return vids;
}













/**************registros****************/
void push_record(node *n){ //se inserta un record al final
	FILE *file;
	file = fopen("index.dat", "a");
	if(!file) {
       printf("El fichero no existe o no puede ser abierto.\n");
    }
	fseek( file, sizeof(node), SEEK_END);
	fwrite( n, sizeof(node), 1,file );
	fclose(file);
}

/*obtener registro*/
node get_record(t_id id){
	node node_;
	FILE* file;
	file = fopen("index.dat", "r");
	fseek( file, id*sizeof(node), SEEK_SET);
	fread( &node_, sizeof(node), 1,file );
	fclose(file);
	return node_;
}

void f_read(t_id id){
	node node_;
	FILE* file;
	file = fopen("index.dat", "r");
	fseek( file, id*sizeof(node), SEEK_SET);
	fread( &node_, sizeof(node), 1,file );
	fclose(file);

	printf("id:%d\n", node_.id );
	for ( t_int_loop i = 0; i < K; ++i ){
		printf("%f ", node_.vd[i] );	
	}
	printf("\n");
}


/************************** utilities*****************/
type** new_matrix(t_integer rows, t_integer cols){
	type **matrix=(type**) malloc( rows*sizeof(type*));
	for (t_int_loop i=0;  i<rows; ++i){
		matrix[i]=(type*) malloc(cols*sizeof(type));
	}
	return matrix;
}

type* new_vector(t_integer n){
	type *v=(type*) malloc( n*sizeof(type));
	return v;
}

t_id* new_vector_ids(t_id n){
	t_id *v = (t_id*) malloc( n*sizeof(t_id) );
	return v;
}