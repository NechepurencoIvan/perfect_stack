#pragma once

#include <iostream>
#include "exceptions.h"
#include "canarey.h"
#include "secure_header.h"
#include "counter.cpp"

template <typename T>
void clear_memory(T* buffer, size_t buffersize){
    char* end = (char*)(buffer + buffersize);
    char* explorer = (char*)buffer;
    if(explorer == nullptr){
        std::cout<<"A"<<std::endl;
    }
    for(char* explorer = (char*)buffer; explorer < end; explorer++){
        *explorer = 0xDEADBEEF;
    }
}

template <typename T>
class memory{
public:
    void reallocate();
    T& operator [](size_t addr) const;
    size_t get_size() const;
    void log(std::ostream &out) const;
    void voidValue(size_t addr);
private:
};

//соре за копипасту двух реализаций
template <typename T>
class dynamicMemory: public memory<T> {
public:
    dynamicMemory(size_t size = 4, T* buffer_ = nullptr){
        buffer_size = size;
        if(buffer_ == nullptr) {
            buffer = new T[buffer_size];
        }
        clear_memory(buffer, buffer_size);
    }

    ~dynamicMemory(){
        delete[] buffer;
    }

    void reallocate(){
        size_t new_buffer_size = buffer_size * 2;
        T* new_buffer = new T[new_buffer_size];
        clear_memory(new_buffer, new_buffer_size);
        for(size_t i = 0; i < buffer_size; ++i){ //stupid spending of time
            new_buffer[i] = buffer[i];
        }
        delete[] buffer;
        buffer = new_buffer;
        buffer_size = new_buffer_size;
    }

    T& operator [](size_t addr) const {
        if(addr >= buffer_size || addr < 0){
            throw outOfMemoryException("incorrect index on memory transaction, this was not supposed to happen");
        }
        return buffer[addr];
    }

    size_t get_size() const {
        return buffer_size;
    }

    void log(std::ostream &out) const {
        out<<"      I am dinamic memory))"<<std::endl;
        checkCanary(out << "      ", "bcanary1", bcanary1, CANARY2);
        for(size_t i = 0; i < buffer_size; ++i){
            out<<"      buffer_["<<i<<"] = "<<buffer[i]<<std::endl;
        }
        checkCanary(out << "      ", "bcanary2", bcanary2, CANARY2);
        std::cout<<"      buffer_size = "<< buffer_size << std::endl;
        checkCanary(out << "      ", "bcanary3", bcanary3, CANARY2);
    }

    void voidValue(size_t addr){
        voidVal<T>(buffer + addr);
    }

    long controlSum() const {
        return countSum((char*) &bcanary1, (char*) &end);
    }

    bool validate(size_t size) const {
        if(bcanary1 != CANARY2 || bcanary2 != CANARY2 || bcanary3 != CANARY2){
            return false;
        }
        bool flag = true;
        T* voidValue = new T;
        voidVal(voidValue);
        for(size_t i = size; i < buffer_size; ++i){
            if (buffer[i] != *voidValue) {
                flag = false;
                break;
            }
        }
        delete voidValue;
        return flag;
    }
private:
    unsigned bcanary1 = CANARY2;
    T* buffer = nullptr;
    unsigned bcanary2 = CANARY2;
    size_t buffer_size;
    unsigned bcanary3 = CANARY2;
    char end;
};

template <typename T>
class staticMemory: public memory<T> {
public:
    staticMemory(size_t size = 0, T* buffer_ = nullptr){
        buffer_size = size;
        buffer = buffer_;
        if(buffer_ != nullptr) {
            clear_memory(buffer, buffer_size);
        }
    }

    ~staticMemory(){
    }

    void reallocate(){
        throw outOfMemoryException("static memory overflow");
    }

    T& operator [](size_t addr) const {
        if(addr >= buffer_size || addr < 0){
            throw outOfMemoryException("incorrect index on memory transaction, this was not supposed to happen");
        }
        return buffer[addr];
    }

    size_t get_size() const {

        return buffer_size;
    }

    void log(std::ostream &out) const {
        out<<"      I am static memory))"<<std::endl;
        checkCanary(out << "      ", "bcanary1", bcanary1, CANARY2);
        for(size_t i = 0; i < buffer_size; ++i){
            out<<"      buffer_["<<i<<"] = "<<buffer[i]<<std::endl;
        }
        checkCanary(out << "      ", "bcanary2", bcanary2, CANARY2);
        std::cout<<"      buffer_size = "<< buffer_size << std::endl;
        checkCanary(out << "      ", "bcanary3", bcanary3, CANARY2);
    }

    void voidValue(size_t addr){
        if(addr >= buffer_size || addr < 0){
            throw outOfMemoryException("incorrect index on memory transaction, this was not supposed to happen");
        }
        voidVal<T>(buffer + addr);
    }

    long controlSum() const {
        return countSum((char*) &bcanary1, (char*) &end);
    }

    bool validate(size_t size) const {
        if(bcanary1 != CANARY2 || bcanary2 != CANARY2 || bcanary3 != CANARY2){
            return false;
        }
        bool flag = true;
        T* voidValue = new T;
        voidVal(voidValue);
        for(size_t i = size; i < buffer_size; ++i){
            if (buffer[i] != *voidValue) {
                flag = false;
                break;
            }
        }
        delete voidValue;
        return flag;
    }
private:
    unsigned bcanary1 = CANARY2;
    T* buffer = nullptr;
    unsigned bcanary2 = CANARY2;
    size_t buffer_size;
    unsigned bcanary3 = CANARY2;
    char end;
};
