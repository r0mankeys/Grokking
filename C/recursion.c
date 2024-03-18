#include <stdio.h>

#define SIZEARRAY(array) sizeof(array) / sizeof(array[0])

int recursive_sum_array(int *array, size_t size);
int recursive_find_max(int *array, size_t size, int max);
int recursive_binary_search(int *array, size_t left, size_t right, int value);

int recursive_sum_array(int *array, size_t size)
{
    if (size == 0)
    {
        return 0;
    }
    return array[size - 1] + recursive_sum_array(array, size - 1);
}

int recursive_find_max(int *array, size_t size, int max)
{
    if (size == 0) 
    {
        return max;
    }

    return array[size - 1] > max ? recursive_find_max(array, size - 1, array[size - 1]) : recursive_find_max(array, size - 1, max);
}

int recursive_binary_search(int *array, size_t left, size_t right, int value)
{
    if (left >= right)
    {
        printf("Value %d not found in input array\n", value);
        return -1;
    }

    int middle = (left + right) / 2;

    if (array[middle] == value) {
        printf("Found value %d at index %d\n", value, middle);
        return middle;
    }

    return array[middle] < value ? recursive_binary_search(array, middle + 1, right, value) : recursive_binary_search(array, left, middle - 1, value);
}

int main(int argc, char *argv[])
{
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t size = SIZEARRAY(array);

    printf("Array: \n");

    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }

    printf("\n");

    printf("Sum of array: %d\n", recursive_sum_array(array, size)); // 45


    int max[] = {1, 2, 3, 4, 21, 6, 7, 8, 9};

    for (int i = 0; i < SIZEARRAY(max); i++)
    {
        printf("%d ", max[i]);
    }

    printf("\n");

    printf("Max of array: %d\n", recursive_find_max(max, SIZEARRAY(max), max[0])); // 21

    int binary[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    printf("Binary search: \n");

    for (int i = 0; i < SIZEARRAY(binary); i++)
    {
        printf("%d ", binary[i]);
    }

    printf("\n");

    recursive_binary_search(binary, 0, SIZEARRAY(binary), 5); // Found value 5 at index 4
}
