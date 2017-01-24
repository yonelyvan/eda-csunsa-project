/***compilacion  e intalacion

gcc -I /home/n/project/include -I /home/n/project/include/postgresql/server -fpic -c insert_image.c
gcc -I /home/n/project/include -I /home/n/project/include/postgresql/server -shared -o insert_image.so insert_image.o 
cp insert_image.so /home/n/project/lib


CREATE OR REPLACE FUNCTION insert_image( int[], int ) 
RETURNS int
AS '/home/n/project/lib/insert_image.so', 'insert_image'
LANGUAGE C STRICT;

*/

#include "postgres.h"
#include <string.h>
#include "fmgr.h"
#include "omni.c"
#include <fmgr.h>
#include <utils/array.h>
#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif


/*insert_image de lso elementdos de un vector*/
PG_FUNCTION_INFO_V1(insert_image);
Datum insert_image( PG_FUNCTION_ARGS ){
    // The formal PostgreSQL array objects:
    ArrayType *array1;
    // The array element types (should always be INT4OID):
    Oid arrayElementType1;
    // The array element type widths (should always be 4):
    int16 arrayElementTypeWidth1;
    // The array element type "is passed by value" flags (not used, should always be true):
    bool arrayElementTypeByValue1;
    // The array element type alignment codes (not used):
    char arrayElementTypeAlignmentCode1; 
    // The array contents, as PostgreSQL "datum" objects:
    Datum *arrayContent1;
    // List of "is null" flags for the array contents:
    bool *arrayNullFlags1;
    // The size of each array:
    int arrayLength1;
    //Datum* sumContent;
    int i;
    // Extract the PostgreSQL arrays from the parameters passed to this function call.
    array1 = PG_GETARG_ARRAYTYPE_P(0);
    int total_images = PG_GETARG_INT32(1);
    // Determine the array element types.
    arrayElementType1 = ARR_ELEMTYPE(array1);
    get_typlenbyvalalign(arrayElementType1, &arrayElementTypeWidth1, &arrayElementTypeByValue1, &arrayElementTypeAlignmentCode1);
    // Extract the array contents (as Datum objects).
    deconstruct_array(array1, arrayElementType1, arrayElementTypeWidth1, arrayElementTypeByValue1, arrayElementTypeAlignmentCode1, &arrayContent1, &arrayNullFlags1, &arrayLength1);
    /*int r=0;
    for (i = 0; i < arrayLength1; i++){
        r=r+arrayContent1[i];
    }*/
   

    
    t_id id= total_images;

    //nueva imagen
    v_feature vf= new_vector(D);
    for (t_int_loop i = 0; i < D; ++i){
        vf[i]=arrayContent1[i];
    }


    //vector caracteristico de  cada K
    vector_features_k vec_fk;

    t_feature vk1[256]={0,74,628,3207,3330,903,894,2417,4896,4095,3634,1094,480,362,380,322,275,230,186,144,102,83,68,51,48,41,44,35,36,28,21,26,21,20,25,18,21,12,19,17,16,21,15,18,16,10,14,12,11,14,13,10,9,10,11,13,12,9,12,9,9,10,10,12,11,5,10,11,11,10,8,11,10,10,10,5,7,8,10,9,10,10,9,10,10,11,8,7,5,8,7,7,8,6,9,8,9,7,3,9,6,7,11,8,7,6,9,7,10,8,6,6,9,9,10,8,9,9,16,10,14,13,10,11,12,10,11,9,10,11,12,7,11,9,11,11,6,7,10,9,10,9,12,9,9,12,11,5,6,8,10,9,6,11,8,6,7,9,8,7,7,10,6,6,8,7,9,8,8,5,8,5,7,9,8,8,6,6,3,8,6,11,10,7,5,9,6,4,8,6,9,7,5,9,6,7,3,8,3,3,5,5,5,6,2,7,5,5,5,4,6,3,4,4,6,5,5,5,3,6,2,4,3,5,4,3,5,3,5,2,3,1,1,3,3,2,2,2,2,2,1,1,1,2,2,1,2,3,2,1,2,2,2,4,16,2};
    t_feature vk2[256]={9,55,299,1484,2321,906,290,867,1958,2982,2467,1610,879,373,156,143,163,217,266,313,284,286,287,270,197,116,96,72,63,59,52,50,58,60,70,63,62,67,68,58,63,73,65,66,62,63,66,62,54,54,53,46,38,52,36,40,35,32,33,34,40,33,30,36,39,37,38,34,34,34,33,33,44,34,37,46,45,46,40,44,47,40,47,43,43,48,52,46,48,49,45,51,50,50,50,50,62,48,57,53,48,56,58,58,64,59,54,51,62,53,48,45,47,42,42,45,56,44,43,48,47,42,43,42,35,39,38,42,42,41,36,39,31,44,38,34,41,48,44,42,39,42,45,39,43,46,46,49,46,56,52,58,50,47,39,45,47,43,47,45,44,47,41,47,38,44,37,33,33,41,34,38,37,38,36,35,39,37,32,31,30,25,24,33,30,31,28,29,33,32,25,30,30,29,28,27,27,28,33,27,31,33,29,29,34,33,32,29,30,29,32,33,31,29,32,34,32,36,37,44,40,36,37,42,45,45,46,55,49,50,45,51,57,59,59,62,62,55,56,55,43,51,50,45,40,43,54,45,52,55,54,64,68,101,316,226};
    t_feature vk3[256]={0,50,373,2311,2002,518,506,1694,3129,4186,2808,1071,647,691,778,823,771,681,572,541,457,369,281,228,189,143,118,106,77,65,74,69,76,71,82,73,80,76,65,74,81,72,68,56,50,49,43,42,42,44,42,42,54,48,44,53,42,43,57,49,45,47,33,34,36,36,36,32,41,34,44,33,41,39,31,33,32,31,32,30,27,24,24,22,18,15,15,19,15,16,11,11,9,11,9,6,11,11,9,7,10,11,9,11,9,12,7,10,7,11,11,10,12,12,12,6,11,6,10,7,9,10,9,10,8,9,7,11,8,9,4,9,5,10,10,9,8,8,12,8,5,11,6,9,7,9,9,7,7,7,9,7,6,7,5,8,7,5,6,8,5,6,5,5,4,5,6,4,4,5,4,3,5,5,4,4,5,3,5,4,2,6,7,7,2,3,5,5,5,2,3,4,2,4,6,3,5,3,3,4,6,4,7,4,4,3,3,5,7,8,6,6,6,4,6,7,2,6,8,4,5,4,8,8,6,7,9,8,15,16,9,10,10,13,8,10,9,10,10,5,4,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0};
    for (t_int_loop i = 0; i < D; ++i){
        vec_fk[0][i]=vk1[i];
        vec_fk[1][i]=vk2[i];
        vec_fk[2][i]=vk3[i];
    }

    insert_img(id, vf,  vec_fk);

    for (t_int_loop i = 0; i < total_images+1; ++i){
        f_read(i);
    }

    printf("____________________________\n");
}
