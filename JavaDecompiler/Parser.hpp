//
//  Parser.hpp
//  JavaDecompiler
//
//  Created by Hades on 22/11/2020.
//
#pragma once

#ifndef Parser_hpp
#define Parser_hpp

#include "Class.hpp"
#include <fstream>
#include <iostream>

#endif /* Parser_hpp */


class Parser {

public:
    classStructure* cs = new classStructure();
    cp_info* cp_data = new cp_info();
    field_info* f_inf = new field_info();
    method_info* m_inf = new method_info();
    Parser(){};
    int Parse(const char* file);
    CONSTANT_Class_info ParseClassInfo(cp_info cp_inf);
    CONSTANT_Fieldref_info ParseFieldrefInfo(cp_info cp_inf);
    CONSTANT_Methodref_info ParseMethodrefInfo(cp_info cp_inf);
    CONSTANT_InterfaceMethodref_info ParseInterfaceMethodrefInfo(cp_info cp_inf);
    CONSTANT_String_info ParseStringInfo(cp_info cp_inf);
    CONSTANT_Integer_info ParseIntegerInfo(cp_info cp_inf);
    CONSTANT_Float_info ParseFloatInfo(cp_info cp_inf);
    CONSTANT_Long_info ParseLongInfo(cp_info cp_inf);
    CONSTANT_Double_info ParseDoubleInfo(cp_info cp_inf);
    CONSTANT_NameAndType_info ParseNameAndTypeInfo(cp_info cp_inf);
    CONSTANT_Utf8_info ParseUtf8Info(cp_info cp_inf);
    CONSTANT_MethodHandle_info ParseMethodHandleInfo(cp_info cp_inf);
    CONSTANT_MethodType_info ParseMethodTypeInfo(cp_info cp_inf);
    CONSTANT_Dynamic_info ParseDynamicInfo(cp_info cp_inf);
    CONSTANT_InvokeDynamic_info ParseInvokeDynamicInfo(cp_info cp_inf);
    CONSTANT_Module_info ParseModuleInfo(cp_info cp_inf);
    CONSTANT_Package_info ParsePackageInfo(cp_info cp_inf);
    
};
