#include <iostream>
#include <cstdlib> // Pentru malloc și free
#include <chrono>  // Pentru măsurarea timpului de execuție
#include "DFS.h"
#include "UCS.h"
#include "AStar.h"

using namespace std;
using namespace std::chrono;

int main() {
    int N;
    cout << "Enter number of cities: ";
    cin >> N;

    // Alocare memorie pentru matricea de distanțe
    int** distances = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; ++i)
        distances[i] = (int*)malloc(N * sizeof(int));

    cout << "Enter distance matrix:" << std::endl;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> distances[i][j];

    int algorithm;
    cout << "Choose algorithm: 1-DFS, 2-UCS, 3-A*: ";
    cin >> algorithm;

    if (algorithm == 1) {
        // Alocare memorie pentru vectorul de vizitare
        bool* visited = (bool*)malloc(N * sizeof(bool));
        for (int i = 0; i < N; ++i)
            visited[i] = false;

        int min_cost = 1000000;
        visited[0] = true;

        auto start_time = high_resolution_clock::now();
        DFS(0, 1, 0, 0, visited, min_cost, N, distances);
        auto end_time = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end_time - start_time).count();

        cout << "Minimum cost (DFS): " << min_cost << std::endl;
        cout << "Execution time (DFS): " << duration << " microseconds" << std::endl;

        // Eliberare memorie pentru vectorul de vizitare
        free(visited);
    }
    else if (algorithm == 2) {
        auto start_time = high_resolution_clock::now();
        int min_cost = uniformCostSearch(0, N, distances);
        auto end_time = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end_time - start_time).count();

        std::cout << "Minimum cost (UCS): " << min_cost << std::endl;
        cout << "Execution time (UCS): " << duration << " microseconds" << std::endl;
    }
    else if (algorithm == 3) {
        auto start_time = high_resolution_clock::now();
        int min_cost = aStarSearch(0, N, distances);
        auto end_time = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end_time - start_time).count();

        cout << "Minimum cost (A*): " << min_cost << std::endl;
        cout << "Execution time (A*): " << duration << " microseconds" << std::endl;
    }
    else {
        cout << "Invalid choice!" << std::endl;
    }

    // Eliberare memorie pentru matricea de distanțe
    for (int i = 0; i < N; ++i)
        free(distances[i]);
    free(distances);

    return 0;
}
