#pragma once

#include <iostream>
#include "exceptions.h"
#include "secure_header.h"

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
        std::cout<<"reallocating"<<std::endl;
        size_t new_buffer_size = buffer_size * 2;
        T* new_buffer = new T[new_buffer_size];
        for(size_t i = 0; i < buffer_size; ++i){ //stupid spending of time
            new_buffer[i] = buffer[i];
        }
        delete[] buffer;
        buffer = new_buffer;
        buffer_size = new_buffer_size;
    }

    T& operator [](size_t addr) const {
        return buffer[addr];
    }

    size_t get_size() const {
        return buffer_size;
    }

    void log(std::ostream &out) const {
        out<<"I am dinamic memory))"<<std::endl;
    }

    void voidValue(size_t addr){
        voidVal<T>(buffer + addr);
    }
private:
    T* buffer = nullptr;
    size_t buffer_size;
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
        return buffer[addr];
    }

    size_t get_size() const {
        return buffer_size;
    }

    void log(std::ostream &out) const {
        out<<"I am static memory))"<<std::endl;
        T* explorer = buffer;
        for(size_t i = 0; i < buffer_size; ++i){
            out<<"buffer_["<<i<<"] = "<<buffer[i]/*&explorer*/<<std::endl;
            explorer++;
        }
    }

    void voidValue(size_t addr){
        voidVal<T>(buffer + addr);
    }
private:
    T* buffer = nullptr;
    size_t buffer_size;
};

