//
//  main.cpp
//  PersistentMap
//
//  Created by Geert Bosch on 11/27/15.
//  Copyright © 2015 MongoDB. All rights reserved.
//

#include <iostream>
#include <string>

#include "persistent_map.h"

#define invariant(_Expression)                     \
do {                                               \
if (!(_Expression)) {                              \
invariantFailed(#_Expression, __FILE__, __LINE__); \
}                                                  \
} while (false)

void invariantFailed(std::string message, std::string file, int line) {
        std::cerr << file << ":" << line << ": invariant failed: " << message << "\n";
        std::terminate();
}

int main(int argc, const char * argv[]) {
    persistent::map<int, int> m;
    invariant(m.empty());
    invariant(m.size() == 0);
    return 0;
}
