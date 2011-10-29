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

void assertMyNotNull(void* pointer, int line, const char* file)
{
	if(!pointer)
	{
		printf("Pointer was null on %s:%d\n", file, line);
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

void assertMyStringEquals(const char* expected, const char* value, int line, const char* file)
{
	if(strcmp(expected, value) != 0)
	{
		printf("Expected \"%s\", got \"%s\" on %s:%d\n", expected, value, file, line);
		exit(-1);
	}
}

void assertMyHigher(int first, int second, int line, const char* file)
{
	if(second >= first)
	{
		printf("Min was less than max %s:%d\n", file, line);
		exit(-1);
	}
}

