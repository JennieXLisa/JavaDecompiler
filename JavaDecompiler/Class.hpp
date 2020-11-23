//
//  Class.hpp
//  JavaDecompiler
//
//  Created by Hades on 22/11/2020.
//
#pragma once

#ifndef Class_hpp
#define Class_hpp

#include <stdint.h>

#endif /* Class_hpp */

// Java Magic

#define MAGIC 0xCAFEBABE

//ACCESS Flags Constants

#define ACC_PUBLIC 0x0001
#define ACC_FINAL 0X0010
#define ACC_SUPER 0x0020
#define ACC_INTERFACE 0x0200
#define ACC_ABSTRACT 0x0400
#define ACC_SYNTHETIC 0x1000
#define ACC_ANNOTATION 0x2000
#define ACC_ENUM 0x4000
#define ACC_MODULE 0x8000


// Constant Pool Tag

#define CONSTANT_Class 7
#define CONSTANT_Fieldref 9
#define CONSTANT_Methodref 10
#define CONSTANT_InterfaceMethodref 11
#define CONSTANT_String 8
#define CONSTANT_Integer 3
#define CONSTANT_Float 4
#define CONSTANT_Long 5
#define CONSTANT_Double 6
#define CONSTANT_NameAndType 12
#define CONSTANT_Utf8 1
#define CONSTANT_MethodHandle 15
#define CONSTANT_MethodType 16
#define CONSTANT_Dynamic 17
#define CONSTANT_InvokeDynamic 18
#define CONSTANT_Module 19
#define CONSTANT_Package 20


// Field Access Flag

#define FACC_PUBLIC 0x0001
#define FACC_PRIVATE 0x0002
#define FACC_PROTECTED 0x0004
#define FACC_STATIC 0x0008
#define FACC_FINAL 0x0010
#define FACC_VOLATILE 0x0040
#define FACC_TRANSIENT 0x0080
#define FACC_SYNTHETIC 0x1000
#define FACC_ENUM 0x4000

// Method Access Flag

#define MACC_PUBLIC 0x0001
#define MACC_PRIVATE 0x0002
#define MACC_PROTECTED 0x0004
#define MACC_STATIC 0x0008
#define MACC_FINAL 0x0010
#define MACC_SYNCHRONIZED 0x0020
#define MACC_BRIDGE 0x0040
#define MACC_VARARGS 0x0080
#define MACC_NATIVE 0x0100
#define MACC_ABSTRACT 0x0400
#define MACC_STRICT 0x0800
#define MACC_SYNTHETIC 0x1000

// Error Code

#define ERROR 0xFFFFFFFF
#define SUCCESS 0x00000000

// Struct Size

#define SZ_Class_info 2
#define SZ_Fieldref_info 4
#define SZ_Methodref_info 4
#define SZ_InterfaceMethodref_info 4
#define SZ_String_info 2
#define SZ_Integer_info 4
#define SZ_Float_info 4
#define SZ_Long_info 8
#define SZ_Double_info 8
#define SZ_NameAndType_info 4
#define SZ_MethodHandle_info 3
#define SZ_MethodType_info 2
#define SZ_Dynamic_info 4
#define SZ_InvokeDynamic_info 4
#define SZ_Module_info 2
#define SZ_Package_info 2



class cp_info {
public:
    uint8_t tag;
    char* info;
    cp_info(){}
};

class attribute_info {
public:
    uint16_t attribute_name_index;
    uint32_t attribute_length;
    uint8_t* info;
    attribute_info(){}
};

class field_info {
public:
    uint16_t access_flag;
    uint16_t name_index;
    uint16_t descriptor_index;
    uint16_t attributes_count;
    attribute_info* attributes;
    field_info(){}
};

class method_info {
public:
    uint16_t access_flags;
    uint16_t name_index;
    uint16_t descriptor_index;
    uint16_t attributes_count;
    attribute_info* attributes;
    method_info(){}
};


class classStructure{
public:
    uint32_t magic;
    uint16_t minor_version;
    uint16_t major_version;
    uint16_t c_pool_count;
    cp_info* c_pool;
    uint16_t access_flag;
    uint16_t this_class;
    uint16_t super_class;
    uint16_t interface_count;
    uint16_t* interfaces;
    uint16_t fields_count;
    field_info* fields;
    uint16_t methods_count;
    method_info* methods;
    uint16_t attributes_count;
    attribute_info* attribute;
    classStructure(){}
};


struct CONSTANT_Class_info{
    uint8_t tag;
    uint16_t name_index;
};

struct CONSTANT_Fieldref_info {
    uint8_t tag;
    uint16_t class_index;
    uint16_t name_and_type_index;
};

struct CONSTANT_Methodref_info {
    uint8_t tag;
    uint16_t class_index;
    uint16_t name_and_type_index;
};

struct CONSTANT_InterfaceMethodref_info {
    uint8_t tag;
    uint16_t class_index;
    uint16_t name_and_type_index;
};

struct CONSTANT_String_info {
    uint8_t tag;
    uint16_t string_index;
};

struct CONSTANT_Integer_info {
    uint8_t tag;
    uint32_t bytes;
};

struct CONSTANT_Float_info {
    uint8_t tag;
    uint32_t bytes;
};

struct CONSTANT_Long_info{
    uint8_t tag;
    uint32_t high_bytes;
    uint32_t low_bytes;
};

struct CONSTANT_Double_info {
    uint8_t tag;
    uint32_t high_bytes;
    uint32_t low_bytes;
};

struct CONSTANT_NameAndType_info {
    uint8_t tag;
    uint16_t name_index;
    uint16_t descriptor_index;
};

struct CONSTANT_Utf8_info{
    uint8_t tag;
    uint16_t length;
    uint8_t* bytes;
};

struct CONSTANT_MethodHandle_info {
    uint8_t tag;
    uint8_t reference_kind;
    uint16_t reference_index;
};

struct CONSTANT_MethodType_info {
    uint8_t tag;
    uint16_t descriptor_index;
};

struct CONSTANT_Dynamic_info {
    uint8_t tag;
    uint16_t bootstrap_method_attr_index;
    uint16_t name_and_type_index;
};

struct CONSTANT_InvokeDynamic_info {
    uint8_t tag;
    uint16_t bootstrap_method_attr_index;
    uint16_t name_and_type_index;
};

struct CONSTANT_Module_info {
    uint8_t tag;
    uint16_t name_index;
};

struct CONSTANT_Package_info {
    uint8_t tag;
    uint16_t name_index;
};
