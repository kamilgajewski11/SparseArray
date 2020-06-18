# SparseArray
A sparse array data structure implementation.

Given an object wchich satisfies following requirerments:
- has default and copy constructor,
- has operators: =, !=, ==, and <<

the program can create a sparse array that stores them.
A sparse array is an array with small amount of objects but they can be very far from each other.
Those on positons that are not initialiazed are assumed to be default (e.g 0 for int).

Implementation uses templates allowing very flexible code. It includes types such as:
-index,
-reference and const reference,
-iterator and const iterator.

