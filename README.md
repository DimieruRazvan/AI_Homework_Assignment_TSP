# TSP Solver

## Table of Contents
1. [Introduction](#introduction)
2. [Problem Statement](#problem-statement)
3. [Algorithms Implemented](#algorithms-implemented)
4. [Application Overview](#application-overview)
5. [Compiling the Code](#compiling-the-code)
6. [Running the Application](#running-the-application)
7. [File Structure](#file-structure)
8. [Conclusions](#conclusions)

## Introduction
This application is a solver for the Traveling Salesman Problem (TSP) using three algorithms: Depth-First Search (DFS), Uniform Cost Search (UCS), and A* Search (A*). The goal is to find the minimum cost path that visits each city exactly once and returns to the starting city.

## Problem Statement
The task is to implement and compare three different algorithms (DFS, UCS, A*) for solving the TSP. Each algorithm should be implemented in C++ and should read an adjacency matrix representing the distances between cities.

## Algorithms Implemented
1. **Depth-First Search (DFS)**: Explores all possible paths from the start city to every other city and back.
2. **Uniform Cost Search (UCS)**: Explores paths in order of their cumulative cost.
3. **A* Search (A*)**: Uses a heuristic to guide the search for the minimum cost path.

## Application Overview
### High-level Architectural Overview
The application is divided into multiple modules, each responsible for a different aspect of the TSP solving process. The main module handles input/output and orchestrates the use of different algorithms.

### Input Data Format
The input is an adjacency matrix representing the distances between cities. The matrix is read from standard input.

### Output Data Format
The output is the minimum cost of a TSP tour found by the selected algorithm.

### Modules and Functions
1. **Main Module (`main.cpp`)**
    - Handles user input and output
    - Invokes the selected algorithm

2. **DFS Module (`DFS.h` / `DFS.cpp`)**
    - Implements the Depth-First Search algorithm
    - `DFS(int start, int N, int** distances)`: Solves the TSP using DFS

3. **UCS Module (`UCS.h` / `UCS.cpp`)**
    - Implements the Uniform Cost Search algorithm
    - `uniformCostSearch(int start, int N, int** distances)`: Solves the TSP using UCS

4. **A* Module (`AStar.h` / `AStar.cpp`)**
    - Implements the A* Search algorithm
    - `aStarSearch(int start, int N, int** distances)`: Solves the TSP using A*

## Compiling the Code
To compile the code, use the provided Makefile. Open a terminal in the root directory of the project and run:
```sh
make
```
This will compile all the source files and generate an executable named `tsp_solver`.

## Running the Application
To run the application, use the following command:
```sh
./tsp_solver
```
You will be prompted to enter the number of cities and the distance matrix, followed by the choice of algorithm:
1. DFS
2. UCS
3. A*

## File Structure
```
TSP_Solver/
├── src/
│   ├── main.cpp
│   ├── DFS.cpp
│   ├── UCS.cpp
│   ├── AStar.cpp
│   └── Makefile
├── include/
│   ├── DFS.h
│   ├── UCS.h
│   └── AStar.h
└── README.md
```

## Conclusions
After completing this homework, we have successfully implemented three different algorithms for solving the TSP and compared their performances. The most challenging part was ensuring the correctness of the heuristic in the A* algorithm. Future work could include optimizing these algorithms further and exploring other heuristic methods for A*.

## References
- Russell, S., & Norvig, P. (2009). Artificial Intelligence: A Modern Approach (3rd ed.). Pearson.
- Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2009). Introduction to Algorithms (3rd ed.). MIT Press.
