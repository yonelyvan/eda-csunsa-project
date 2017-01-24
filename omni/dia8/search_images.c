/***compilacion  e intalacion
gcc -I /home/n/project/include -I /home/n/project/include/postgresql/server -fpic -c search_images.c
gcc -I /home/n/project/include -I /home/n/project/include/postgresql/server -shared -o search_images.so search_images.o 
cp search_images.so /home/n/project/lib




CREATE FUNCTION search_images(anyarray, integer, bool)
RETURNS SETOF int
AS '/home/n/project/lib/search_images.so'
LANGUAGE C STRICT;


*/

#include "postgres.h"
#include <string.h>
#include "fmgr.h"
#include "funcapi.h"
#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif




typedef struct generate_iterator_fctx{
        int    lower;
        int    upper;
        bool    reverse;
} generate_iterator_fctx;

Datum search_images(PG_FUNCTION_ARGS);
PG_FUNCTION_INFO_V1(search_images);

/* 
 * search_images(array anyarray, dim int, reverse bool)
 */
Datum search_images(PG_FUNCTION_ARGS){
        FuncCallContext *funcctx;
        MemoryContext oldcontext;
        generate_iterator_fctx *fctx;

        /* stuff done only on the first call of the function */
        if ( SRF_IS_FIRSTCALL() ){
            ArrayType *v = PG_GETARG_ARRAYTYPE_P(0);
                int reqdim;
                int *lb, *dimv;

                /* create a function context for cross-call persistence */
                funcctx = SRF_FIRSTCALL_INIT();

                reqdim = (PG_NARGS()  MAXDIM)
                        SRF_RETURN_DONE(funcctx);

                /* Sanity check: was the requested dim valid */
                if (reqdim  ARR_NDIM(v)){
                    SRF_RETURN_DONE(funcctx);
                }
                        
                /*
                 * switch to memory context appropriate for multiple function calls
                 */
                oldcontext = MemoryContextSwitchTo(funcctx->multi_call_memory_ctx);
                fctx = (generate_iterator_fctx *) palloc(sizeof(generate_iterator_fctx));

                lb = ARR_LBOUND(v);
                dimv = ARR_DIMS(v);

                fctx->lower = lb[reqdim - 1];
                fctx->upper = dimv[reqdim - 1] + lb[reqdim - 1] - 1;
                fctx->reverse = (PG_NARGS() user_fctx = fctx;

                MemoryContextSwitchTo(oldcontext);

        }
        funcctx = SRF_PERCALL_SETUP();

        fctx = funcctx->user_fctx;

        if (fctx->lower upper){
                if (!fctx->reverse)
                        SRF_RETURN_NEXT(funcctx, Int32GetDatum(fctx->lower++));
                else
                        SRF_RETURN_NEXT(funcctx, Int32GetDatum(fctx->upper--));
        }
        else
                /* do when there is no more left */
                SRF_RETURN_DONE(funcctx);
}


