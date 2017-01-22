#include <unistd.h>
#include <stdlib.h>
#include "heap.h"
#define CMP(a, b) ((a) >= (b))

static const unsigned int base_size = 8;


void heap_init( heap *restrict h){
	*h = ( heap){
		.size = base_size,
		.count = 0,
		.data = malloc(sizeof(type) * base_size)
	};
	if (!h->data) _exit(1);
}


void heap_push( heap *restrict h, type value){
	unsigned int index, parent;
	if (h->count == h->size){
		h->size <<= 1;
		h->data = realloc(h->data, sizeof(type) * h->size);
		if (!h->data) _exit(1);
	}
	for(index = h->count++; index; index = parent){
		parent = (index - 1) >> 1;
		if CMP(h->data[parent], value) break;
		h->data[index] = h->data[parent];
	}
	h->data[index] = value;
}


void heap_pop( heap *restrict h){
	unsigned int index, swap, other;
	type temp = h->data[--h->count];

	if ((h->count <= (h->size >> 2)) && (h->size > base_size)){
		h->size >>= 1;
		h->data = realloc(h->data, sizeof(type) * h->size);
		if (!h->data) _exit(1); 
	}

	for(index = 0; 1; index = swap){ 
		swap = (index << 1) + 1;
		if (swap >= h->count) break; 
		other = swap + 1;
		if ((other < h->count) && CMP(h->data[other], h->data[swap])) swap = other;
		if CMP(temp, h->data[swap]) break; 

		h->data[index] = h->data[swap];
	}
	h->data[index] = temp;
}


void heapify(type data[restrict], unsigned int count){
	unsigned int item, index, swap, other;
	type temp;
	item = (count >> 1) - 1;
	while (1){
		temp = data[item];
		for(index = item; 1; index = swap){
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
