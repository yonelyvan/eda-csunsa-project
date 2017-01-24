/***compilacion  e intalacion

gcc -I /home/yonel/project/include -I /home/yonel/project/include/postgresql/server -fpic -c maximo.c
gcc -I /home/yonel/project/include -I /home/yonel/project/include/postgresql/server -shared -o maximo.so maximo.o 
cp maximo.so /home/yonel/project/lib


CREATE OR REPLACE FUNCTION maximo( int ,int ) 
RETURNS int
AS '/home/yonel/project/lib/maximo.so', 'maximo'
LANGUAGE C STRICT;

*/

#include "postgres.h"
#include <string.h>
#include "fmgr.h"
#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif



PG_FUNCTION_INFO_V1(maximo);


Datum maximo( PG_FUNCTION_ARGS ){
	int32 a = PG_GETARG_INT32(0);
	int32 b = PG_GETARG_INT32(1);
	printf("comparando\n");
	if( a>b ){
		PG_RETURN_INT32(a);
	}
	else{
		PG_RETURN_INT32(b);	
	}
	
}
