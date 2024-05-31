#include "DFS.h"
#include <algorithm> 

void DFS(int current, int count, int cost, int start, bool* visited, int& min_cost, int N, int** distances) {
    if (count == N && distances[current][start]) {
        min_cost = std::min(min_cost, cost + distances[current][start]);
        return;
    }
    for (int i = 0; i < N; i++) {
        if (!visited[i] && distances[current][i]) {
            visited[i] = true;
            DFS(i, count + 1, cost + distances[current][i], start, visited, min_cost, N, distances);
            visited[i] = false;
        }
    }
}
