#include "ArgumentManager.h"
#include <fstream>
#include <iostream>
#include <queue>
using namespace std;

// RESOURCES: GRAPH.ZIP
/* void DFS(int **graph, int source, int n){
    stack<int> s; // Initialize stack
    bool *visited = new bool[n]; // Initialize visited array
    for(int i = 0; i < n; i++){
        visited[i] = false;
    }
    s.push(source);
    while(!s.empty()){ // Perform DFS
        int v = s.top();
        s.pop();
        if(!visited[v]){
            cout << v << " ";
            visited[v] = true;
        }
        for(int i = 0; i < n; i++){ // Push adjacent vertices to stack
            if(graph[v][i] != 0 && !visited[i]){
                s.push(i);
            }
        }
    }
    cout << endl;
    delete [] visited;
}*/ 
bool dfs(int node, vector<bool> &visited, vector<bool> &recursionStack,
         vector<vector<int>> &adjList) {
  visited[node] = true;
  recursionStack[node] = true;
  for (int neighbor : adjList[node]) {
    if (!visited[neighbor] && dfs(neighbor, visited, recursionStack, adjList)) {
      return true;
    } else if (recursionStack[neighbor]) {
      return true;
    }
  }
  recursionStack[node] = false;
  return false;
}

bool hasCycle(vector<vector<int>> &adjList) {
  int numNodes = adjList.size();
  vector<bool> visited(numNodes, false);
  vector<bool> recursionStack(numNodes, false);
  for (int i = 0; i < numNodes; i++) {
    if (!visited[i] && dfs(i, visited, recursionStack, adjList)) {
      return true;
    }
  }
  return false;
}

int main(int argc, char *argv[]) {
  ArgumentManager am(argc, argv);
  ifstream fin(am.get("input"));
  ofstream fout(am.get("output"));
  int numNodes;
  fin >> numNodes;
  vector<vector<int>> adjList(numNodes);
  int from, to;
  while (fin >> from >> to) {
    adjList[from].push_back(to);
  }
  fin.close();
  if (hasCycle(adjList)) {
    fout << "TRUE" << endl;
  } else {
    fout << "FALSE" << endl;
  }
  fout.close();
  return 0;
}