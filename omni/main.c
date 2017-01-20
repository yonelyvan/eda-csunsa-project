#include "omni.c"




/*
//ejemplo min heap
int main(){
	heap h;
	heap_init(&h);
	for (int i = 0; i < 100; i++) {
		heap_push(&h, rand()%10000);
	}
	for (int i = 0; i < 10; i++) {
		printf("%d\n", heap_front(&h) );
		heap_pop(&h);
	}
}
*/


/*

int main(){

	matrix_o_k Ki;
	Ki[0][0]=0;
	Ki[0][1]=10;

	Ki[1][0]=1;//1
	Ki[1][1]=1;
	
	Ki[2][0]=1;//1
	Ki[2][1]=10;

	v_feature vc=( v_feature )malloc(D);
	for (int i = 0; i < D; ++i){
		vc[i]=6*10.0;
	}
	//insert(5,vc,Ki);
	for (int i = 0; i < 4; ++i){
		f_read(i);
	}

	return 0;
}
*/








// ejemplo vectores ...
#define dim 3
int* get_vector(){
	int *v = (int *)malloc(dim);
	for (int i = 0; i < dim; ++i){
		v[i]=(i+1)*10;
	}
	return v;
}

int main(){

	int *v;
	v=get_vector();
	for (int i = 0; i < dim; ++i){
		printf("%d \n",v[i] );
	}
	return 0;
}
