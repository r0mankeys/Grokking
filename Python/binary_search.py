import time

def linearSearch(lst, value):
    for i in range(len(lst)):
        if lst[i] == value:
            return i
    return -1

def binarySearch(lst, value):
    # Set pointers to the beginning and end of the list
    low = 0
    high = len(lst) - 1
    # While the low pointer is not at the end of the list (i.e. the value could still be in the list)
    while low <= high:
        mid = (low + high) // 2
        if lst[mid] == value:
            return mid
        elif lst[mid] < value:
            low = mid + 1
        else:
            high = mid - 1
    return -1

# Test the function
my_list = [1, 3, 5, 7, 9]
print(binarySearch(my_list, 3)) # 1
print(binarySearch(my_list, -1)) # -1  
print(binarySearch(my_list, 9)) # 4

# Test time difference between linear and binary search
length = 1000000
sorted_list = list(range(length))
start = time.time()
linearSearch(sorted_list, length - 1)
print("Linear search time: ", time.time() - start)
start = time.time()
binarySearch(sorted_list, length - 1)
print("Binary search time: ", time.time() - start)
