#include "omni.c"



/*
int main(){
	count total_imagenes=5;
	t_id id=total_imagenes-1;

	//nueva imagen
	v_feature vf= new_vector(D);
	vf[0]=0;
	vf[1]=0;

	//vector caracteristico de  cada K
	//vector_features_k vec_fk;
	vfk[0][0]=0.01;
	vfk[0][1]=0.01;

	vfk[1][0]=10;
	vfk[1][1]=0;
	
	vfk[2][0]=0;
	vfk[2][1]=10;

	cargar_index_omni(total_imagenes);
	v_id vids=search(vf,2);

	
	for (int i = 0; i < total_result; ++i){
		printf(" %d",vids[i] );
	}
	printf("\n");

	//for (t_int_loop i = 0; i < total_imagenes; ++i){ f_read(i); }

	return 0;
}
*/



int main(){
	count total_imagenes=3;
	t_id id=total_imagenes-1;

	//nueva imagen
	v_feature vf= new_vector(D);
	for (int i = 0; i < D; ++i){
		vf[i]=id;
	}

	//vector caracteristico de  cada K
	vector_features_k vec_fk;
	for (int i = 0; i < K; ++i){
		for (int j = 0; j < D; ++j){
			vec_fk[i][j]=rand()%100;
		}
	}


	insert_img(id, vf,  vec_fk);
	for (t_int_loop i = 0; i < total_imagenes; ++i){ f_read(i); }
	return 0;
}

