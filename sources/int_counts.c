#include "int_counts.h"

#include <stddef.h>

struct int_counts
{
int* parray;
int key;
int value;
};

struct int_counts* int_counts_create(void)
{
int* array = malloc(sizeof(int)*100);
struct int_counts* container = malloc(sizeof(struct int_counts));
container->key = 0;
container->parray = array;
container->value = 0;
return container;
}

void int_counts_add(struct int_counts* container, int key)
{
container->parray[key]++;
}

int int_counts_get(struct int_counts* container, int key)
{
return container->parray[key];
}

int int_counts_min(struct int_counts* container)
{
	return -1;
}

int int_counts_max(struct int_counts* container)
{	
	return -1;
}

void int_counts_destroy(struct int_counts* container)
{
free(container->parray);
}
