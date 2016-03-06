# Homework 3

## Introduction

Hadoop is a software system that greatly reduces the complicate process of doing large-scale MapReduce (MR) programming.  

For this homework assignment, we will explore the process of setting up a simple cluster for doing Hadoop.  Students should note that the cluster building exercise is not intended to demonstrate performance.

## Objective

The purpose of this homework assignment is to introduce students to the Hadoop architecture with a hands-on exercise.

## Task

The `cs-tools` example includes a few configuration files that can be found in `cs-tools/vagrant/hadoop/cluster`:

* `core-site.xml`
* `hdfs-site.xml`
* `mapred-site.xml`

These files are copied to the hadoop installed directory:

```
cp /vagrant/${MODE}/* /opt/${HADOOP}/conf/
```

Where `${MODE}` is defined to be `cluster` when you start `node1`, `node2`, `node3` and `node4`.  Note that when you boot up `node0`, `${MODE}` defaults to `one-node`.

## Deliverable

Students will demonstrate a cluster running Hadoop and `wordcount` with a text document to be provided:

* Run build-in java `wordcount` example
* Run the provided c++ `wordcount` example

## Grading Rubric

The homework grade will be graded as followed:

* Completion: Everything works 8 pts
* Discussion: I will ask you questions on your assignment 2 pt
