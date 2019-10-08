//
//  build.cpp
//  Building-Bridges
//
//  Created by Chris McClure on 9/19/19.
//  Copyright © 2019 Chris McClure. All rights reserved.
//

#include "build.h"
//checks for crossing bridges and multiple bridges beginning or ending on the same city
int check_collisions(vector<Bridge> & subset, int subset_size){
    int toll = 0;
    for(int i = 0; i < subset_size; i++){
        for(int j = i+1; j < subset_size; j++){
            if((subset[i][0] <= subset[j][0] && subset[i][1] >= subset[j][1]) || //if A < C and B > D, then the bridges are crossing.
               (subset[i][0] >= subset[j][0] && subset[i][1] <= subset[j][1])){
                return 0;
            }
        }
        toll += subset[i][2];
    }
    return toll;
}

int build(int w, int e, const vector<Bridge> & bridges){    
    auto num_of_bridges = bridges.size(); // get the size of the bridges
    int toll = 0;
    int max_toll = 0;
    int subset_size = 0;
    
    vector<Bridge> subset(num_of_bridges); //size of subset is number of bridges given
    
    //this for loops creates all of the subsets of the given bridges
    for(int i = 1; i < 1<<num_of_bridges; i++){ // from 0 up to 2^n
        // 0000 = empty set
        // 0001 = a
        // 0010 = b
        // 0011 = ab
        // 0100 = c
        // ...
        for(int j = 0; j < num_of_bridges; j++){ // from 0 to n
            if(i&1<<j){ // check to see if the bits are set
                subset[subset_size] = bridges[j]; //if so, add the bridges at j to the subset to be compared in check_collision
                subset_size++;
            }
        }
        toll = check_collisions(subset, subset_size);
        if(toll > max_toll){
            max_toll = toll;
        }
        subset_size = 0; //reset the subset size to 0, so we can
    }
    return max_toll;
}

