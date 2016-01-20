# Homework 1

## Introduction

Given an array of integers, if the array is sorted then searching for an element is trivial.  In fact, one could do in _log(N)_ time, where _N_ is the size of the array.  If the array is not sorted, the process is not as trivial.

Let us assume that you have an array size _N_ filled with random integers from 0 to _z_.  
* Devise a sequential algorithm that will search the array and count up the number of times _k_ appears.  
* Devise a parallel algorithm that will search the array and count up the number of times _k_ appears if you have _M_ threads.

## Example code

### To compile

```
gcc -o program program.c 
```

To run on unix:

```
./program 1000 100 25 5
```

## Deliverable

The example programs are provided to get you started.  You should combine all three programs: `dynamic-array.c` `program.c` and `thread-demo.c` into a single program `homework1.c` that is to be executed as followed:

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

## Hints and Tips

1. Start with a simple C program that can generate `N` random integers from 0 to `z`

2. Modify the C program so that it searches the array sequentially and count the number of times the integer `k` appears

3. Modify the C program so that you can partition the array into `M` partitions

4. Figure out which thread is responsible for which partition, e.g. thread id, start, and end index (you can do this without coding)

5. Write threaded routine to perform step 2 (from above)

