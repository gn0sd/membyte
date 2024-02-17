#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define ERROR_NULL_POINTER -1
#define ERROR_INSUFFICIENT_DEST_SIZE -2
#define ERROR_ZERO_BYTES_COPY -3
#define ERROR_OVERLAPPING_MEMORY -4

int copyNBytes(void* dest, size_t dsize, const void* src, size_t n_bytes) {
    if (dest == NULL || src == NULL) {
        return ERROR_NULL_POINTER;
    }

    if (dsize < n_bytes) {
        return ERROR_INSUFFICIENT_DEST_SIZE;
    }

    if (n_bytes == 0) {
        return ERROR_ZERO_BYTES_COPY;
    }

    if (src >= dest && src < (char*)dest + n_bytes) {
        return ERROR_OVERLAPPING_MEMORY;
    }

    if ((char*)dest >= (char*)src && (char*)dest < (char*)src + n_bytes) {
        return ERROR_OVERLAPPING_MEMORY;
    }

    char* cdest = (char*)dest;
    const char* csrc = (const char*)src;

    for (size_t i = 0; i < n_bytes; i++) {
        cdest[i] = csrc[i];
    }

    return SUCCESS;
}

void testSrcNull() {
    char dest[10] = "Hello";
    int result = copyNBytes(dest, sizeof(dest), NULL, 5);
    printf("Test: testSrcNull - Result: %d\n", result);
}

void testDestNull() {
    const char src[10] = "Hello";
    int result = copyNBytes(NULL, 10, src, sizeof(src));
    printf("Test: testDestNull - Result: %d\n", result);
}

void testNBytesCopy1() {
    char dest[10] = "Hello";
    const char src[10] = "World";
    int result = copyNBytes(dest, sizeof(dest), src, 5);
    printf("Test: testNBytesCopy1 - Result: %d\n", result);
    printf("Destination: %s\n", dest);
}

void testNBytesCopy2() {
    char dest[10] = "Hello";
    const char src[10] = "World";
    int result = copyNBytes(dest, sizeof(dest), src, sizeof(src));
    printf("Test: testNBytesCopy2 - Result: %d\n", result);
    printf("Destination: %s\n", dest);
}

void testOverlapData() {
    char dest[10] = "Hello";
    const char src[10] = "World";
    int result = copyNBytes(dest, sizeof(dest), src + 1, sizeof(src) - 1);
    printf("Test: testOverlapData - Result: %d\n", result);
    printf("Destination: %s\n", dest);
}

void testZerosBytesCopy() {
    char dest[10] = "Hello";
    const char src[10] = "World";
    int result = copyNBytes(dest, sizeof(dest), src, 0);
    printf("Test: testZerosBytesCopy - Result: %d\n", result);
    printf("Destination: %s\n", dest);
}

void testSmallerDestSize() {
    char dest[5] = "Hello";
    const char src[10] = "World";
    int result = copyNBytes(dest, sizeof(dest), src, sizeof(src));
    printf("Test: testSmallerDestSize - Result: %d\n", result);
    printf("Destination: %s\n", dest);
}

int main() {
    testSrcNull();
    testDestNull();
    testNBytesCopy1();
    testNBytesCopy2();
    testOverlapData();
    testZerosBytesCopy();
    testSmallerDestSize();

    return 0;
}
