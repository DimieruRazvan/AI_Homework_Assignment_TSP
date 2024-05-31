#ifndef ASTAR_H
#define ASTAR_H

int heuristic(const int* path, int path_size, int N, int** distances);
int aStarSearch(int start, int N, int** distances);

#endif 
