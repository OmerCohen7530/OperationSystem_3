#include "Kosaraju.hpp"
#include <iostream>
#include <list>
#include <algorithm>
#include <functional>
#include <vector>
#include <deque>

using namespace std;

void Kosaraju(const std::vector<std::vector<int>>& adj, const std::vector<std::vector<int>>& adjT, int vertices) {
    std::vector<bool> visited(vertices, false);
    std::vector<int> order;

    // First DFS to find the finishing order
    std::function<void(int)> dfs1 = [&](int u) {
        visited[u] = true;
        for (int v : adj[u]) {
            if (!visited[v]) {
                dfs1(v);
            }
        }
        order.push_back(u);
    };

    for (int i = 0; i < vertices; ++i) {
        if (!visited[i]) {
            dfs1(i);
        }
    }

    std::reverse(order.begin(), order.end());
    std::vector<int> component(vertices, -1);
    int comp = 0;

    // Second DFS on the transposed graph
    std::function<void(int)> dfs2 = [&](int u) {
        component[u] = comp;
        for (int v : adjT[u]) {
            if (component[v] == -1) {
                dfs2(v);
            }
        }
    };

    for (int u : order) {
        if (component[u] == -1) {
            dfs2(u);
            comp++;
        }
    }

    std::cout << "Total strongly connected components: " << comp << std::endl;
}