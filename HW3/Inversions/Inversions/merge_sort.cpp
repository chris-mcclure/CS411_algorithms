// merge_sort.cpp
// Glenn G. Chappell
// 9 Oct 2015
//
// For CS 411/611 Fall 2015
// Merge Sort using Iterators

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <vector>
using std::vector;
#include <cstddef>
using std::size_t;
#include <algorithm>
using std::copy;
#include <iterator>
using std::distance;
using std::advance;
#include <type_traits>
using std::remove_reference;


// stableMerge
// Merge two halves of a sequence, each sorted, into a single sorted
// sequence in the same location. Merge is done in a stable manner.
// Requirements on Types:
//     RAIter is a forward iterator type.
//     The value type of RAIter has default ctor, dctor, copy=,
//      operator<.
//     operator< is a total order on the value type of RAIter.
// Pre:
//     [first, middle) and [middle, last) are valid ranges, each sorted
//      by <.
// Post:
//     [first, last) contains the same items as it did initially, but
//      now sorted by < (in a stable manner).
template <typename RAIter>
size_t stableMerge(RAIter first, RAIter middle, RAIter last)
{
    size_t inversions = 0;
    // ** C++03:
    using Value = typename std::iterator_traits<RAIter>::value_type;
    // ** C++11:
    // using Value = typename remove_reference<decltype(*first)>::type;
    // ** Is this really better?

    vector<Value> buffer(distance(first, last));
                                // Buffer for temporary copy of data
    RAIter in1 = first;         // Read location in 1st half
    RAIter in2 = middle;        // Read location in 2nd half
    auto out = buffer.begin();  // Write location in buffer
    // ** auto! That *is* better than vector<Value>::iterator

    // Merge two sorted lists into a single list in buff.
    while (in1 != middle && in2 != last)
    {
        if (*in2 < *in1){  // Must do comparison this way, to be stable.
            *out++ = *in2++;
            inversions += distance(in1, middle); // Number of inversions is equal to the amount of values still in the first half of the array.
        }
        else
            *out++ = *in1++;
    }

    // Copy remainder of original sequence to buffer.
    // Only one of the following two copy calls will do anything, since
    //  the other is given an empty source range.
    copy(in1, middle, out);
    copy(in2, last, out);

    // Copy buffer contents back to original sequence location.
    copy(buffer.begin(), buffer.end(), first);
    return inversions;
}


// mergeSort
// Sorts a sequence, using Merge Sort.
// Recursive.
// Requirements on Types:
//     RAIter is a forward iterator type.
//     The value type of RAIter has default ctor, dctor, copy=,
//      operator<.
//     operator< is a total order on the value type of RAIter.
// Pre:
//     [first, last) is a valid range.
// Post:
//     [first, last) contains the same items as it did initially,
//      but now sorted by < (in a stable manner).
template <typename RAIter>
size_t mergeSort(RAIter first, RAIter last)
{
    // Compute size of sequence
    size_t size = distance(first, last);
    // BASE CASE
    if (size <= 1) return 0;
    // Find iterator pointing to the middle of the array.
    RAIter middle = first + ((last - first) / 2);
    // Recursively sort the two lists
    size_t m = mergeSort(first, middle);
    size_t n = mergeSort(middle, last);
    // And merge them
    size_t total = stableMerge(first, middle, last) + m + n;
    return total;
}

