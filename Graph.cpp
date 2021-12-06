#include "Graph.h"
#include <fstream>
#include <string>
#include <iostream>

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
​
    string line;
    string from;
    string to;
​
    while (getline(fin, line)) {
​
        istringstream ss(line);
        getline(ss, from, ',');
        getline(ss, to);
        adjList[stoi(from)].push_back(stoi(to));
    }
}

void Graph::BFS(int id1, int id2) {

}

void Graph::MST(int id) {
    // Find one user's entire spanning tree inward and outward by level
}

void Graph::MST(int id1, int id2) {
    // Find connections in Spanning Trees in common by level of following/followed?
}