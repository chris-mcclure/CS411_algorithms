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
#include <iterator>
using std::distance;
#include <algorithm>


template<typename RAIter>
size_t inversions(RAIter first, RAIter last){
    size_t size = distance(first, last-1);
    
    return size;
    
    
}

#endif /* inversions_h */
