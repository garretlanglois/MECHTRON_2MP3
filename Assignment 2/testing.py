import time
import ctypes
import numpy as np
from numpy.ctypeslib import ndpointer
import platform

# Path to the shared library
if platform.system() == 'Windows':
    lib_path = './libmysort.dll'
else:
    lib_path = './libmysort.so'

# Load the shared library
mySortLib = ctypes.CDLL(lib_path)

# input argument types and return types for each sorting function
mySortLib.bubbleSort.argtypes = [ndpointer(ctypes.c_int, flags="C_CONTIGUOUS"), ctypes.c_int]
mySortLib.bubbleSort.restype = None

mySortLib.insertionSort.argtypes = [ndpointer(ctypes.c_int, flags="C_CONTIGUOUS"), ctypes.c_int]
mySortLib.insertionSort.restype = None

mySortLib.mergeSort.argtypes = [ndpointer(ctypes.c_int, flags="C_CONTIGUOUS"), ctypes.c_int, ctypes.c_int]
mySortLib.mergeSort.restype = None

mySortLib.heapSort.argtypes = [ndpointer(ctypes.c_int, flags="C_CONTIGUOUS"), ctypes.c_int]
mySortLib.heapSort.restype = None

mySortLib.countingSort.argtypes = [ndpointer(ctypes.c_int, flags="C_CONTIGUOUS"), ctypes.c_int]
mySortLib.countingSort.restype = None

# small array test
arr0 = np.array([64, -134, -5, 0, 25, 12, 22, 11, 90], dtype=np.int32)
n = len(arr0)

print("Original array:", arr0)

# Test Bubble Sort
arr_copy = np.copy(arr0)
mySortLib.bubbleSort(arr_copy, n)
print("Sorted array using Bubble Sort:", arr_copy)

# Test Insertion Sort
arr_copy = np.copy(arr0)
mySortLib.insertionSort(arr_copy, n)
print("Sorted array using Insertion Sort:", arr_copy)

# Test Merge Sort (passing 0 as the start index and n-1 as the end index)
arr_copy = np.copy(arr0)
mySortLib.mergeSort(arr_copy, 0, n-1)
print("Sorted array using Merge Sort:", arr_copy)

# Test Heap Sort
arr_copy = np.copy(arr0)
mySortLib.heapSort(arr_copy, n)
print("Sorted array using Heap Sort:", arr_copy)

# Test Counting Sort
arr_copy = np.copy(arr0)
mySortLib.countingSort(arr_copy, n)
print("Sorted array using Counting Sort:", arr_copy)

# Creating a large test case
arr = np.random.choice(np.arange(-1000000, 1000000, dtype=np.int32), size=500000, replace=False)
n = len(arr)
print("Original array for large test (first 10 elements):", arr[:10], "...")

# Function to time and print sorting results
def time_sorting(sort_func, name, arr, n, *extra_args):
    arr_copy = np.copy(arr)
    start = time.time()
    
    # Need to pass extra arguments for merge sort
    if extra_args:
        sort_func(arr_copy, *extra_args) 
    else:
        sort_func(arr_copy, n) 
        
    end = time.time()
    print(f"Time to sort using {name}: {end - start} seconds")
    print(f"First 10 elements of the sorted array using {name}: {arr_copy[:10]}")  # Print first 10 elements

# Timing all the algorithms with the large array
time_sorting(mySortLib.bubbleSort, "Bubble Sort", arr, n)
time_sorting(mySortLib.insertionSort, "Insertion Sort", arr, n)
time_sorting(mySortLib.mergeSort, "Merge Sort", arr, n, 0, n-1)  # Passing start and end indices for merge sort
time_sorting(mySortLib.heapSort, "Heap Sort", arr, n)
time_sorting(mySortLib.countingSort, "Counting Sort", arr, n)

# Compare with python's sorting algorithm
arr_copy = np.copy(arr)
start = time.time()
sorted_arr = sorted(arr_copy)
end = time.time()
print("Time taken by Python's built-in sort:", end - start, "seconds")

# Compare with numpys sorting algorithm
arr_copy = np.copy(arr)
start = time.time()
np_sorted_arr = np.sort(arr_copy)
end = time.time()
print("Time taken by NumPy's sort:", end - start, "seconds")
