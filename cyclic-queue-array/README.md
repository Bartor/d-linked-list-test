## Introduction

This is a resizing, cyclic array version of double sided queue. You can push and pop from the head and the tail. Data is stored in an array and wraps around it.

## How does it work?

There are two pointers `head` and `tail` poiting onto particular element of the data array; they are decremented and incremented _real modulo_ the data array size (_real modulo_ means that negative values are mapped to the posivite values, eg. -1 mod 7 = 5). If the number of elements in the array reaches its capacity, the array capacity is doubled and then all the elements are copied into the new array. If the number of elements in the array reaches 1/4 of its capacity, the array capacity is cut down to half and all the elements are copied into the new array.

## Why?

Because:
- it's cache-optimized (the data array is linear)
- it's ammortized O(1) for all the operations
- futhermore, any element can be accessed in real O(1) time, which doesn't work with regular queue

And thos are pretty cool.

## Wait, ammortized O(1)?

That's true, cause it's basically a [dynamic array](https://en.wikipedia.org/wiki/Amortized_analysis#Dynamic_array).