//
//  main.cpp
//  dijkstras-algorithm
//
//  Created by Chris McClure on 12/9/19.
//  Copyright © 2019 Chris McClure. All rights reserved.
//
//  Code was taken from GeeksForGeeks https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/

#define CATCH_CONFIG_MAIN
#define INF INT_MAX
#include "catch.hpp"
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <vector>
using std::vector;


int minDistance(vector<int> & dist, vector<bool> & shortPath, int num_vertices){
    int min = INF;
    int min_index = 0;
    for(int i = 0; i < num_vertices; i++){
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

int dijkstra(vector<vector<int>> & graph, int src, int dest, int num_vertices){
    vector<int> dist(num_vertices);
    vector<bool> shortPath(num_vertices);
    for(int i = 0; i < num_vertices; i++){
        dist[i] = INF;
        shortPath[i] = false;
    }
    
    dist[src] = 0;
    for(int i = 0; i < num_vertices - 1; i++){
        int u = minDistance(dist, shortPath, num_vertices);
        shortPath[u] = true;
        for(int j = 0; j < num_vertices; j++){
            if(!shortPath[j] && graph[u][j] && dist[u] != INF && dist[u] + graph[u][j] < dist[j])
                dist[j] = dist[u] + graph[u][j];
        }
    }
    printSol(dist, src, dest);
    return dist[dest] - dist[src];
}

// Reference the provide pictures for the layout of the graphs.
TEST_CASE("Small graph", "[graph]"){
    cout << "\t\t SMALL GRAPH" << endl;
    int num_vertices = 5;
    int num_nodes = num_vertices*num_vertices;
    vector<vector<int>> graph = {
           //   0  1  2  3  4
        /* 0 */{0, 3, 0, 2, 8},
        /* 1 */{3, 0, 1, 0, 0},
        /* 2 */{0, 1, 0, 4, 1},
        /* 3 */{2, 0, 4, 0, 0},
        /* 4 */{8, 0, 1, 0, 0}
    };
    
    vector<vector<int>> table(num_nodes, vector<int>(num_nodes));
    for(int i = 0; i < num_vertices; i++){
        for(int j = 0; j < num_vertices; j++){
            table[i][j] = dijkstra(graph, i, j, num_vertices);
        }
    }
    
    SECTION("0 to any vertice"){
        REQUIRE(table[0][0] == 0);
        REQUIRE(table[0][1] == 3);
        REQUIRE(table[0][2] == 4);
        REQUIRE(table[0][3] == 2);
        REQUIRE(table[0][4] == 5);
        
        REQUIRE(table[1][0] == table[0][1]);
        REQUIRE(table[1][1] == 0);
        REQUIRE(table[1][2] == 1);
        REQUIRE(table[1][3] == 5);
        REQUIRE(table[1][4] == 2);
        
        REQUIRE(table[2][0] == table[0][2]);
        REQUIRE(table[2][1] == table[1][2]);
        REQUIRE(table[2][2] == 0);
        REQUIRE(table[2][3] == 4);
        REQUIRE(table[2][4] == 1);
        
        REQUIRE(table[3][0] == table[0][3]);
        REQUIRE(table[3][1] == table[1][3]);
        REQUIRE(table[3][2] == table[2][3]);
        REQUIRE(table[3][3] == 0);
        REQUIRE(table[3][4] == 5);
        
        REQUIRE(table[4][0] == table[0][4]);
        REQUIRE(table[4][1] == table[1][4]);
        REQUIRE(table[4][2] == table[2][4]);
        REQUIRE(table[4][3] == table[3][4]);
        REQUIRE(table[4][4] == 0);
    }
    cout << "\n";
}

TEST_CASE("Large graph", "[graph]"){
    cout << "\t\t LARGE GRAPH" << endl;
    int num_vertices = 9;
    int num_nodes = num_vertices*num_vertices;
    vector<vector<int>> graph = {
           //   0  1  2  3  4  5  6  7  8
        /* 0 */{0, 2, 6, 7, 2, 0, 6, 0, 0},
        /* 1 */{2, 0, 3, 6, 4, 2, 0, 0, 0},
        /* 2 */{6, 3, 0, 0, 5, 4, 0, 0, 3},
        /* 3 */{7, 6, 0, 0, 9, 0, 3, 7, 0},
        /* 4 */{2, 4, 5, 9, 0, 10, 2, 2, 1},
        /* 5 */{0, 2, 4, 0, 10, 0, 0, 1, 4},
        /* 6 */{8, 0, 0, 3, 2, 0, 0, 1, 8},
        /* 7 */{0, 0, 0, 7, 2, 1, 1, 0, 5},
        /* 8 */{0, 0, 3, 0, 1, 4, 8, 5, 0}
    };
    vector<vector<int>> table(num_nodes, vector<int>(num_nodes));
    for(int i = 0; i < num_vertices; i++){
        for(int j = 0; j < num_vertices; j++){
            table[i][j] = dijkstra(graph, i, j, num_vertices);
        }
    }
    
    SECTION("0 to any vertice"){
        REQUIRE(table[0][0] == 0);
        REQUIRE(table[0][1] == 2);
        REQUIRE(table[0][2] == 5);
        REQUIRE(table[0][3] == 7);
        REQUIRE(table[0][4] == 2);
        REQUIRE(table[0][5] == 4);
        REQUIRE(table[0][6] == 4);
        REQUIRE(table[0][7] == 4);
        REQUIRE(table[0][8] == 3);

        REQUIRE(table[1][0] == table[0][1]);
        REQUIRE(table[1][1] == 0);
        REQUIRE(table[1][2] == 3);
        REQUIRE(table[1][3] == 6);
        REQUIRE(table[1][4] == 4);
        REQUIRE(table[1][5] == 2);
        REQUIRE(table[1][6] == 4);
        REQUIRE(table[1][7] == 3);
        REQUIRE(table[1][8] == 5);

        REQUIRE(table[2][0] == table[0][2]);
        REQUIRE(table[2][1] == table[1][2]);
        REQUIRE(table[2][2] == 0);
        REQUIRE(table[2][3] == 9);
        REQUIRE(table[2][4] == 4);
        REQUIRE(table[2][5] == 4);
        REQUIRE(table[2][6] == 6);
        REQUIRE(table[2][7] == 5);
        REQUIRE(table[2][8] == 3);
        
        REQUIRE(table[3][0] == table[0][3]);
        REQUIRE(table[3][1] == table[1][3]);
        REQUIRE(table[3][2] == table[2][3]);
        REQUIRE(table[3][3] == 0);
        REQUIRE(table[3][4] == 5);
        REQUIRE(table[3][5] == 5);
        REQUIRE(table[3][6] == 3);
        REQUIRE(table[3][7] == 4);
        REQUIRE(table[3][8] == 6);
        
        REQUIRE(table[4][0] == table[0][4]);
        REQUIRE(table[4][1] == table[1][4]);
        REQUIRE(table[4][2] == table[2][4]);
        REQUIRE(table[4][3] == table[3][4]);
        REQUIRE(table[4][4] == 0);
        REQUIRE(table[4][5] == 3);
        REQUIRE(table[4][6] == 2);
        REQUIRE(table[4][7] == 2);
        REQUIRE(table[4][8] == 1);
        
        REQUIRE(table[5][0] == table[0][5]);
        REQUIRE(table[5][1] == table[1][5]);
        REQUIRE(table[5][2] == table[2][5]);
        REQUIRE(table[5][3] == table[3][5]);
        REQUIRE(table[5][4] == table[4][5]);
        REQUIRE(table[5][5] == 0);
        REQUIRE(table[5][6] == 2);
        REQUIRE(table[5][7] == 1);
        REQUIRE(table[5][8] == 4);
        
        REQUIRE(table[6][0] == table[0][6]);
        REQUIRE(table[6][1] == table[1][6]);
        REQUIRE(table[6][2] == table[2][6]);
        REQUIRE(table[6][3] == table[3][6]);
        REQUIRE(table[6][4] == table[4][6]);
        REQUIRE(table[6][5] == table[5][6]);
        REQUIRE(table[6][6] == 0);
        REQUIRE(table[6][7] == 1);
        REQUIRE(table[6][8] == 3);
        
        REQUIRE(table[7][0] == table[0][7]);
        REQUIRE(table[7][1] == table[1][7]);
        REQUIRE(table[7][2] == table[2][7]);
        REQUIRE(table[7][3] == table[3][7]);
        REQUIRE(table[7][4] == table[4][7]);
        REQUIRE(table[7][5] == table[5][7]);
        REQUIRE(table[7][6] == table[6][7]);
        REQUIRE(table[7][7] == 0);
        REQUIRE(table[7][8] == 3);
        
        REQUIRE(table[8][0] == table[0][8]);
        REQUIRE(table[8][1] == table[1][8]);
        REQUIRE(table[8][2] == table[2][8]);
        REQUIRE(table[8][3] == table[3][8]);
        REQUIRE(table[8][4] == table[4][8]);
        REQUIRE(table[8][5] == table[5][8]);
        REQUIRE(table[8][6] == table[6][8]);
        REQUIRE(table[8][7] == table[7][8]);
        REQUIRE(table[8][8] == 0);
    }
}
