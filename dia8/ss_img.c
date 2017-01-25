/***compilacion  e intalacion

gcc -I /home/micaela/project/include -I /home/micaela/project/include/postgresql/server -fpic -c ss_img.c
gcc -I /home/micaela/project/include -I /home/micaela/project/include/postgresql/server -shared -o ss_img.so ss_img.o 
cp ss_img.so /home/micaela/project/lib



CREATE OR REPLACE FUNCTION ss_img(IN int[], IN integer , IN integer, OUT f1 integer, OUT f2 integer)
RETURNS SETOF record
AS '/home/micaela/project/lib/ss_img.so', 'ss_img'
LANGUAGE C IMMUTABLE STRICT;


*/
#include "postgres.h"
#include <string.h>
#include "fmgr.h"
#include "funcapi.h"
#include <utils/array.h>
#include "omni.c"
#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

PG_FUNCTION_INFO_V1(ss_img);

Datum ss_img(PG_FUNCTION_ARGS){
    FuncCallContext     *funcctx;
    int                  call_cntr;
    int                  max_calls;
    TupleDesc            tupdesc;
    AttInMetadata       *attinmeta;

    /*recibir array*/
    Oid arrayElementType1;
    int16 arrayElementTypeWidth1;
    ArrayType *array1;
    Datum *arrayContent1;
    bool arrayElementTypeByValue1;
    // The array element type alignment codes (not used):
    char arrayElementTypeAlignmentCode1; 
    bool *arrayNullFlags1;
    // The size of each array:
    int arrayLength1;

    array1 = PG_GETARG_ARRAYTYPE_P(0);
    arrayElementType1 = ARR_ELEMTYPE(array1);
    get_typlenbyvalalign(arrayElementType1, &arrayElementTypeWidth1, &arrayElementTypeByValue1, &arrayElementTypeAlignmentCode1);
    // Extract the array contents (as Datum objects).
    deconstruct_array(array1, arrayElementType1, arrayElementTypeWidth1, arrayElementTypeByValue1, arrayElementTypeAlignmentCode1, &arrayContent1, &arrayNullFlags1, &arrayLength1);
    

     /*********************************/
    count radio=PG_GETARG_UINT32(1);
    count total_imagenes=PG_GETARG_UINT32(2);
	//nueva imagen
	v_feature vf= new_vector(D);
	
	for (int i = 0; i < D; ++i){
		vf[i] = arrayContent1[i];
	}
    
    printf("\n");

    printf("mediad del array consulta: %d\n", arrayLength1 );

	//vector caracteristico de  cada K
    t_feature vk1[256]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    t_feature vk2[256]={0, 29, 98, 919, 2792, 1152, 234, 529, 773, 1873, 5204, 3831, 888, 342, 602, 909, 1061, 943, 931, 830, 595, 347, 211, 128, 116, 96, 86, 82, 84, 86, 84, 90, 82, 79, 84, 81, 69, 81, 71, 70, 75, 61, 72, 61, 66, 63, 57, 61, 51, 52, 64, 54, 57, 50, 46, 51, 52, 51, 45, 49, 44, 52, 49, 50, 51, 41, 36, 44, 40, 39, 37, 42, 44, 44, 34, 34, 28, 32, 30, 30, 31, 24, 25, 28, 29, 29, 23, 25, 27, 26, 25, 25, 23, 24, 27, 25, 22, 20, 20, 19, 22, 21, 18, 22, 20, 18, 19, 17, 17, 18, 14, 17, 17, 14, 16, 15, 12, 15, 14, 14, 16, 13, 13, 16, 14, 12, 12, 12, 10, 11, 12, 10, 12, 9, 10, 9, 10, 8, 11, 8, 6, 9, 10, 9, 5, 6, 7, 9, 6, 9, 10, 6, 5, 5, 8, 7, 4, 6, 8, 4, 7, 4, 5, 7, 6, 5, 2, 5, 6, 7, 6, 4, 4, 7, 5, 6, 5, 7, 3, 6, 2, 5, 5, 3, 3, 3, 2, 4, 4, 2, 4, 3, 3, 3, 2, 5, 5, 3, 3, 5, 2, 2, 1, 1, 4, 2, 2, 1, 1, 0, 1, 1, 2, 3, 1, 1, 3, 0, 1, 1, 1, 1, 1, 0, 1, 2, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    t_feature vk3[256]={60,65,193,218,194,192,194,170,127,109,91,97,87,86,83,93,88,78,77,77,81,86,84,82,97,101,83,89,78,82,98,97,84,81,76,60,70,80,101,85,81,84,129,143,159,154,166,193,147,187,187,169,138,179,154,156,174,175,137,151,128,113,109,93,107,104,96,87,93,97,88,82,68,61,61,72,72,62,62,58,67,58,56,61,65,75,72,72,76,78,93,97,109,114,105,89,77,88,91,92,102,98,99,111,110,117,118,129,138,131,127,140,129,129,126,129,143,135,136,142,155,155,154,177,161,166,164,163,190,184,169,168,172,157,167,159,161,149,140,140,133,138,139,145,129,135,140,137,132,137,135,129,126,132,113,117,111,94,85,98,80,82,80,79,71,69,71,64,63,64,54,56,50,59,64,63,63,57,61,57,58,71,77,71,66,71,65,60,59,66,67,59,55,60,69,66,62,71,58,68,67,60,76,65,83,87,84,91,95,103,106,95,99,86,78,79,90,109,82,90,83,76,72,68,68,48,58,56,53,49,48,52,43,33,44,36,33,33,28,22,25,24,18,15,23,23,21,18,22,25,38,55,82,145,225,96};


    for (int i = 0; i < D; ++i){
        vfk[0][i]=vk1[i];
        vfk[1][i]=vk2[i];
        vfk[2][i]=vk3[i];
    }
	cargar_index_omni(total_imagenes);
	v_id vids=search(vf,radio);
	printf("total_result:::: %d \n",total_result);

	v_id v_ids_result= new_vector_ids(total_result);
	for (int i = 0; i < total_result; ++i){
		v_ids_result[i] = vids[i];
	}
    printf("__________________________________________________\n");
    /*********************************/

    if (SRF_IS_FIRSTCALL()){/* stuff done only on the first call of the function */
        MemoryContext   oldcontext;
        funcctx = SRF_FIRSTCALL_INIT();/* create a function context for cross-call persistence */
        oldcontext = MemoryContextSwitchTo(funcctx->multi_call_memory_ctx); /* switch to memory context appropriate for multiple function calls */
        funcctx->max_calls = total_result;//PG_GETARG_UINT32(0);/* total number of tuples to be returned */
        if (get_call_result_type(fcinfo, NULL, &tupdesc) != TYPEFUNC_COMPOSITE) /* Build a tuple descriptor for our result type */
            ereport(ERROR, (errcode(ERRCODE_FEATURE_NOT_SUPPORTED), errmsg("function returning record called in context that cannot accept type record")));
        attinmeta = TupleDescGetAttInMetadata(tupdesc);
        funcctx->attinmeta = attinmeta;
        MemoryContextSwitchTo(oldcontext);
    }
   
    funcctx = SRF_PERCALL_SETUP();/* stuff done on every call of the function */
    call_cntr = funcctx->call_cntr;
    max_calls = funcctx->max_calls;
    attinmeta = funcctx->attinmeta;

	
    
    if (call_cntr < max_calls){
        char       **values;
        HeapTuple    tuple;
        Datum        result;

        values = (char **) palloc(2 * sizeof(char *));/*3->4*/
        values[0] = (char *) palloc(16 * sizeof(char));
        values[1] = (char *) palloc(16 * sizeof(char));

        snprintf(values[0], 16, "%d", call_cntr );
        snprintf(values[1], 16, "%d", v_ids_result[call_cntr]  );
     
        tuple = BuildTupleFromCStrings(attinmeta, values);/* build a tuple */
        result = HeapTupleGetDatum(tuple);/* make the tuple into a datum */
        /* clean up (this is not really necessary) */
        pfree(values[0]);
        pfree(values[1]); 

        pfree(values);

        SRF_RETURN_NEXT(funcctx, result);
    }
    else{/* do when there is no more left */
        SRF_RETURN_DONE(funcctx);
    }
}