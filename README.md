# Sorting Algorithm Optimization using **OpenMP** and **MPI**

This project aims to optimize classical sorting algorithms using OpenMP and MPI. The project contains two folders, one for OpenMP and the other for MPI.

## OpenMP

The OpenMP folder contains serial and parallel solutions for three sorting algorithms: **quick sort**, **enumeration sort**, and **merge sort** using OpenMP.

### Quick Sort

The quick sort algorithm is a divide-and-conquer algorithm that partitions the array around a pivot element and recursively sorts the left and right subarrays. The OpenMP implementation parallelizes the partition and sort operations to improve performance.

### Enumeration Sort

The enumeration sort algorithm is a simple sorting algorithm that counts the number of elements less than each element and uses these counts to place each element in the correct position. The OpenMP implementation parallelizes the counting operation to improve performance.

### Merge Sort

The merge sort algorithm is a divide-and-conquer algorithm that recursively divides the array into smaller subarrays and then merges them in sorted order. The OpenMP implementation parallelizes the merge operation to improve performance.

## MPI

The MPI folder contains serial and parallel solutions for the same three sorting algorithms: **quick sort**, **enumeration sort**, and **merge sort** using MPI.

### Quick Sort

The MPI implementation of the quick sort algorithm distributes the data among multiple processors and parallelizes the partition and sort operations to improve performance.

### Enumeration Sort

The MPI implementation of the enumeration sort algorithm distributes the data among multiple processors and parallelizes the counting operation to improve performance.

### Merge Sort

The MPI implementation of the merge sort algorithm distributes the data among multiple processors and parallelizes the merge operation to improve performance.

## Experimental Data

Each folder contains specific files that include detailed requirements and experimental data for each sorting algorithm.

## Report

The `Report.md` file in each folder contains the details of all projects, including a description of the algorithms, the implementation details, and the experimental results.
