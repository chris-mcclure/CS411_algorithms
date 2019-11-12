//
//  build.hpp
//  dp_bridges
//
//  Created by Chris McClure on 11/10/19.
//  Copyright © 2019 Chris McClure. All rights reserved.
//

#ifndef build_hpp
#define build_hpp

#include <iostream>
#include <vector>
#include <algorithm>

using Bridge = std::vector<int>;
int build(int w, int e, const std::vector<Bridge> & bridges);

#endif /* build_hpp */
