#include <stdio.h>

#define SIZEARRAY(array) sizeof(array) / sizeof(array[0])

void swap(int *a, int *b);
void quick_sort(int *array, size_t size);

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;  
}

void quick_sort(int *array, size_t size) 
{
    if (size < 2)
    {
        return;
    } else if (size == 2) {
        if (array[0] > array[1])
        {
            swap(&array[0], &array[1]);
        }
        return;
    }

    int pivot = array[0];
    int i = 1;
    int j = size - 1;

    while (i <= j) {
        if (array[i] < pivot) {
            i++;
        } else if (array[j] > pivot) {
            j--;
        } else {
            swap(&array[i], &array[j]);
            i++;
            j--;
        }
    }

    swap(&array[0], &array[j]);

    quick_sort(array, j);
    quick_sort(array + i, size - i);
}

int main(int argc, char *argv[])
{
    int unsorted[] = {5, 3, 2, 1, 0, 23, 12, 107, 21, 9};

    quick_sort(unsorted, SIZEARRAY(unsorted));

    printf("Sorted array: \n");
    for (size_t i = 0; i < SIZEARRAY(unsorted); i++)
    {
        printf("%d ", unsorted[i]);
    }

    printf("\n");

    return 0;
}
