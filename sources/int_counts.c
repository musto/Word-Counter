#include "int_counts.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

struct int_counts
{
	int* pvalues;
	int min;
	int max;
	int total;
};

#define MAX_SIZE 200

struct int_counts* int_counts_create(void)
{
	int* values = malloc(sizeof(int) * MAX_SIZE);
	struct int_counts* container = malloc(sizeof(struct int_counts));
	if(!container) {
		return NULL;
	}
	container->pvalues = values;
	container->min = INT_MAX;
	container->max = -1;
	container->total = 0;
	for(int i = 0; i < MAX_SIZE; ++i) {
		container->pvalues[i] = 0;
	}
	return container;
}

void int_counts_add(struct int_counts* container, int key)
{
	assert(key < MAX_SIZE);

	++container->pvalues[key];
	++container->total;

	if (key > container->max)
		container->max = key;
	if (key < container->min)
		container->min = key;
}

int int_counts_get(struct int_counts* container, int key)
{
	assert(key < MAX_SIZE);

	return container->pvalues[key];
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
	free(container);
}

int int_counts_total(struct int_counts* container)
{
	return container->total;
}

