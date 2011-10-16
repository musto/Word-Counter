#include "test.h"

#include <stdio.h>
#include <stdlib.h>

void assertMyNull(void* pointer, int line, const char* file)
{
	if(pointer)
	{
		printf("Pointer was not null on %s:%d\n", file, line);
		exit(-1);
	}
}

void assertMyIntEquals(int expected, int value, int line, const char* file)
{
	if(expected != value)
	{
		printf("Expected %d, got %d on %s:%d\n", expected, value, file, line);
		exit(-1);
	}
}

