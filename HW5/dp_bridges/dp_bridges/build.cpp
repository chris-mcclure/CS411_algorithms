//
//  build.cpp
//  dp_bridges
//
//  Created by Chris McClure on 11/10/19.
//  Copyright © 2019 Chris McClure. All rights reserved.
//

#include "build.hpp"
using std::vector;
using std::cout;
using std::endl;
using std::sort;
using std::max;

bool cmp(const vector<int> & w, const vector<int> & e){
    return w[0] < e[0];
}

int check_collisions(const vector<int> & b1, const vector<int> & b2){

    if((b1[0] < b2[0] && b1[1] > b2[1]) ||
       (b1[0] > b2[0] && b1[1] < b2[1])){
        return 0;
    }
    else if((b1[0] == b2[0]) || (b1[1] == b2[1]))
        return max(b1[2], b2[2]);
    else
        return b1[2]+b2[2];
}

int recurseBridges(vector<Bridge> & bridges, vector<int> & memo, int n){
    int toll = 0;
    if(n == bridges.size()){
        return toll;
    }
    else if(bridges.size() == 1){
        toll = bridges[0][2];
    }
    else
        toll += check_collisions(bridges[n], bridges[n+1]);
    cout << "toll: " << memo[n] << endl;
    return toll;
}

int memoBridges(vector<Bridge> & bridges){
    auto numOfBridges = bridges.size();
    vector<int> bridgetable(numOfBridges+1);
    return recurseBridges(bridges, bridgetable, 0);
}


int build(int w, int e, const vector<Bridge> & bridges){
    // sort bridges by west city
    vector<Bridge> sortedBridges;
    for(int i = 0; i < bridges.size(); i++){
        sortedBridges.push_back(bridges[i]);
    }
    sort(sortedBridges.begin(), sortedBridges.end(), cmp);
    return memoBridges(sortedBridges);
}
