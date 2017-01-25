/*
    gcc -I /home/yonel/project/include -I /home/yonel/project/include/postgresql/server -fpic -c sumar.c
    gcc -I /home/yonel/project/include -I /home/yonel/project/include/postgresql/server -shared -o sumar.so sumar.o 
    cp sumar.so /home/yonel/project/lib




CREATE OR REPLACE FUNCTION suma( array1 int[] ) 
RETURNS int[]
AS '/home/yonel/project/lib/suma.so', 'suma'
LANGUAGE C STRICT;
*/


#include <postgres.h>
#include <fmgr.h>
#include <utils/array.h>

PG_MODULE_MAGIC;

//int4_array_add
Datum sumar(PG_FUNCTION_ARGS);

PG_FUNCTION_INFO_V1(sumar);

/**
 * Returns the sum of two int arrays.
 * by Matt Solnit on Stack Overflow - http://stackoverflow.com/questions/16992339
 */
Datum
sumar(PG_FUNCTION_ARGS){
    // The formal PostgreSQL array objects:
    ArrayType *array1, *array2;

    // The array element types (should always be INT4OID):
    Oid arrayElementType1, arrayElementType2;

    // The array element type widths (should always be 4):
    int16 arrayElementTypeWidth1, arrayElementTypeWidth2;

    // The array element type "is passed by value" flags (not used, should always be true):
    bool arrayElementTypeByValue1, arrayElementTypeByValue2;

    // The array element type alignment codes (not used):
    char arrayElementTypeAlignmentCode1, arrayElementTypeAlignmentCode2;

    // The array contents, as PostgreSQL "datum" objects:
    Datum *arrayContent1, *arrayContent2;

    // List of "is null" flags for the array contents:
    bool *arrayNullFlags1, *arrayNullFlags2;

    // The size of each array:
    int arrayLength1, arrayLength2;

    Datum* sumContent;
    int i;
    ArrayType* resultArray;

    if (PG_ARGISNULL(0) || PG_ARGISNULL(1))
      ereport(ERROR, (errmsg("Null arrays not accepted")));

    array1 = PG_GETARG_ARRAYTYPE_P(0);
    array2 = PG_GETARG_ARRAYTYPE_P(1);

    if (ARR_NDIM(array1) != 1 || ARR_NDIM(array2) != 1)
      ereport(ERROR, (errmsg("One-dimesional arrays are required")));

    arrayLength1 = (ARR_DIMS(array1))[0];
    if (arrayLength1 != (ARR_DIMS(array2))[0])
      ereport(ERROR, (errmsg("Arrays are of different lengths")));

    if (array_contains_nulls(array1) || array_contains_nulls(array2))
      ereport(ERROR, (errmsg("Array contains null elements")));

    // Determine the array element types.
    arrayElementType1 = ARR_ELEMTYPE(array1);
    get_typlenbyvalalign(arrayElementType1, &arrayElementTypeWidth1, &arrayElementTypeByValue1, &arrayElementTypeAlignmentCode1);
    arrayElementType2 = ARR_ELEMTYPE(array2);
    get_typlenbyvalalign(arrayElementType2, &arrayElementTypeWidth2, &arrayElementTypeByValue2, &arrayElementTypeAlignmentCode2);

    // Extract the array contents (as Datum objects).
    deconstruct_array(array1, arrayElementType1, arrayElementTypeWidth1, arrayElementTypeByValue1, arrayElementTypeAlignmentCode1, &arrayContent1, &arrayNullFlags1, &arrayLength1);
    deconstruct_array(array2, arrayElementType2, arrayElementTypeWidth2, arrayElementTypeByValue2, arrayElementTypeAlignmentCode2, &arrayContent2, &arrayNullFlags2, &arrayLength2);

    // Create a new array of sum results (as Datum objects).
    sumContent = palloc(sizeof(Datum) * arrayLength1);

    // Generate the sums.
    for (i = 0; i < arrayLength1; i++)
    {
      sumContent[i] = arrayContent1[i] + arrayContent2[i];
    }

    // Wrap the sums in a new PostgreSQL array object.
    resultArray = construct_array(sumContent, arrayLength1, arrayElementType1, arrayElementTypeWidth1, arrayElementTypeByValue1, arrayElementTypeAlignmentCode1);

    // Return the final PostgreSQL array object.
    PG_RETURN_ARRAYTYPE_P(resultArray);
}