/***compilacion  e intalacion

gcc -I /home/yonel/project/include -I /home/yonel/project/include/postgresql/server -fpic -c insert_image.c
gcc -I /home/yonel/project/include -I /home/yonel/project/include/postgresql/server -shared -o insert_image.so insert_image.o 
cp insert_image.so /home/yonel/project/lib


CREATE OR REPLACE FUNCTION insert_image( int[], int ) 
RETURNS int
AS '/home/yonel/project/lib/insert_image.so', 'insert_image'
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
    int r=0;
    for (i = 0; i < arrayLength1; i++){
        r=r+arrayContent1[i];
    }
   

    
    t_id id= total_images;

    //nueva imagen
    v_feature vf= new_vector(D);
    vf[0]=arrayContent1[0];
    vf[1]=arrayContent1[1];
    vf[2]=arrayContent1[2];

    //vector caracteristico de  cada K
    vector_features_k vec_fk;
    vec_fk[0][0]=0.01;
    vec_fk[0][1]=0.01;
    vec_fk[0][2]=0.01;

    vec_fk[1][0]=10;
    vec_fk[1][1]=0;
    vec_fk[1][2]=0;
    
    vec_fk[2][0]=0;
    vec_fk[2][1]=10;
    vec_fk[2][2]=10;

    insert_img(id, vf,  vec_fk);

    for (t_int_loop i = 0; i < total_images+1; ++i){
        f_read(i);
    }

    printf("____________________________\n");

    PG_RETURN_INT32(r);
}
