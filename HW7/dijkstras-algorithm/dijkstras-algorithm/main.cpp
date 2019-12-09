//
//  main.cpp
//  dijkstras-algorithm
//
//  Created by Chris McClure on 12/9/19.
//  Copyright © 2019 Chris McClure. All rights reserved.
//

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <vector>
using std::vector;

#define NUMVS 5

int minDistance(vector<int> & dist, vector<bool> & shortPath){
    int min = INT_MAX;
    int min_index = 0;
    
    for(int i = 0; i < NUMVS; i++){
        if(shortPath[i] == false && dist[i] <= min){
            min = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

void printSol(vector<int> & dist, int src, int dest){
    cout << "Distance from " << src << " to " << dest << " is " << dist[dest] - dist[src] << endl;
}

void dijkstra(vector<vector<int>> & graph, int src, int dest){
    vector<int> dist(NUMVS);
    vector<bool> shortPath(NUMVS);
    
    for(int i = 0; i < NUMVS; i++){
        dist[i] = INT_MAX;
        shortPath[i] = false;
    }
    
    dist[src] = 0;
    
    for(int i = 0; i < NUMVS - 1; i++){
        int u = minDistance(dist, shortPath);
        shortPath[u] = true;
        
        for(int j = 0; j < NUMVS; j++){
            if(!shortPath[j] && graph[u][j] && dist[u] != INT_MAX && dist[u] + graph[u][j] < dist[j])
                dist[j] = dist[u] + graph[u][j];
        }
    }
    printSol(dist, src, dest);
}

int main(void){
    int src = 0;
    int dest = 0;
    cout << "spec source: ";
    std::cin >> src;
    cout << "spec dest: ";
    std::cin >> dest;
//    vector<vector<int>> graph = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
//                                  { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
//                                  { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
//                                  { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
//                                  { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
//                                  { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
//                                  { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
//                                  { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
//                                  { 0, 0, 2, 0, 0, 0, 6, 7, 0 }
//    };
    
    vector<vector<int>> graph = {
        {0, 3, 0, 2, 8},
        {3, 0, 1, 0, 0},
        {0, 1, 0, 4, 1},
        {2, 0, 4, 0, 0},
        {8, 0, 1, 0, 0}
    };
    dijkstra(graph, src, dest);
    return 0;
        
}
