//
//  Parser.cpp
//  JavaDecompiler
//
//  Created by Hades on 22/11/2020.
//

#include "Parser.hpp"
#include "utils.hpp"
#include "Class.hpp"



int Parser::Parse(const char* file){
    uint32_t i_temp;
    std::ifstream rf(file, std::ios::in | std::ios::binary);
    char u4[4];
    char u2[2];
    char u1[1];
    uint16_t tmp;
    uint16_t sz;
    
    if (!rf) {
        return ERROR;
    }
    rf.read(u4, 4);
    i_temp = bytes2int(u4,4);
    
    if (i_temp != MAGIC) {
        return ERROR;
    }
    this->cs->magic = i_temp;
    
    rf.read(u2, 2);
    i_temp = bytes2int(u2,2);
    this->cs->minor_version = i_temp;
    
    rf.read(u2, 2);
    i_temp = bytes2int(u2,2);
    this->cs->major_version = i_temp;
    
    rf.read(u2, 2);
    i_temp = bytes2int(u2,2);
    this->cs->c_pool_count = i_temp;
    this->cs->c_pool = new cp_info[i_temp-1]();
    
    for (int i = 0 ; i < this->cs->c_pool_count - 1; i++) {
        rf.read(u1, 1);
        cp_info* c_pool = &this->cs->c_pool[i];
        switch ((uint8_t)u1[0]) {
            case CONSTANT_Class:
                c_pool->tag = u1[0];
                c_pool->info = new char[SZ_Class_info]();
                rf.read(c_pool->info,SZ_Class_info);
                break;
            case CONSTANT_Fieldref:
                c_pool->tag = u1[0];
                c_pool->info = new char[SZ_Fieldref_info]();
                rf.read(c_pool->info, SZ_Fieldref_info);
                break;
            case CONSTANT_Methodref:
                c_pool->tag = u1[0];
                c_pool->info = new char[SZ_Methodref_info]();
                rf.read(c_pool->info, SZ_Methodref_info);
                break;
            case CONSTANT_InterfaceMethodref:
                c_pool->tag = u1[0];
                c_pool->info = new char[SZ_InterfaceMethodref_info]();
                rf.read(c_pool->info, SZ_InterfaceMethodref_info);
                break;
            case CONSTANT_String:
                c_pool->tag = u1[0];
                c_pool->info = new char[SZ_String_info]();
                rf.read(c_pool->info, SZ_String_info);
                break;
            case CONSTANT_Integer:
                c_pool->tag = u1[0];
                c_pool->info = new char[SZ_Integer_info]();
                rf.read(c_pool->info, SZ_Integer_info);
                break;
            case CONSTANT_Float:
                c_pool->tag = u1[0];
                c_pool->info = new char[SZ_Float_info]();
                rf.read(c_pool->info, SZ_Float_info);
                break;
            case CONSTANT_Long:
                c_pool->tag = u1[0];
                c_pool->info = new char[SZ_Long_info]();
                rf.read(c_pool->info, SZ_Long_info);
                break;
            case CONSTANT_Double:
                c_pool->tag = u1[0];
                c_pool->info = new char[SZ_Double_info]();
                rf.read(c_pool->info, SZ_Double_info);
                break;
            case CONSTANT_NameAndType:
                c_pool->tag = u1[0];
                c_pool->info = new char[SZ_NameAndType_info]();
                rf.read(c_pool->info, SZ_NameAndType_info);
                break;
            case CONSTANT_Utf8:
                // This Structure Need To Handle Differently
                c_pool->tag = u1[0];
                // Read length 
                rf.read(u2,2);
                tmp = bytes2int(u2,2);
                sz = sizeof(uint16_t) + tmp * sizeof(uint8_t);
                tmp = rf.tellg();
                rf.seekg(tmp - 2);
                c_pool->info = new char[sz]();
                rf.read(c_pool->info, sz);
                break;
            case CONSTANT_MethodHandle:
                c_pool->tag = u1[0];
                c_pool->info = new char[SZ_MethodHandle_info]();
                rf.read(c_pool->info, SZ_MethodHandle_info);
                break;
            case CONSTANT_MethodType:
                c_pool->tag = u1[0];
                c_pool->info = new char[SZ_MethodType_info]();
                rf.read(c_pool->info, SZ_MethodType_info);
                break;
            case CONSTANT_Dynamic:
                c_pool->tag = u1[0];
                c_pool->info = new char[SZ_Dynamic_info]();
                rf.read(c_pool->info, SZ_Dynamic_info);
                break;
            case CONSTANT_InvokeDynamic:
                c_pool->tag = u1[0];
                c_pool->info = new char[SZ_InvokeDynamic_info]();
                rf.read(c_pool->info, SZ_InvokeDynamic_info);
                break;
            case CONSTANT_Module:
                c_pool->tag = u1[0];
                c_pool->info = new char[SZ_Module_info]();
                rf.read(c_pool->info, SZ_Module_info);
                break;
            case CONSTANT_Package:
                c_pool->tag = u1[0];
                c_pool->info = new char[SZ_Package_info]();
                rf.read(c_pool->info, SZ_Package_info);
                break;
            default:
                break;
        }
    }
    
    rf.read(u2, 2);
    this->cs->access_flag = bytes2int(u2, 2);
    
    rf.read(u2, 2);
    this->cs->this_class = bytes2int(u2, 2);
    
    rf.read(u2, 2);
    this->cs->super_class = bytes2int(u2, 2);
    
    rf.read(u2, 2);
    this->cs->interface_count = bytes2int(u2, 2);
    
    this->cs->interfaces = new uint16_t[this->cs->interface_count]();
    
    
    for (int i = 0 ; i < this->cs->interface_count ; i++) {
        rf.read(u2, 2);
        this->cs->interfaces[i] = bytes2int(u2, 2);
    }
    
    rf.read(u2, 2);
    this->cs->fields_count = bytes2int(u2, 2);
    
    this->cs->fields = new field_info[this->cs->fields_count]();
    
    field_info* field;
    for (int i = 0; i < this->cs->fields_count; i++) {
        field = &this->cs->fields[i];
        rf.read(u2, 2);
        field->access_flag = bytes2int(u2, 2);
        rf.read(u2, 2);
        field->name_index = bytes2int(u2, 2);
        rf.read(u2, 2);
        field->descriptor_index = bytes2int(u2, 2);
        rf.read(u2, 2);
        field->attributes_count = bytes2int(u2, 2);
        
        field->attributes = new attribute_info[field->attributes_count]();
        
        attribute_info* attribute;
        for (int j = 0; j < field->attributes_count; j++) {
            attribute = &field->attributes[j];
            rf.read(u2, 2);
            attribute->attribute_name_index = bytes2int(u2, 2);
            rf.read(u4, 4);
            attribute->attribute_length = bytes2int(u4, 4);
            
            attribute->info = new uint8_t[attribute->attribute_length]();
            
            for (int k = 0; k < attribute->attribute_length; k++) {
                rf.read(u1, 1);
                attribute->info[k] = (uint8_t)u1[0];
            }
            
        }
        
    }
    
    rf.read(u2, 2);
    this->cs->methods_count = bytes2int(u2, 2);
        
    this->cs->methods = new method_info[this->cs->methods_count]();
    
    method_info* method;
    
    for (int i = 0; i < this->cs->methods_count; i++) {
        method = &this->cs->methods[i];
        rf.read(u2, 2);
        method->access_flags = bytes2int(u2, 2);
        rf.read(u2, 2);
        method->name_index = bytes2int(u2, 2);
        rf.read(u2, 2);
        method->descriptor_index = bytes2int(u2, 2);
        rf.read(u2, 2);
        method->attributes_count = bytes2int(u2, 2);
        
        method->attributes = new attribute_info[method->attributes_count]();
        
        attribute_info* attribute;
        
        
        for (int j = 0; j < method->attributes_count; j++) {
            attribute = &method->attributes[j];
            rf.read(u2, 2);
            attribute->attribute_name_index = bytes2int(u2, 2);
            rf.read(u4, 4);
            attribute->attribute_length = bytes2int(u4, 4);
            
            attribute->info = new uint8_t[attribute->attribute_length]();
            
            for (int k = 0; k < attribute->attribute_length; k++) {
                rf.read(u1, 1);
                attribute->info[k] = (uint8_t)u1[0];
            }
            
        }
        
    }
    
    
    rf.read(u2, 2);
    this->cs->attributes_count = bytes2int(u2, 2);
    this->cs->attribute = new attribute_info[this->cs->attributes_count]();
    
    attribute_info* attribute;
    for (int i = 0; i < this->cs->attributes_count; i++){
        attribute = &this->cs->attribute[i];
        rf.read(u2, 2);
        attribute->attribute_name_index = bytes2int(u2, 2);
        rf.read(u4, 4);
        attribute->attribute_length = bytes2int(u4, 4);
        
        attribute->info = new uint8_t[attribute->attribute_length]();
        
        for (int k = 0; k < attribute->attribute_length; k++) {
            rf.read(u1, 1);
            attribute->info[k] = (uint8_t)u1[0];
        }
    }
    
    
    return SUCCESS;
}
