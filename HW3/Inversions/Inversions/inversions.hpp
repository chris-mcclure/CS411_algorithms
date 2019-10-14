//
//  inversions.hpp
//  Inversions
//
//  Created by Chris McClure on 10/7/19.
//  Copyright © 2019 Chris McClure. All rights reserved.
//
//  Credit: Functions mergeSort and stableMerge are taken from
//  Dr. Chappell's Stable MergeSort example.
//
//  stableMerge and mergeSort have both been changed to return a value of the number
//  of inversions in the dataset rather than returning void as they previously were.
//

#ifndef inversions_h
#define inversions_h
#include "merge_sort.cpp"

// inversions
// calculates the number of decreasing values in an array that must be moved before
// the array is in ascending order.
template<typename RAIter>
size_t inversions(RAIter first, RAIter last){
    if(first == last) return 0;// If iterators are equal in the beginning, the array is empty.
    return mergeSort(first, last);
}

#endif /* inversions_h */
