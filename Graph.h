 #pragma once
// Includes go here
#include <vector>
#include <stack>
using namespace std;

class Graph {
    public:
        // Public functions
        Graph();
        int BFS(int id1, int id2); // Breadth First Search, can modify parameters/return and copy/paste code in
        vector<vector<int>> GetConnections(int id); // Spanning Tree, additional non-graph specific algorithm
        vector<int> GetIDSCC(int id); // Get ID's SCC so menu/main class can print


    private:
        // Private variables
        vector<vector<int>> adjList;
        int vertices;
        int edges;
        vector<vector<int>> scc; // Includes all vertices but grouped into strongly connected components

        // Private helper functions
        void LoadData();
        void SCC(); // Algorithm that does Strongly Connected Components, learned about concepts through GeeksforGeeks
        // void GetComponent(int vertex, vector<vector<int>>& reverseAdjList, vector<bool>& visited, vector<int>& strongComponent); // Helper for SCC
        // void VisitVertex(int vertext, vector<bool>& visited, stack<int>& toProcess); // Helper for SCC
        vector<int> FollowingTree(int id);
        vector<int> FollowerTree(int id);
};