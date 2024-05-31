#include <iostream>  // input/output operations
#include <cstdlib>   // standard library definitions
#include <chrono>    // time utilities
#include "DFS.h"     // Depth First Search algorithm header
#include "UCS.h"     // Uniform Cost Search algorithm header
#include "AStar.h"   // A* Search algorithm header

using namespace std;
using namespace std::chrono;

int main() {
    int N;
    cout << "Enter number of cities: ";
    cin >> N;

    // Dynamically allocate memory for the distance matrix
    int** distances = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; ++i)
        distances[i] = (int*)malloc(N * sizeof(int));

    // Input the distance matrix
    cout << "Enter distance matrix:" << std::endl;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> distances[i][j];

    int algorithm;
    cout << "Choose algorithm: 1-DFS, 2-UCS, 3-A*: ";
    cin >> algorithm;

    if (algorithm == 1) {  // Depth First Search
        // Dynamically allocate memory for visited array
        bool* visited = (bool*)malloc(N * sizeof(bool));
        for (int i = 0; i < N; ++i)
            visited[i] = false;

        int min_cost = 1000000;  // Initialize minimum cost
        visited[0] = true;       // Mark the starting city as visited

        auto start_time = high_resolution_clock::now();  // Start time
        DFS(0, 1, 0, 0, visited, min_cost, N, distances);  // Execute DFS
        auto end_time = high_resolution_clock::now();    // End time
        auto duration = duration_cast<microseconds>(end_time - start_time).count();  // Calculate duration

        cout << "Minimum cost (DFS): " << min_cost << std::endl;  // Output minimum cost found
        cout << "Execution time (DFS): " << duration << " microseconds" << std::endl;  // Output execution time

        free(visited);  // Free allocated memory
    }
    else if (algorithm == 2) {  // Uniform Cost Search
        auto start_time = high_resolution_clock::now();  // Start time
        int min_cost = uniformCostSearch(0, N, distances);  // Execute UCS
        auto end_time = high_resolution_clock::now();    // End time
        auto duration = duration_cast<microseconds>(end_time - start_time).count();  // Calculate duration

        std::cout << "Minimum cost (UCS): " << min_cost << std::endl;  // Output minimum cost found
        cout << "Execution time (UCS): " << duration << " microseconds" << std::endl;  // Output execution time
    }
    else if (algorithm == 3) {  // A* Search
        auto start_time = high_resolution_clock::now();  // Start time
        int min_cost = aStarSearch(0, N, distances);  // Execute A*
        auto end_time = high_resolution_clock::now();    // End time
        auto duration = duration_cast<microseconds>(end_time - start_time).count();  // Calculate duration

        cout << "Minimum cost (A*): " << min_cost << std::endl;  // Output minimum cost found
        cout << "Execution time (A*): " << duration << " microseconds" << std::endl;  // Output execution time
    }
    else {
        cout << "Invalid choice!" << std::endl;  // Output for invalid algorithm choice
    }

    // Free allocated memory for the distance matrix
    for (int i = 0; i < N; ++i)
        free(distances[i]);
    free(distances);

    return 0;
}
