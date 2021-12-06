#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <queue>
#include <set>
#include <algorithm>
#include "Graph.h"

/* -------------------- PUBLIC FUNCTIONS -------------------- */

Graph::Graph() {
    vertices = 11316811;
    edges = 85331846;
    adjList.resize(vertices);

    LoadData();

    SCC();
}

void Graph::BFS(int id1, int id2) {
    // TODO for Dennis
}

// Find one user's entire spanning tree inward and outward by level
vector<vector<int>> Graph::MST(int id) {
    vector<vector<int>> connections;

    // Get following connection tree
    vector<int> following = FollowingTree(id);
    connections.push_back(following);

    // Get follower connection tree
    vector<int> follower = FollowerTree(id);
    connections.push_back(follower);

    return connections;
}

vector<int> Graph::GetIDSCC(int id) {
    for (int i = 0; i < scc.size(); i++) { // Search through all SCC's for one that contains id
        if (find(scc[i].begin(), scc[i].end(), id) != scc[i].end()) {
            return scc[i];
        }
    }

    vector<int> selfSCC(1, id); // If theoretically id not located, id is a SCC consisting of itself and only itself
    return selfSCC;
}


/* -------------------- PRIVATE HELPER FUNCTIONS -------------------- */

void Graph::LoadData() {
    fstream fin;
    string file("./Twitter-dataset/data/edges.csv");
    fin.open(file, ios::in);
    string line;
    string from;
    string to;
    while (getline(fin, line)) { // Load each edge of data into adjacency list format
        istringstream ss(line);
        getline(ss, from, ',');
        getline(ss, to);
        adjList[stoi(from)].push_back(stoi(to));
    }
}

void Graph::SCC() {
    stack<int> toProcess;
    vector<bool> visited(vertices, false);

    for (int i = 0; i < vertices; i++) { // Put vertexes in order on stack
        if (!visited[i]) {
            VisitVertex(i, visited, toProcess);
        }
    }

    vector<vector<int>> reverseAdjList; // Make reverse (transposed) version of adjacency list graph
    reverseAdjList.resize(vertices);
    for (int i = 0; i < vertices; i++) {
        for (auto j = 0; j < adjList[i].size(); j++) {
            reverseAdjList[j].push_back(i);
        }
        visited[i] = false; // Set back to false before second DFS
    }

    while (!toProcess.empty()) { // Check until each vertex checked
        int processing = toProcess.top();
        toProcess.pop();

        if (visited[processing]) { // If vertex not checked yet find new strongly connected component and add to vector of vectors
            vector<int> strongComponent;
            GetComponent(processing, reverseAdjList, visited, strongComponent);
            scc.push_back(strongComponent);
        }
    }
}

void Graph::GetComponent(int vertex, vector<vector<int>>& reverseAdjList, vector<bool>& visited, vector<int>& strongComponent) {
    visited[vertex] = true;
    strongComponent.push_back(vertex); // Add to strong component vector

    for (int i = 0; i < reverseAdjList[vertex].size(); i++) { // Use reverse so that inward connections used
        if (!visited[reverseAdjList[vertex][i]]) {
            GetComponent(reverseAdjList[vertex][i], reverseAdjList, visited, strongComponent); // DFS visit for each vertex in strong componenet using recursion
        }
    }
}

void Graph::VisitVertex(int vertex, vector<bool>& visited, stack<int>& toProcess) {
    visited[vertex] = true;

    for (int i = 0; i < adjList[vertex].size(); i++) {
        if (!visited[adjList[vertex][i]]) {
            VisitVertex(adjList[vertex][i], visited, toProcess); // DFS visit for each vertex to fill stack in order using recursion
        }
    }

    toProcess.push(vertex); // Add to processing stack
}

vector<int> Graph::FollowingTree(int id) {
    vector<int> following;
    following.push_back(0); // Index 0 will hold total connection amount

    int total = 0;
    int lastInLevel = id; // Use lastInLevel and last to correctly update level counts
    int last = -1;
    int lastTotal = 0; // Difference between total and this variables holds level count

    queue<int> toCheck;
    set<int> checked; // Make sure no values checked multiple times
    toCheck.push(id);
    checked.insert(id);

    while (!toCheck.empty()) {
        int checking = toCheck.front();
        toCheck.pop();


        for (int i = 0; i < adjList[checking].size(); i++) { // Look for next level followings
            if (checked.find(adjList[checking][i]) == checked.end()) { // Make sure no duplicates added to total
                toCheck.push(adjList[checking][i]);
                checked.insert(adjList[checking][i]);
                total++;
                last = adjList[checking][i];
            }
        }
        
        if (lastInLevel == checking) { // Push level count to vector and move to counting next vector
            lastInLevel = last;
            following.push_back(total - lastTotal);
            lastTotal = total;
        }
    }

    following[0] = total; // Update total count
    return following;
}

vector<int> Graph::FollowerTree(int id) {
    vector<int> follower;
    follower.push_back(0);

    int total = 0;
    int lastInLevel = id;
    int last = -1;
    int lastTotal = 0;

    queue<int> toCheck;
    set<int> checked;
    toCheck.push(id);
    checked.insert(id);

    while (!toCheck.empty()) {
        int checking = toCheck.front();
        toCheck.pop();

        for (int i = 0; i < adjList.size(); i++) { // Iterate through all following lists in adjList to find instances of checking
            if (checked.find(i) == checked.end()) {
                for (int j = 0; j < adjList[i].size(); j++) {
                    if (adjList[i][j] == checking) { // If vector of user id i has checking, then add to follower tree
                        toCheck.push(i);
                        checked.insert(i);
                        total++;
                        last = i;
                    }
                }
            }
        }
        
        if (lastInLevel == checking) {
            lastInLevel = last;
            follower.push_back(total - lastTotal);
            lastTotal = total;
        }    
    }

    follower[0] = total;
    return follower;
}