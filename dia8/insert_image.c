/***compilacion  e intalacion

gcc -I /home/micaela/project/include -I /home/micaela/project/include/postgresql/server -fpic -c insert_image.c
gcc -I /home/micaela/project/include -I /home/micaela/project/include/postgresql/server -shared -o insert_image.so insert_image.o 
cp insert_image.so /home/micaela/project/lib


CREATE OR REPLACE FUNCTION insert_image( int[], int ) 
RETURNS int
AS '/home/micaela/project/lib/insert_image.so', 'insert_image'
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
  
    t_id id= total_images;

    //nueva imagen
    v_feature vf= new_vector(D);
    for (t_int_loop i = 0; i < D; ++i){
        vf[i]=arrayContent1[i];
    }
    
    //vector caracteristico de  cada K
    vector_features_k vec_fk;
    t_feature vk1[256]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    t_feature vk2[256]={0, 29, 98, 919, 2792, 1152, 234, 529, 773, 1873, 5204, 3831, 888, 342, 602, 909, 1061, 943, 931, 830, 595, 347, 211, 128, 116, 96, 86, 82, 84, 86, 84, 90, 82, 79, 84, 81, 69, 81, 71, 70, 75, 61, 72, 61, 66, 63, 57, 61, 51, 52, 64, 54, 57, 50, 46, 51, 52, 51, 45, 49, 44, 52, 49, 50, 51, 41, 36, 44, 40, 39, 37, 42, 44, 44, 34, 34, 28, 32, 30, 30, 31, 24, 25, 28, 29, 29, 23, 25, 27, 26, 25, 25, 23, 24, 27, 25, 22, 20, 20, 19, 22, 21, 18, 22, 20, 18, 19, 17, 17, 18, 14, 17, 17, 14, 16, 15, 12, 15, 14, 14, 16, 13, 13, 16, 14, 12, 12, 12, 10, 11, 12, 10, 12, 9, 10, 9, 10, 8, 11, 8, 6, 9, 10, 9, 5, 6, 7, 9, 6, 9, 10, 6, 5, 5, 8, 7, 4, 6, 8, 4, 7, 4, 5, 7, 6, 5, 2, 5, 6, 7, 6, 4, 4, 7, 5, 6, 5, 7, 3, 6, 2, 5, 5, 3, 3, 3, 2, 4, 4, 2, 4, 3, 3, 3, 2, 5, 5, 3, 3, 5, 2, 2, 1, 1, 4, 2, 2, 1, 1, 0, 1, 1, 2, 3, 1, 1, 3, 0, 1, 1, 1, 1, 1, 0, 1, 2, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    t_feature vk3[256]={60,65,193,218,194,192,194,170,127,109,91,97,87,86,83,93,88,78,77,77,81,86,84,82,97,101,83,89,78,82,98,97,84,81,76,60,70,80,101,85,81,84,129,143,159,154,166,193,147,187,187,169,138,179,154,156,174,175,137,151,128,113,109,93,107,104,96,87,93,97,88,82,68,61,61,72,72,62,62,58,67,58,56,61,65,75,72,72,76,78,93,97,109,114,105,89,77,88,91,92,102,98,99,111,110,117,118,129,138,131,127,140,129,129,126,129,143,135,136,142,155,155,154,177,161,166,164,163,190,184,169,168,172,157,167,159,161,149,140,140,133,138,139,145,129,135,140,137,132,137,135,129,126,132,113,117,111,94,85,98,80,82,80,79,71,69,71,64,63,64,54,56,50,59,64,63,63,57,61,57,58,71,77,71,66,71,65,60,59,66,67,59,55,60,69,66,62,71,58,68,67,60,76,65,83,87,84,91,95,103,106,95,99,86,78,79,90,109,82,90,83,76,72,68,68,48,58,56,53,49,48,52,43,33,44,36,33,33,28,22,25,24,18,15,23,23,21,18,22,25,38,55,82,145,225,96};


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
