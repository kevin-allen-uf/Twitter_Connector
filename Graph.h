#pragma once
// Includes go here
#include <vector>
using namspace std;

class Graph {
    public:
        Graph();
        void LoadData();
        void BFS(); // Breadth First Search, can modify parameters/return and copy/paste code in
        void MST(); // Modified Spanning Tree, can modify parameters/return and copy/paste code in

    private:
        // Private variables and functions
        vector<vector<int>> adjList;
        int vertices;
        int edges;

};