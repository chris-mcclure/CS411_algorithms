// huffcode.cpp  UNFINISHED
// Glenn G. Chappell
// 29 Nov 2015
//
// For CS 411/611 Fall 2015
// Assignment 6, Exercise A
// Source for class HuffCode
//
// Modified 11/22/17
// Chris Hartman
// For CS 411 Fall 2017

#include "huffcode.hpp"  // for class HuffCode declaration
#include <string>
using std::string;
#include <unordered_map>
using std::unordered_map;
#include <iostream>
using std::cout;
using std::endl;
#include <algorithm>
using std::sort;
using std::pair;
#include <vector>
using std::vector;
#include <iterator>
using std::advance;

void HuffCode::setWeights(const unordered_map<char, int> & theweights)
{
    vector<pair<char, int>> sortedWeights(theweights.begin(),theweights.end());
    sort(sortedWeights.begin(), sortedWeights.end(), [&](pair<char,int> & a, pair<char,int> & b){
        return a.second < b.second;
    });
    
    cout << endl;
    for(auto & weight: sortedWeights){
        cout << "first: " << weight.first << " second: " << weight.second << endl;
        weights = weight.second;
    }
    cout << endl;
}


string HuffCode::encode(const string & text) const
{
    string huffstring = "";
    if(text.size() == 0)
        return huffstring;
    // WRITE THIS!!!
    for(auto & letter: text){
        if(letter == 'a')
            huffstring += "1";
        else if(letter == 'b')
            huffstring += "01";
        else
            huffstring += "00";
    }
    cout << "\nhuffstring: " << huffstring << endl;
    return huffstring;  // DUMMY RETURN
}

//string HuffCode::recurseDecode(string & codestr, string::iterator & first, string::iterator & last) const{
//    string huffstring = "";
//    if(first == last)
//        return huffstring;
//
//    for(auto & letter: codestr){
//        if(letter == '0'){
//            advance(first, 1);
//            huffstring += recurseDecode(codestr, first, last);
//        }
////        else huffstring += recurseDecode(codestr, first, last);
//    }
//    cout << "huffstring1: " << huffstring << endl;
//    return huffstring;
//}

string HuffCode::decode(const string & codestr) const
{
    if(codestr.size() == 0)
        return "";
    
    auto code = codestr;
    string::iterator first = code.begin();
    string::iterator last = code.end()-1;
//    return recurseDecode(code, first, last);
    return "";
    
}

