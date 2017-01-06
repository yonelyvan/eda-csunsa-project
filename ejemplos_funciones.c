
/* ejemplo1 
    less_one.c
*/
/***compilacion  e intalacion

gcc -I /home/n/project/include -I /home/n/project/include/postgresql/server -fpic -c less_one.c
gcc -I /home/n/project/include -I /home/n/project/include/postgresql/server -shared -o less_one.so less_one.o 
cp less_one.so /home/n/project/lib

CREATE OR REPLACE FUNCTION less_one( int ) 
RETURNS int
AS '/home/n/project/lib/less_one.so', 'less_one'
LANGUAGE C STRICT;
*/

#include "postgres.h"
#include <string.h>
#include "fmgr.h"
#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif



PG_FUNCTION_INFO_V1(less_one);

Datum less_one( PG_FUNCTION_ARGS ){
	int32 a= PG_GETARG_INT32(0);
	PG_RETURN_INT32(a-1);
}
/* fin primer ejemplo */
