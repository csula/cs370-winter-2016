# Homework 2

## Introduction

Given a two-dimensional square grid of size `n` x `n`, we define the following properties for our system:
* Each grid point `s(i,j)` can either spin up or spin down (`1` or `0`)
* Each node also has a bias value `z(i,j)`
* The value of the node `h(i,j) = s(i,j) * z(i,j)`

For small grids, it's trivial to calculate global minimum (maximum) of the entire grid space.  However, for larger grids (e.g. `n = 1E10`), this is a daunting task!  As such we rely on parallel programming.

In a real system, there is an additional variable `J(k)` which represents the value of interaction between a node and its neighbors.  Together they encode information we would like to solve.  And in fact, we can generate or tune the desired `h`'s and `J`'s.  **For the purpose of this homework assignment, we will assume that both `s` and `h` are random and that the `J`'s are all `0`.**

## Objective

Write a parallel program (i.e. modify `homework2.c`) to compute the following statistical data on a two-dimensional grid of size `n` x `n`:

* Mean - average of all of the grid points
* Sum - cumulative values of all grid points
* Max/Min - grid with the highest/lowest value
* Std - standard deviation

## Build and run

To compile your homework assignment, you only need to type `make`  this command reads in your `Makefile` and produces an executable `homework2`.  The benefit of using a `Makefile` is that tedious tasks can be automated with a single command.

To run your program run the following command in your `/share` folder:

```
/usr/lib64/mpich/bin/mpirun -n 4 -f hostfile `pwd`/homework2 <n> <z> <seed>
```

Where `n` is `sqrt(N)`, `<z-max>` is the maximum `z` value, and `seed` is random seed to the program.  The output of your program should be as followed:

```
N    = ...
sum  = ...
mean = ...
std  = ...
max  = ...
min  = ...
```

## Deliverable

You will demonstrate a running program with the correct solution to the various seeds that will provided during class.

## Grading Rubric

The homework grade will be graded as followed:

* Completion: Everything works 8 pts
* Discussion: I will ask you questions on your assignment 2 pt

## Bonus

Modify the `Makefile` so that you can call `mpirun` directly.  For example by simply type `make run` your MPI program is executed.
