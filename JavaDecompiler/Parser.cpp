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
    this->cs->c_pool = new cp_info*[i_temp]();
    
    for (int i = 1 ; i < this->cs->c_pool_count; i++) {
        rf.read(u1, 1);
        switch ((uint8_t)u1[0]) {
            case CONSTANT_Class:
            {
                CONSTANT_Class_info* c_pool = new CONSTANT_Class_info();
                c_pool->tag = (uint8_t)u1[0];
                rf.read(u2,2);
                c_pool->name_index = bytes2int(u2, 2);
                this->cs->c_pool[i] = (cp_info*)c_pool;
                break;
            }
            case CONSTANT_Fieldref:
            {
                CONSTANT_Fieldref_info* c_pool = new CONSTANT_Fieldref_info();
                c_pool->tag = u1[0];
                rf.read(u2, 2);
                c_pool->class_index = bytes2int(u2, 2);
                rf.read(u2, 2);
                c_pool->name_and_type_index = bytes2int(u2, 2);
                this->cs->c_pool[i] = (cp_info*)c_pool;
                break;
            }
            case CONSTANT_Methodref:
            {
                CONSTANT_Methodref_info* c_pool = new CONSTANT_Methodref_info();
                c_pool->tag = u1[0];
                rf.read(u2, 2);
                c_pool->class_index = bytes2int(u2, 2);
                rf.read(u2, 2);
                c_pool->name_and_type_index = bytes2int(u2, 2);
                this->cs->c_pool[i] = (cp_info*)c_pool;
                break;
            }
            case CONSTANT_InterfaceMethodref:
            {
                CONSTANT_InterfaceMethodref_info* c_pool = new CONSTANT_InterfaceMethodref_info();
                c_pool->tag = u1[0];
                rf.read(u2, 2);
                c_pool->class_index = bytes2int(u2, 2);
                rf.read(u2, 2);
                c_pool->name_and_type_index = bytes2int(u2, 2);
                this->cs->c_pool[i] = (cp_info*)c_pool;
                break;
            }
            case CONSTANT_String:
            {
                CONSTANT_String_info* c_pool = new CONSTANT_String_info();
                c_pool->tag = u1[0];
                rf.read(u2, 2);
                c_pool->string_index = bytes2int(u2, 2);
                this->cs->c_pool[i] = (cp_info*)c_pool;
                break;
            }
            case CONSTANT_Integer:
            {
                CONSTANT_Integer_info* c_pool = new CONSTANT_Integer_info();
                c_pool->tag = u1[0];
                rf.read(u4, 4);
                c_pool->bytes = bytes2int(u4, 4);
                this->cs->c_pool[i] = (cp_info*)c_pool;
                break;
            }
            case CONSTANT_Float:
            {
                CONSTANT_Float_info* c_pool = new CONSTANT_Float_info();
                c_pool->tag = u1[0];
                rf.read(u4, 4);
                c_pool->bytes = bytes2int(u4, 4);
                this->cs->c_pool[i] = (cp_info*)c_pool;
                break;
            }
            case CONSTANT_Long:
            {
                CONSTANT_Long_info* c_pool = new CONSTANT_Long_info();
                c_pool->tag = u1[0];
                rf.read(u4, 4);
                c_pool->high_bytes = bytes2int(u4, 4);
                rf.read(u4, 4);
                c_pool->low_bytes = bytes2int(u4, 4);
                this->cs->c_pool[i] = (cp_info*)c_pool;
                i++;
                break;
            }
            case CONSTANT_Double:
            {
                CONSTANT_Double_info* c_pool = new CONSTANT_Double_info();
                c_pool->tag = u1[0];
                rf.read(u4, 4);
                c_pool->high_bytes = bytes2int(u4, 4);
                rf.read(u4, 4);
                c_pool->low_bytes = bytes2int(u4, 4);
                this->cs->c_pool[i] = (cp_info*)c_pool;
                i++;
                break;
            }
            case CONSTANT_NameAndType:
            {
                CONSTANT_NameAndType_info* c_pool = new CONSTANT_NameAndType_info();
                c_pool->tag = u1[0];
                rf.read(u2, 2);
                c_pool->name_index = bytes2int(u2, 2);
                rf.read(u2, 2);
                c_pool->descriptor_index = bytes2int(u2, 2);
                this->cs->c_pool[i] = (cp_info*)c_pool;
                break;
            }
            case CONSTANT_Utf8:
            {

                CONSTANT_Utf8_info* c_pool = new CONSTANT_Utf8_info();
                c_pool->tag = u1[0];
                // Read length 
                rf.read(u2,2);
                c_pool->length  = bytes2int(u2,2);
                c_pool->bytes = new char[c_pool->length]();
                rf.read(c_pool->bytes, c_pool->length);
                this->cs->c_pool[i] = (cp_info*)c_pool;
                break;
            }
            case CONSTANT_MethodHandle:
            {
                CONSTANT_MethodHandle_info* c_pool = new CONSTANT_MethodHandle_info();
                c_pool->tag = u1[0];
                rf.read(u1, 1);
                c_pool->reference_kind = (uint8_t)u1[0];
                rf.read(u2, 2);
                c_pool->reference_index = bytes2int(u2, 2);
                this->cs->c_pool[i] = (cp_info*)c_pool;
                break;
            }
            case CONSTANT_MethodType:
            {
                CONSTANT_MethodType_info* c_pool = new CONSTANT_MethodType_info();
                c_pool->tag = u1[0];
                rf.read(u2, 2);
                c_pool->descriptor_index = bytes2int(u2, 2);
                this->cs->c_pool[i] = (cp_info*)c_pool;
                break;
            }
            case CONSTANT_Dynamic:
            {
                CONSTANT_Dynamic_info* c_pool = new CONSTANT_Dynamic_info();
                c_pool->tag = u1[0];
                rf.read(u2, 2);
                c_pool->bootstrap_method_attr_index = bytes2int(u2, 2);
                rf.read(u2, 2);
                c_pool->name_and_type_index = bytes2int(u2, 2);
                this->cs->c_pool[i] = (cp_info*)c_pool;
                break;
            }
            case CONSTANT_InvokeDynamic:
            {
                CONSTANT_InvokeDynamic_info* c_pool = new CONSTANT_InvokeDynamic_info();
                c_pool->tag = u1[0];
                rf.read(u2, 2);
                c_pool->bootstrap_method_attr_index = bytes2int(u2, 2);
                rf.read(u2, 2);
                c_pool->name_and_type_index = bytes2int(u2, 2);
                this->cs->c_pool[i] = (cp_info*)c_pool;
                break;
            }
            case CONSTANT_Module:
            {
                CONSTANT_Module_info* c_pool = new CONSTANT_Module_info();
                c_pool->tag = u1[0];
                rf.read(u2, 2);
                c_pool->name_index = bytes2int(u2, 2);
                this->cs->c_pool[i] = (cp_info*)c_pool;
                break;
            }
            case CONSTANT_Package:
            {
                CONSTANT_Package_info* c_pool = new CONSTANT_Package_info();
                c_pool->tag = u1[0];
                rf.read(u2, 2);
                c_pool->name_index = bytes2int(u2, 2);
                this->cs->c_pool[i] = (cp_info*)c_pool;
                break;
            }
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
    
    rf.close();
    
    return SUCCESS;
}
