// Chris McClure
// 12/6/19
//
// huffcode.hpp  UNFINISHED
// Glenn G. Chappell
// 29 Nov 2015
//
// For CS 411/611 Fall 2015
// Assignment 6, Exercise A
// Header for class HuffCode
//
// Modified 11/22/17
// Chris Hartman
// For CS 411 Fall 2017

#ifndef FILE_HUFFCODE_H_INCLUDED
#define FILE_HUFFCODE_H_INCLUDED

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <memory>
#include <queue>
#include <string>

/* Node struct for binary tree construction */
struct Node{
    Node(){}
    Node(char key, int weight): _key(key), _weight(weight){}
    Node(std::shared_ptr<Node> & leftNode, std::shared_ptr<Node> & rightNode, int weight):
    _leftNode(leftNode), _rightNode(rightNode), _weight(weight){}
    
    std::shared_ptr<Node> _leftNode, _rightNode = nullptr;
    int _weight = 0;
    char _key = 0;
};

// Class HuffCode
// Encoding & decoding using a Huffman code
class HuffCode {

// ***** HuffCode: ctors, dctor, op= *****
public:

    // Compiler-generated default ctor, copy ctor, copy =, dctor used

// ***** HuffCode: general public functions *****
public:
    bool cmp(std::shared_ptr<Node> & lhs, std::shared_ptr<Node> & rhs);
    void setWeights(const std::unordered_map<char, int> & theweights);
    std::string encode(const std::string & text) const;
    std::string decode(const std::string & codestr) const;
    void weightMap(Node & node, std::string code);
    std::string recurseDecode(std::string & codestr, std::string::iterator & first, std::string::iterator & last) const;
    // ***** HuffCode: data members *****
private:
    Node root;
    std::unordered_map<char, std::string> lookup_map;
};  // End class HuffCode


#endif //#ifndef FILE_HUFFCODE_H_INCLUDED

