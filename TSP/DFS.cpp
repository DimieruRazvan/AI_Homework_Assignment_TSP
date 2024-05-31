#include "DFS.h"
#include <algorithm>

// Depth First Search algorithm
void DFS(int current, int count, int cost, int start, bool* visited, int& min_cost, int N, int** distances) {
    // Check if we have completed the path
    if (count == N && distances[current][start]) {
        min_cost = std::min(min_cost, cost + distances[current][start]);  // Update minimum cost
        return;
    }

    // Explore neighboring cities
    for (int i = 0; i < N; i++) {
        if (!visited[i] && distances[current][i]) {
            visited[i] = true;  // Mark city as visited
            DFS(i, count + 1, cost + distances[current][i], start, visited, min_cost, N, distances);  // Recursive call
            visited[i] = false;  // Mark city as unvisited for backtracking
        }
    }
}
