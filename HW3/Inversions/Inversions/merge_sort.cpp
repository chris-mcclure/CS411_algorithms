// merge_sort.cpp
// Glenn G. Chappell
// 9 Oct 2015
//
// For CS 411/611 Fall 2015
// Merge Sort using Iterators

#include <vector>
#include <cstddef>
#include <algorithm>
#include <iterator>


// stableMerge
// Merge two halves of a sequence, each sorted, into a single sorted
// sequence in the same location. Merge is done in a stable manner.
// Returns the amount of items remaining in the first half (inversions).
// Requirements on Types:
//     RAIter is a random access iterator type.
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
std::size_t stableMerge(RAIter first, RAIter middle, RAIter last)
{
    std::size_t numInversions = 0;
    // ** C++03:
    using Value = typename std::iterator_traits<RAIter>::value_type;
    // ** C++11:
    // using Value = typename remove_reference<decltype(*first)>::type;
    // ** Is this really better?

    std::vector<Value> buffer(std::distance(first, last));
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
            numInversions += (middle - in1); // Number of inversions is equal to the amount of values still in the first half of the array.
        }
        else
            *out++ = *in1++;
    }

    // Copy remainder of original sequence to buffer.
    // Only one of the following two copy calls will do anything, since
    //  the other is given an empty source range.
    std::copy(in1, middle, out);
    std::copy(in2, last, out);

    // Copy buffer contents back to original sequence location.
    std::copy(buffer.begin(), buffer.end(), first);
    return numInversions;
}

// mergeSort
// Sorts a sequence, using Merge Sort. Returns the value returned by stableMerge.
// Recursive.
// Requirements on Types:
//     RAIter is a random access iterator type.
//     The value type of RAIter has default ctor, dctor, copy=,
//      operator<.
//     operator< is a total order on the value type of RAIter.
// Pre:
//     [first, last) is a valid range.
// Post:
//     [first, last) contains the same items as it did initially,
//      but now sorted by < (in a stable manner).
template <typename RAIter>
std::size_t mergeSort(RAIter first, RAIter last)
{
    // Compute size of sequence
    std::size_t size = std::distance(first, last);
    // BASE CASE
    if (size <= 1) return 0;
    // Find iterator pointing to the middle of the array.
    RAIter middle = first + ((last - first) / 2);
    // Recursively sort and find the number of inversions in the first and second halves
    // of the list.
    std::size_t firstHalfInversions = mergeSort(first, middle);
    std::size_t secondHalfInversions = mergeSort(middle, last);
    // merge them and return the total amount of inversions.
    return (stableMerge(first, middle, last) + firstHalfInversions + secondHalfInversions);
}


