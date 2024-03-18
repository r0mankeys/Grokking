#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZEARRAY(array) sizeof(array) / sizeof(array[0])

int linear_search(int *array, size_t size, int value);
int binary_search(int *array, size_t size, int value);

int linear_search(int *array, size_t size, int value)
{
    for (size_t i = 0; i < size; i++)
    {
        if (array[i] == value)
        {
            printf("Found value %d at index %zu\n", value, i);
            return 0;
        } 
    }
    printf("Value %d not found in input array\n", value);
    return -1;
}

int binary_search(int *array, size_t size, int value) 
{
    size_t left = 0;
    size_t right = size;

    while (left <= right) {
        size_t middle = (left + right) / 2;
        if (array[middle] == value) {
            printf("Found value %d at index %zu\n", value, middle);
            return 0;
        } else if (array[middle] < value) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }
    printf("Value %d not found in input array\n", value);
    return -1;
}

int main(int argc, char* argv[])
{ 

    if (argc != 3) {
        printf("Usage: %s <linear|binary> <value>\n", argv[0]);
        return -1;
    }

    int buffer[1000];

    for (size_t i = 0; i < 1000; i++)
    {
        buffer[i] = i;
    }

    size_t size = SIZEARRAY(buffer);

    if (strcmp(argv[1], "linear") == 0 && isdigit(*argv[2])) {
        linear_search(buffer, size, atoi(argv[2]));
    } else if (strcmp(argv[1], "binary") == 0 && isdigit(*argv[2])) {
        binary_search(buffer, size, atoi(argv[2]));
    }
    return 0;
}
