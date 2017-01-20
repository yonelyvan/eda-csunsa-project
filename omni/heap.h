typedef int type;

typedef struct _heap heap;
struct _heap{
	unsigned int size; 	// tamaño de la memoria asignada
	unsigned int count; // contador de elementos del heap
	type *data; 		// array con los elementos
};

void heap_init( heap *restrict h);
void heap_push( heap *restrict h, type value);
void heap_pop( heap *restrict h);

/*retorna al objeto q esta en top*/
#define heap_front(h) (*(h)->data)

/*libera la memoria asignada*/
#define heap_term(h) (free((h)->data))

void heapify(type data[restrict], unsigned int count);