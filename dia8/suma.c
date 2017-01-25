/***compilacion  e intalacion

gcc -I /home/yonel/project/include -I /home/yonel/project/include/postgresql/server -fpic -c suma.c
gcc -I /home/yonel/project/include -I /home/yonel/project/include/postgresql/server -shared -o suma.so suma.o 
cp suma.so /home/yonel/project/lib




CREATE OR REPLACE FUNCTION suma( array1 int[] ) 
RETURNS int
AS '/home/yonel/project/lib/suma.so', 'suma'
LANGUAGE C STRICT;



*/

#include "postgres.h"
#include <string.h>
#include "fmgr.h"
#include <fmgr.h>
#include <utils/array.h>
#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif


/*suma de lso elementdos de un vector*/
PG_FUNCTION_INFO_V1(suma);
Datum suma( PG_FUNCTION_ARGS ){
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
  	// Determine the array element types.
  	arrayElementType1 = ARR_ELEMTYPE(array1);
  	get_typlenbyvalalign(arrayElementType1, &arrayElementTypeWidth1, &arrayElementTypeByValue1, &arrayElementTypeAlignmentCode1);
  	// Extract the array contents (as Datum objects).
  	deconstruct_array(array1, arrayElementType1, arrayElementTypeWidth1, arrayElementTypeByValue1, arrayElementTypeAlignmentCode1, &arrayContent1, &arrayNullFlags1, &arrayLength1);
   	int r=0;
  	for (i = 0; i < arrayLength1; i++){
  		r=r+arrayContent1[i];
  	}

  	printf("test 333\n");

  	PG_RETURN_INT32(r);
}
