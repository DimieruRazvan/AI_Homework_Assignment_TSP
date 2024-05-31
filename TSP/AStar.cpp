#include "AStar.h"
#include <algorithm>
#include <cstdlib>
#include <climits>
#include <cstring>

// Function to calculate the heuristic value for A* search
int heuristic(const int* path, int path_size, int N, int** distances) {
    int h = 0;  // Initialize heuristic value
    bool* in_path = (bool*)malloc(N * sizeof(bool));  // Allocate memory for array to track visited cities
    std::fill(in_path, in_path + N, false);  // Initialize all cities as not visited

    // Mark cities in the current path as visited
    for (int i = 0; i < path_size; ++i) {
        in_path[path[i]] = true;
    }

    // Calculate heuristic value based on the closest unvisited city for each city not in the current path
    for (int i = 0; i < N; ++i) {
        if (!in_path[i]) {
            int min_cost = INT_MAX;  // Initialize minimum cost to a very large value
            // Find the closest unvisited city to city i
            for (int j = 0; j < N; ++j) {
                if (i != j && distances[i][j] < min_cost) {
                    min_cost = distances[i][j];
                }
            }
            h += min_cost;  // Add the minimum cost to the heuristic value
        }
    }

    free(in_path);  // Free memory for the array tracking visited cities
    return h;  // Return the heuristic value
}

// A* search algorithm
int aStarSearch(int start, int N, int** distances) {
    int min_cost = INT_MAX;  // Initialize minimum cost to a very large value

    // Structure to represent a node in the search tree
    struct Node {
        int city;              // Current city
        int cost;              // Total cost so far
        int heuristic;         // Heuristic value
        int path[20];          // Path taken so far
        int path_size;         // Size of the path

        // Constructors to initialize a node
        Node() : city(0), cost(0), heuristic(0), path_size(0) {
            std::fill(path, path + 20, 0);  // Initialize path array
        }

        Node(int c, int cst, int h, const int* p, int p_size) : city(c), cost(cst), heuristic(h), path_size(p_size) {
            std::copy(p, p + p_size, path);  // Copy path array
        }
    };

    Node* stack = (Node*)malloc(N * N * sizeof(Node));  // Allocate memory for the stack
    int stack_top = 0;  // Initialize stack top

    Node initial;  // Create initial node
    initial.city = start;  // Set initial city
    initial.heuristic = heuristic(initial.path, initial.path_size, N, distances);  // Calculate heuristic value
    initial.path[0] = start;  // Set initial path with starting city
    initial.path_size = 1;  // Set initial path size
    stack[stack_top++] = initial;  // Push initial node to stack

    // Explore nodes in the stack
    while (stack_top > 0) {
        Node node = stack[--stack_top];  // Pop node from stack

        // Check if we have completed the path
        if (node.path_size == N && distances[node.city][start]) {
            min_cost = std::min(min_cost, node.cost + distances[node.city][start]);  // Update minimum cost
            continue;
        }

        // Explore neighboring cities
        for (int i = 0; i < N; ++i) {
            bool in_path = false;
            for (int j = 0; j < node.path_size; ++j) {
                if (node.path[j] == i) {
                    in_path = true;
                    break;
                }
            }

            if (!in_path && distances[node.city][i]) {
                Node new_node;  // Create new node
                new_node.city = i;  // Set city
                new_node.cost = node.cost + distances[node.city][i];  // Calculate cost
                new_node.path_size = node.path_size + 1;  // Update path size
                std::copy(node.path, node.path + node.path_size, new_node.path);  // Copy path
                new_node.path[node.path_size] = i;  // Add new city to path
                new_node.heuristic = heuristic(new_node.path, new_node.path_size, N, distances);  // Calculate heuristic value
                stack[stack_top++] = new_node;  // Push new node to stack
            }
        }
    }

    free(stack);  // Free memory for the stack
    return min_cost;  // Return minimum cost
}
