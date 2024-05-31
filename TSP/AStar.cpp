#include "AStar.h"
#include <algorithm> 
#include <cstdlib>
#include <climits>
#include <cstring>

int heuristic(const int* path, int path_size, int N, int** distances) {
    int h = 0;
    bool* in_path = (bool*)malloc(N * sizeof(bool));
    std::fill(in_path, in_path + N, false);

    for (int i = 0; i < path_size; ++i) {
        in_path[path[i]] = true;
    }

    for (int i = 0; i < N; ++i) {
        if (!in_path[i]) {
            int min_cost = INT_MAX;
            for (int j = 0; j < N; ++j) {
                if (i != j && distances[i][j] < min_cost) {
                    min_cost = distances[i][j];
                }
            }
            h += min_cost;
        }
    }

    free(in_path);
    return h;
}

int aStarSearch(int start, int N, int** distances) {
    int min_cost = INT_MAX;

    struct Node {
        int city;
        int cost;
        int heuristic;
        int path[20];
        int path_size;

        Node() : city(0), cost(0), heuristic(0), path_size(0) {
            std::fill(path, path + 20, 0);
        }

        Node(int c, int cst, int h, const int* p, int p_size) : city(c), cost(cst), heuristic(h), path_size(p_size) {
            std::copy(p, p + p_size, path);
        }
    };

    Node* stack = (Node*)malloc(N * N * sizeof(Node));
    int stack_top = 0;

    Node initial;
    initial.city = start;
    initial.heuristic = heuristic(initial.path, initial.path_size, N, distances);
    initial.path[0] = start;
    initial.path_size = 1;
    stack[stack_top++] = initial;

    while (stack_top > 0) {
        Node node = stack[--stack_top];

        if (node.path_size == N && distances[node.city][start]) {
            min_cost = std::min(min_cost, node.cost + distances[node.city][start]);
            continue;
        }

        for (int i = 0; i < N; ++i) {
            bool in_path = false;
            for (int j = 0; j < node.path_size; ++j) {
                if (node.path[j] == i) {
                    in_path = true;
                    break;
                }
            }

            if (!in_path && distances[node.city][i]) {
                Node new_node;
                new_node.city = i;
                new_node.cost = node.cost + distances[node.city][i];
                new_node.path_size = node.path_size + 1;
                std::copy(node.path, node.path + node.path_size, new_node.path);
                new_node.path[node.path_size] = i;
                new_node.heuristic = heuristic(new_node.path, new_node.path_size, N, distances);
                stack[stack_top++] = new_node;
            }
        }
    }

    free(stack);
    return min_cost;
}
