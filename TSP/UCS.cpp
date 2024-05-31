#include "UCS.h"
#include <algorithm>
#include <cstdlib> // Pentru malloc și free
#include <cstring> 
using namespace std;

struct Node {
    int city;
    int cost;
    int* path;
    int path_size;

    Node(int c, int cst, int* p, int size) : city(c), cost(cst), path_size(size) {
        path = (int*)malloc(size * sizeof(int));
        copy(p, p + size, path);
    }

  
};

int uniformCostSearch(int start, int N, int** distances) {
    int min_cost = 1000000;
    Node** stack = (Node**)malloc(N * N * sizeof(Node*));
    int stack_top = 0;

    int* initial_path = (int*)malloc(sizeof(int));
    initial_path[0] = start;

    for (int i = 0; i < N; ++i) {
        if (i != start && distances[start][i] > 0) {
            int* new_path = (int*)malloc(2 * sizeof(int));
            new_path[0] = start;
            new_path[1] = i;
            stack[stack_top++] = new Node(i, distances[start][i], new_path, 2);
            free(new_path);
        }
    }

    while (stack_top > 0) {
        Node* current_node = stack[--stack_top];

        if (current_node->path_size == N && distances[current_node->city][start] > 0) {
            min_cost = min(min_cost, current_node->cost + distances[current_node->city][start]);
            free(current_node);
            continue;
        }

        for (int i = 0; i < N; ++i) {
            bool in_path = false;
            for (int j = 0; j < current_node->path_size; ++j) {
                if (current_node->path[j] == i) {
                    in_path = true;
                    break;
                }
            }

            if (!in_path && distances[current_node->city][i] > 0) {
                int* new_path = (int*)malloc((current_node->path_size + 1) * sizeof(int));
                copy(current_node->path, current_node->path + current_node->path_size, new_path);
                new_path[current_node->path_size] = i;
                stack[stack_top++] = new Node(i, current_node->cost + distances[current_node->city][i], new_path, current_node->path_size + 1);
                free(new_path);
            }
        }

        free(current_node);
    }

    free(stack);
    free(initial_path);
    return min_cost == 1000000 ? -1 : min_cost;
}
