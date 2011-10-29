#ifndef INT_COUNTS_H
#define INT_COUNTS_H

struct int_counts;

struct int_counts* int_counts_create(void);
void int_counts_add(struct int_counts* container, int key);
int int_counts_get(struct int_counts* container, int key);
int int_counts_min(struct int_counts* container);
int int_counts_max(struct int_counts* container);
void int_counts_destroy(struct int_counts* container);

#endif

