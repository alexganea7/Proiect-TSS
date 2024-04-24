#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <climits>
#include <queue>
using namespace std;

class Graph{

public:
    Graph();
    Graph(unordered_map<int, unordered_set<int>>);
    Graph(const Graph&);
    unordered_map<int, unordered_set<int>> get_adj();
    int get_x();
    vector<int> getNodes();
    vector<pair<int, int>> getEdges();
    void insertEdge(int node1, int node2);
    void deleteEdge(int node1, int node2);
    void insertNode(int node = -1);
    void deleteNode(int node);
    bool checkAdj(int node1, int node2);
    void partialTree(unordered_map<int, int>& tata);
    void bfs_pt(int node, unordered_set<int>& visited, unordered_map<int, int>& tata);
    bool acyclicity();
    
private:
    unordered_map<int, unordered_set<int>> adj;
    int x = INT_MAX;
};

void Graph::insertEdge(int node1, int node2){
    if(adj[node1].find(node2) == adj[node1].end())
        adj[node1].insert(node2);
    if(adj[node2].find(node1) == adj[node2].end())
        adj[node2].insert(node1);
}

void Graph::deleteEdge(int node1, int node2){
    if(adj[node1].find(node2) != adj[node1].end())
        adj[node1].erase(node2);
    if(adj[node2].find(node1) != adj[node2].end())
        adj[node2].erase(node1);
}

bool Graph::checkAdj(int node1, int node2){
    return (adj[node1].find(node2) != adj[node1].end());
}

void Graph::deleteNode(int node){
    if(adj.find(node) == adj.end())
        return;
    else{
        for(auto i:adj[node])
            adj[i].erase(node);
        adj.erase(node);
    }
}
void Graph::insertNode(int node){
    if(adj.find(node) != adj.end())
        return;
    if(node!=-1){
        adj.insert({node, {}});
    }
    else{
        adj.insert({x, {}});
        x--;
    }
}

unordered_map<int, unordered_set<int>> Graph::get_adj(){
    return this->adj;
}

int Graph::get_x(){
    return this->x;
}

Graph::Graph(const Graph& ob){
    adj = ob.adj;
    x = ob.x;
}
Graph::Graph(unordered_map<int, unordered_set<int>> adj){
    this->adj = adj;
    this->x = x;
}

Graph::Graph(){}

vector<int> Graph::getNodes(){
    vector<int> nodes;
    for(auto i:adj){
        nodes.push_back(i.first);
    }
    return nodes;}

vector<pair<int, int>> Graph::getEdges(){
    vector<pair<int, int>> muchii;
    for(auto i:adj){
       for(auto j:i.second){
            if(j>i.first)
                muchii.push_back(make_pair(i.first, j));
        }
    }
    return muchii;}

void Graph::partialTree(unordered_map<int, int>& tata){
    unordered_set<int> visited;
    vector<int> nodes = getNodes();
    tata.clear();
    for(auto i:nodes){
        if(visited.find(i) == visited.end())
            bfs_pt(i, visited, tata);
    }
}

void Graph::bfs_pt(int node, unordered_set<int>& visited, unordered_map<int, int>& tata){
    queue<int> q;
    q.push(node);
    tata[node] = -1;
    visited.insert(node);
    while(!q.empty()){
        node = q.front();
        q.pop();
        for(int i:adj[node]){
            if(visited.find(i)==visited.end()){
                tata[i] = node;
                visited.insert(i);
                q.push(i);
            }
        }
    }
}

bool Graph::acyclicity(){
    vector<pair<int, int>> edges = getEdges();
    unordered_map<int, int> tata;
    partialTree(tata);
    for(auto i:edges){
        if(!(tata[i.first]==i.second || tata[i.second] == i.first))
            return 0;
    }
    return 1;}
