//
//  main.cpp
//  JavaDecompiler
//
//  Created by Hades on 22/11/2020.
//


#include <iostream>
#include "Class.hpp"
#include "Parser.hpp"

int main(int argc, const char * argv[]) {
    Parser ps;
    ps.Parse("/Users/hades/Documents/OOP Reversing/JavaDecompiler/Simple.class");
    return 0;
}
