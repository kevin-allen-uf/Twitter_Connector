#pragma once
// Includes go here
#include <vector>
using namespace std;

class Graph {
    public:
        Graph();
        void LoadData();
        void BFS(int id1, int id2); // Breadth First Search, can modify parameters/return and copy/paste code in
        void MST(int id);
        void MST(int id1, int id2); // Modified Spanning Tree, can modify parameters/return and copy/paste code in

    private:
        // Private variables and functions
        vector<vector<int>> adjList;
        int vertices;
        int edges;

};