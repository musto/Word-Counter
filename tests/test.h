#ifndef TEST_H
#define TEST_H

void assertMyNull(void* pointer, int line);
void assertMyIntEquals(int expected, int value, int line);

#define assertNull(pointer) assertMyNull(pointer, __LINE__)
#define assertIntEquals(expected, value) assertMyIntEquals(expected, value, __LINE__)

#endif

