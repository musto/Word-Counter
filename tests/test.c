#include "test.h"

#include <stdio.h>
#include <stdlib.h>

void assertMyNull(void* pointer, int line)
{
	if(pointer)
	{
		printf("Pointer was not null on line %d\n", line);
		exit(-1);
	}
}

void assertMyIntEquals(int expected, int value, int line)
{
	printf("Expected %d, got %d on line %d\n", expected, value, line);
	exit(-1);
}

