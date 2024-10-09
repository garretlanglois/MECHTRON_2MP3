#this is the testing code for timing our functions
#the code below is adapted from Pedram's code included in the assignment file 

import time
import ctypes
import numpy as np
from numpy.ctypeslib import ndpointer

lib_path = 'libmysort.so'

# Load the shared library
mySortLib = ctypes.CDLL(lib_path)

# Define input argument types without conversion using ndpointer
mySortLib.bubbleSort.argtypes = [ndpointer(ctypes.c_int, flags="C_CONTIGUOUS"), ctypes.c_int]
mySortLib.bubbleSort.restype = None

# Running a simple test with Bubble Sort
arr0 = np.array([64, -134, -5, 0, 25, 12, 22, 11, 90], dtype=np.int32)
n = len(arr0)
print("Original array:", arr0)

# Call Bubble Sort
mySortLib.bubbleSort(arr0, n)
print("Sorted array using Bubble Sort:", arr0)

# Creating a large test case
arr = np.random.choice(np.arange(-1000000, 1000000, dtype=np.int32), size=500000, replace=False)
n = len(arr)
print("Original array:", arr)

# Sorting with Bubble Sort
arr_copy = np.copy(arr)
start = time.time()
mySortLib.bubbleSort(arr_copy, n)
end = time.time()
print("Sorted array using Bubble Sort:", arr_copy)
print(f"Time to sort using Bubble Sort: {end - start} seconds")

# Compare with built-in Python sort 
arr_copy = np.copy(arr)
start = time.time()
sorted_arr = sorted(arr_copy)  # Python's built-in sort
end = time.time()
print("Time taken by built-in sort:", end - start, "seconds")


#Note this runs out of memory on my macbook...