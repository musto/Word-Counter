#ifndef TEST_H
#define TEST_H

void assertMyNull(void* pointer, int line, const char* file);
void assertMyNotNull(void* pointer, int line, const char* file);
void assertMyIntEquals(int expected, int value, int line, const char* file);
void assertMyStringEquals(const char* expected, const char* value, int line, const char* file);

#define assertNull(pointer) assertMyNull(pointer, __LINE__, __FILE__)
#define assertNotNull(pointer) assertMyNotNull(pointer, __LINE__, __FILE__)
#define assertIntEquals(expected, value) assertMyIntEquals(expected, value, __LINE__, __FILE__)
#define assertStringEquals(expected, value) assertMyStringEquals(expected, value, __LINE__, __FILE__)

#endif

