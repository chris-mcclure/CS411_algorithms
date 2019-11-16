//
//  build.cpp
//  dp_bridges
//
//  Created by Chris McClure on 11/10/19.
//  Copyright © 2019 Chris McClure. All rights reserved.
//

#include "build.hpp"
using std::vector;
using std::sort;
using std::max;

bool cmp(vector<int> & b1, vector<int> & b2){
    if(b1[0] == b2[0])
        return b1[1] < b2[1];
    return b1[0] < b2[0];
}

int recBridges(vector<Bridge> & bridges, int w, int e, vector<vector<int>> & table){
    int toll = 0;
    if(table[w][e] != -1)
        return table[w][e];
        
    for(auto & b: bridges){
        if(b[0] < w && b[1] < e)
            toll = max(recBridges(bridges, b[0], b[1], table)+b[2], toll);
    }
    table[w][e] = toll;
    return toll;
}

int build(int w, int e, const vector<Bridge> & bridges){
    auto table = vector<vector<int>>(w+1, vector<int>(e+1, -1));
    if(bridges.size() == 0)
        return 0;
    else if(bridges.size() == 1)
        return bridges[0][2];
    auto copyOfBridges = bridges;
    sort(copyOfBridges.begin(), copyOfBridges.end(), cmp);
    return recBridges(copyOfBridges, w, e, table);
}
