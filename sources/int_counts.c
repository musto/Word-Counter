#include "int_counts.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct int_counts
{
	int* parray;
	int* pvalues;
	int min;
	int max;
};

struct int_counts* int_counts_create(void)
{
	int* array = malloc(sizeof(int)*100);
	int* values = malloc(sizeof(int)*100);
	struct int_counts* container = malloc(sizeof(struct int_counts));
	container->parray = array;
	container->pvalues = values;
	container->min = 1000;
	container->max = -1;
	for (int i = 0; i < 100; i++){
	container->pvalues[i] = 0;
	}
	return container;
/*
 * parrayn alustus uupuu vielä
 */
}

void int_counts_add(struct int_counts* container, int key)
{	
	container->parray[key]++;	
	if (key > container->max)
		container->max = key;
	if (key < container->min)
		container->min = key;

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
	free(container->pvalues);
	free(container->parray);
	free(container);
}
