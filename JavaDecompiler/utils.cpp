//
//  utils.cpp
//  JavaDecompiler
//
//  Created by Hades on 23/11/2020.
//

#include "utils.hpp"


u_int32_t bytes2int(char* buffer,int sz){
    uint32_t res = 0;
    int index = 0;
    for (int i = sz - 1; i >= 0; i--) {
        res |= uint32_t((unsigned char)(buffer[index]) << i * 8);
        index++;
    }
    return res;
}
