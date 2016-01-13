# Homework 1

## Introduction

Given an array of integers, if the array is sorted then searching for an element is trivial.  In fact, one could do in _log(N)_ time, where _N_ is the size of the array.  If the array is not sorted, the process is not as trivial.

Let us assume that you have an array size _N_ filled with random integers from 0 to _z_.  
* Devise a sequential algorithm that will search the array and count up the number of times _k_ appears.  
* Devise a parallel algorithm that will search the array and count up the number of times _k_ appears if you have _M_ threads.

## Deliverable

Combine these two algorithms into a single C program can be executed as followed

```
program <N> <z> <k> <M>
```

The output of your program should be:
```
t(1) = c1
t(2) = c2
t(3) = c3
...
t(M) = cM
total = T
```

Note that `T` is sum of `c1` ... `cM`.  Please use `1024` as the seed to your program's random number generator.

## Grading Rubric

The homework grade will be graded as followed:

* Completion: Everything works 8 pts
* Discussion: I will ask you questions on your assignment 2 pt

