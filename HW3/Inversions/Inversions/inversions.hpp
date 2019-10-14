//
//  inversions.hpp
//  Inversions
//
//  Created by Chris McClure on 10/7/19.
//  Copyright © 2019 Chris McClure. All rights reserved.
//

#ifndef inversions_h
#define inversions_h

#include "merge_sort.cpp"
template<typename RAIter>
size_t inversions(RAIter first, RAIter last){
    if(first == last) // If iterators are equal in the beginning, the array is empty.
        return 0;
    return mergeSort(first, last);;
}

#endif /* inversions_h */
