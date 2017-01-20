#include <unistd.h>
#include <stdlib.h>
#include "heap.h"
#define CMP(a, b) ((a) <= (b))/*se define maxheap(>=) o minheap(<=)*/

static const unsigned int base_size = 8;





/*	funciones 	*/

// inisializar heap para su uso (constructor)
void heap_init( heap *restrict h){
	*h = ( heap){
		.size = base_size,
		.count = 0,
		.data = malloc(sizeof(type) * base_size)
	};
	if (!h->data) _exit(1); //error si la asignacion de memoria falla
}


void heap_push( heap *restrict h, type value){
	unsigned int index, parent;
	// Resize
	if (h->count == h->size){
		h->size <<= 1;
		h->data = realloc(h->data, sizeof(type) * h->size);
		if (!h->data) _exit(1); //error si la asignacion de memoria falla
	}
	//encontrar donde colocar el elemento y ponerlo
	for(index = h->count++; index; index = parent){
		parent = (index - 1) >> 1;
		if CMP(h->data[parent], value) break;
		h->data[index] = h->data[parent];
	}
	h->data[index] = value;
}

/* Removes the biggest element from the heap */
void heap_pop( heap *restrict h){
	unsigned int index, swap, other;
	type temp = h->data[--h->count];// eliminar elemento q esta en top

	// cambiar el tamaño del heap si esta consumiendo demasiada memoria
	if ((h->count <= (h->size >> 2)) && (h->size > base_size)){
		h->size >>= 1;
		h->data = realloc(h->data, sizeof(type) * h->size);
		if (!h->data) _exit(1); 
	}

	// reordenar elementos
	for(index = 0; 1; index = swap){
		// Encuentra al hijo para intercambiar 
		swap = (index << 1) + 1;
		if (swap >= h->count) break; //Si no hay hijos, el heap se reordena
		other = swap + 1;
		if ((other < h->count) && CMP(h->data[other], h->data[swap])) swap = other;
		if CMP(temp, h->data[swap]) break; //si el hijo mayor es menor o igual que su padre, el heap se reordena

		h->data[index] = h->data[swap];
	}
	h->data[index] = temp;
}


void heapify(type data[restrict], unsigned int count){
	unsigned int item, index, swap, other;
	type temp;
	// Muever cada elemento no-hoja a la posición correcta en su subarbol
	item = (count >> 1) - 1;
	while (1){
		// Encontrar la posición del elemento actual en su subárbol
		temp = data[item];
		for(index = item; 1; index = swap){
			// encontrar al hijo para intercambiar
			swap = (index << 1) + 1;
			if (swap >= count) break; 
			other = swap + 1;
			if ((other < count) && CMP(data[other], data[swap])) swap = other;
			if CMP(temp, data[swap]) break; 

			data[index] = data[swap];
		}
		if (index != item) data[index] = temp;

		if (!item) return;
		--item;
	}
}