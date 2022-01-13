# Multicore programming in C examples

Hello World from thread 0! This is a set of examples with code from Tim Mattson @ Intel Corp
to assist learning how to write parallel programs in C

## Hello

This is the simplest parallel program I can think of! Hello World from thread 0!

## Pi Serial

This is a program which computes the value of pi from a Riemann sum using a serial calculation

## Pi Parallel

This is a program which computes the value of  pi from a parallelized Riemann sum using
a parallel block from OpenMP

## Pi Parallel Pad

This is a program which demonstrates how false sharing (cache collisions in parallel codes) leads to slow downs. I determined the cache size of my machine experimentally, so user beware of performance loss/gain.

## Pi Critical

The pi program but rewritten with a critical section to eliminate false sharing

## Pi atomic

The pi program but rewritten with an atomic operation to eliminate false sharing

## Pi loop redux

The pi program with a loop reduction

## Mandel Wrong

A known incorrect parallel code. Can you figure out what's wrong? Hint: Change default(shared) to default(none) and see what the compiler says.

## Mandel Correct

Possible answer key for the mandel wrong challenge problem

## Pi final

The pi program with a loop reduction and the correct memory sharing (private x)


### Matthew Cufari
### Syracuse University Computer Science
### January 2022
### Innovate Orange Technology Team  
