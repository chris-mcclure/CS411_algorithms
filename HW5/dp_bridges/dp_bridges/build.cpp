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
        cout << "bridges are crossing" << endl;
//        return 0;
        return max(b1[2], b2[2]);
    }
    else if((b1[0] == b2[0]) || (b1[1] == b2[1])){
        cout << "bridges have common city" << endl;
        return max(b1[2], b2[2]);
    }
    else
        return b1[2]+b2[2];
}

int recurseBridges(vector<Bridge> & bridges, vector<int> & memo, int n){
    cout << "size: " << bridges.size() << endl;
    cout << "n: " << n << endl;
    int result = 0;
    if(memo[n] != 0){
        cout << "in memo if statement" << endl;
        return memo[n];
    }
    
    if(n == bridges.size()){
        cout << "size == 0" << endl;
        return 0;
    }
    else if(bridges.size() == 1){
        cout << "size == 1" << endl;
        return bridges[0][2];
    }
    else{
        cout << "n: " << n << endl;
        cout << "before check collisions" << endl;
        result = check_collisions(bridges[n], bridges[n+1]);
//        result = recurseBridges(bridges, memo, n+1);
    }
    return result;
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
