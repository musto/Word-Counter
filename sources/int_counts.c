#include "int_counts.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct int_counts
{
	int* parray;
	int value;
	int min;
	int max;
};

struct int_counts* int_counts_create(void)
{
	int* array = malloc(sizeof(int)*100);
	struct int_counts* container = malloc(sizeof(struct int_counts));
	container->parray = array;
	container->value = 0;
	return container;
}

void int_counts_add(struct int_counts* container, int key)
{
	container->value++;
	container->parray[key]++;
	if (container->value > container->max)
		container->max = container->value;
	if (container->value < container->min)
		container->min = container->value;
}

int int_counts_get(struct int_counts* container, int key)
{
	return container->parray[key];
}

int int_counts_min(struct int_counts* container)
{
	return container->min;
}

int int_counts_max(struct int_counts* container)
{	
	return container->max;
}

void int_counts_destroy(struct int_counts* container)
{
	free(container->parray);
}
