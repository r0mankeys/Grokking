#include <stdio.h>

#define SIZEARRAY(array) sizeof(array) / sizeof(array[0])

void swap(int *a, int *b);
void bubble_sort(int *array, size_t size);
void selection_sort(int *array, size_t size);

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(int *array, size_t size)
{
    for (int i = 0; i < size; ++i){
        for (int j = i + 1; j < size; ++j)
        {
            if (array[i] > array[j])
            swap(&array[i], &array[j]);
        }
    }
}

void selection_sort(int *array, size_t size) 
{
    for (int i = 0; i < size; ++i) 
    {
        int min = i;
        for (int j = i + 1; j < size; ++j)
        {
            if (array[j] < array[min])
            {
                min = j;
            }
        }
        swap(&array[i], &array[min]);
    }
}

int main(int argc, char *argv[])
{
    int unsorted[] = {5, 3, 2, 1, 4, 6, 7, 8, 9, 0, 23, 12, 45, 33, 102, 21, 85};
    size_t size = SIZEARRAY(unsorted);   

    printf("Unsorted array: \n");
    for (size_t i = 0; i < size; i++)
    {
        printf("%d ", unsorted[i]);
    }
    printf("\n");

    selection_sort(unsorted, size);

    printf("Sorted array: \n");
    for (size_t i = 0; i < size; i++)
    {
        printf("%d ", unsorted[i]);
    }
    printf("\n");
    return 0;
}
