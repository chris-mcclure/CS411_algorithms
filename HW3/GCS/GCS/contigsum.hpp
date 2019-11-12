//
//  contigsum.hpp
//  GCS
//
//  Created by Chris McClure on 10/7/19.
//  Copyright © 2019 Chris McClure. All rights reserved.
//

#ifndef contigsum_h
#define contigsum_h
#include <iterator>
#include <algorithm>

//A. The GCS of the sequence.
//B. The greatest possible sum of a contiguous subsequence
//    that includes the first value in the sequence, or zero if all
//    such sums are negative.
//C. The greatest possible sum of a contiguous subsequence
//    that includes the last value in the sequence, or zero if all
//    such sums are negative.
//D. The sum of the entire sequence.

struct gcsValues{
    int gcsOfSeq = 0;
    int gcsWithFirstVal = 0;
    int gcsWithLastVal = 0;
    int sumOfSeq = 0;
};

int maximum(int valOfGcs, int valFirstHalf, int valAcrossMiddle){
    int max = valOfGcs;
    if(valFirstHalf > max)
        max = valFirstHalf;
    if(valAcrossMiddle > max)
        max = valAcrossMiddle;
    return max;
}

template <typename RAIter>
gcsValues incrementVals(RAIter first, gcsValues v){
    if(*first < 0){
        v.sumOfSeq += (*first);
        return v;
    }
    v.gcsOfSeq += (*first);
    v.gcsWithFirstVal += (*first);
    v.gcsWithLastVal += (*first);
    v.sumOfSeq += (*first);
    return v;
}

template <typename RAIter>
gcsValues recurse(RAIter first, RAIter last, size_t size){
    gcsValues val1;
    if(size == 1) return incrementVals(first, val1); // base case
    
    //recurse over both halves of the array
    RAIter mid = first + ((last - first)/2);
    size = std::distance(first, mid)+1;
    val1 = recurse(first, mid, size);
    size = std::distance(mid+1, last)+1;
    gcsValues val2 = recurse(mid+1, last, size);
    gcsValues val3 = {
                    maximum(val1.gcsOfSeq, val2.gcsOfSeq, val1.gcsWithLastVal + val2.gcsWithFirstVal),
                    std::max(val1.gcsWithFirstVal, val1.sumOfSeq + val2.gcsWithFirstVal),
                    std::max(val2.gcsWithLastVal, val2.sumOfSeq + val1.gcsWithLastVal),
                    val1.sumOfSeq + val2.sumOfSeq
                  };
    return val3;
}

template <typename RAIter>
int contigSum(RAIter first, RAIter last){
    int sum = 0;
    if(first == last) return sum;

    size_t size = std::distance(first, last);
    gcsValues v = recurse(first, last-1, size);
    sum = v.gcsOfSeq;
    return sum;
}


#endif /* contigsum_h */
