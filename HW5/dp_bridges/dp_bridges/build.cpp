//
//  build.cpp
//  dp_bridges
//
//  Created by Chris McClure on 11/10/19.
//  Copyright © 2019 Chris McClure. All rights reserved.
//

#include "build.hpp"
using std::vector;
using std::max;

// function recBridges
// uses top down (memoization) dynamic programming to calculate the maximum toll
// of bridges connecting west cities to east cities, such that no bridges cross or share a city in common.
int recBridges(const vector<Bridge> & bridges, int w, int e, vector<vector<int>> & table){
    int toll = 0;
    if(table[w][e] != -1) //if the value isn't -1, then the function has already calculated this position of the table.
        return table[w][e];
        
    for(auto & b: bridges){
        if(b[0] < w && b[1] < e) //bridges don't have common cities and aren't crossing.
            toll = max(recBridges(bridges, b[0], b[1], table)+b[2], toll);
    }
    table[w][e] = toll; //store that toll in the table to reuse later.
    return toll;
}


// function build
// returns 0 if the vector is empty,
// otherwise it returns the toll returned by recBridges.
int build(int w, int e, const vector<Bridge> & bridges){
    if(bridges.size() == 0)
        return 0;
    
    // creates a table with one extra row and column and intializes each position in the table to -1.
    // table[# of west cities][# of east cities] will be the maximum toll.
    auto table = vector<vector<int>>(w+1, vector<int>(e+1, -1));
    return recBridges(bridges, w, e, table);
}
