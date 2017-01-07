/***compilacion  e intalacion

gcc -I /home/n/project/include -I /home/n/project/include/postgresql/server -fpic -c maximo.c
gcc -I /home/n/project/include -I /home/n/project/include/postgresql/server -shared -o maximo.so maximo.o 
cp maximo.so /home/n/project/lib


CREATE OR REPLACE FUNCTION maximo( int ) 
RETURNS int
AS '/home/n/project/lib/maximo.so', 'maximo'
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
	if( a>b ){
		PG_RETURN_INT32(a);
	}
	else{
		PG_RETURN_INT32(b);	
	}
	
}
