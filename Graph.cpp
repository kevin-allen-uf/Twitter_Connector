#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <queue>
#include <set>
#include "Graph.h"

Graph::Graph() {
    vertices = 11316811;
    edges = 85331846;
    adjList.resize(vertices);
    LoadData();
}

void Graph::LoadData() {
    fstream fin;
    string file("./Twitter-dataset/data/edges.csv");
    fin.open(file, ios::in);
    string line;
    string from;
    string to;
    while (getline(fin, line)) {
        istringstream ss(line);
        getline(ss, from, ',');
        getline(ss, to);
        adjList[stoi(from)].push_back(stoi(to));
    }
}

void Graph::BFS(int id1, int id2) {

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

// Find connections in Spanning Trees in common by level of following/followed?
vector<vector<int>> Graph::MST(int id1, int id2) {
    vector<vector<int>> commonConnections;
    return commonConnections;
}