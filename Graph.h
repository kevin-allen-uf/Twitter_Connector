// Code developed by JDK Co. (John Ridgeway, Dennis Kim, Kevin Allen)

#pragma once
#include <vector>
#include <stack>
using namespace std;

class Graph {
    public:
        // Public functions
        Graph();
        bool BFS(int id1, int id2, int &levels); // Breadth First Search, can modify parameters/return and copy/paste code in
        vector<vector<int>> GetConnections(int id); // Spanning Tree, additional non-graph specific algorithm
        vector<int> GetIDSCC(int id); // Get ID's SCC so menu/main class can print


    private:
        // Private variables
        vector<vector<int>> adjList;
        int vertices;
        int edges;
        vector<vector<int>> scc; // Includes all vertices but grouped into strongly connected components

        // Private helper functions
        void LoadData(); // Loads graph data into adjList private variable
        void SCC(); // Kosaraju's Algorithm for Strongly Connected Components, learned about through GeeksforGeeks but implemented via user-defined explicit call stack "recursion"
        void VisitVertex(int startVertex, vector<bool>& visited, vector<int>& retIndexes, stack<int>& toProcess); // Helper for SCC
        vector<int> GetComponent(int startVertex, vector<vector<int>>& reverseAdjList, vector<bool>& visited, vector<int>& retIndexes); // Helper for SCC
        vector<int> FollowingTree(int id); // Helper for GetConnections
        vector<int> FollowerTree(int id); // Helper for GetConnections
};