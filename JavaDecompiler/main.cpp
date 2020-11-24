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
    
    for (int i = 0; i < ps.cs->attributes_count; i++) {
        attribute_info attr = ps.cs->attribute[i];
        int index = attr.attribute_name_index;
        CONSTANT_Utf8_info* c = (CONSTANT_Utf8_info*)ps.cs->c_pool[index];
        printf("Type Info : %s\n",c->bytes);
    }
    
//    for (int i = 1 ; i < ps.cs->c_pool_count; i++) {
//        if (ps.cs->c_pool[i]->tag == CONSTANT_Long || ps.cs->c_pool[i]->tag == CONSTANT_Double) {
//            i++;
//            continue;
//        }
//        if (ps.cs->c_pool[i]->tag == CONSTANT_Utf8) {
//            CONSTANT_Utf8_info* c = (CONSTANT_Utf8_info*)ps.cs->c_pool[i];
//            printf("STRS : %s\n",c->bytes);
//        }
//
//    }
    
    return 0;
}
