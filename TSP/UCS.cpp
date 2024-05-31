#include "UCS.h"
#include <algorithm>
#include <cstdlib>
#include <cstring>  // for memcpy
using namespace std;

// Structure to represent a node in the search tree
struct Node {
    int city;        // Current city
    int cost;        // Total cost so far
    int* path;       // Path taken so far
    int path_size;   // Size of the path

    // Constructor to initialize a node
    Node(int c, int cst, int* p, int size) : city(c), cost(cst), path_size(size) {
        path = (int*)malloc(size * sizeof(int));  // Allocate memory for the path
        copy(p, p + size, path);  // Copy the path array
    }
};

// Function to perform Uniform Cost Search
int uniformCostSearch(int start, int N, int** distances) {
    int min_cost = 1000000;  // Initialize minimum cost
    Node** stack = (Node**)malloc(N * N * sizeof(Node*));  // Allocate memory for the stack
    int stack_top = 0;  // Initialize stack top

    int* initial_path = (int*)malloc(sizeof(int));  // Allocate memory for initial path
    initial_path[0] = start;  // Set initial path with starting city

    // Add neighboring cities of the starting city to the stack
    for (int i = 0; i < N; ++i) {
        if (i != start && distances[start][i] > 0) {
            int* new_path = (int*)malloc(2 * sizeof(int));  // Allocate memory for the new path
            new_path[0] = start;
            new_path[1] = i;
            stack[stack_top++] = new Node(i, distances[start][i], new_path, 2);  // Push new node to stack
            free(new_path);  // Free memory for the new path
        }
    }

    // Explore nodes in the stack
    while (stack_top > 0) {
        Node* current_node = stack[--stack_top];  // Pop node from stack

        // Check if we have completed the path
        if (current_node->path_size == N && distances[current_node->city][start] > 0) {
            min_cost = min(min_cost, current_node->cost + distances[current_node->city][start]);  // Update minimum cost
            free(current_node);  // Free memory for the current node
            continue;
        }

        // Explore neighboring cities
        for (int i = 0; i < N; ++i) {
            bool in_path = false;
            for (int j = 0; j < current_node->path_size; ++j) {
                if (current_node->path[j] == i) {
                    in_path = true;
                    break;
                }
            }

            if (!in_path && distances[current_node->city][i] > 0) {
                int* new_path = (int*)malloc((current_node->path_size + 1) * sizeof(int));  // Allocate memory for the new path
                copy(current_node->path, current_node->path + current_node->path_size, new_path);  // Copy current path to new path
                new_path[current_node->path_size] = i;  // Add new city to new path
                stack[stack_top++] = new Node(i, current_node->cost + distances[current_node->city][i], new_path, current_node->path_size + 1);  // Push new node to stack
                free(new_path);  // Free memory for the new path
            }
        }

        free(current_node);  // Free memory for the current node
    }

    free(stack);  // Free memory for the stack
    free(initial_path);  // Free memory for the initial path
    return min_cost == 1000000 ? -1 : min_cost;  // Return minimum cost
}
