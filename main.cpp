#include <iostream>

#include "secure_header.h"

int arr[8] = {0, 1, 2, 3, 4, 5, 6, 7};

template <typename T>
class dynamicMemory{
public:
    dynamicMemory(size_t size = 4, T* buffer_ = nullptr){
        buffer_size = size;
        if(buffer_ == nullptr) {
            buffer = new T[buffer_size];
        }
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

    size_t get_size(){
        return buffer_size;
    }
private:
    T* buffer = nullptr;
    size_t buffer_size;
};

template <typename T>
class staticMemory{
public:
    staticMemory(size_t size = 0, T* buffer_ = nullptr){
        buffer_size = size;
        buffer = buffer_;
    }

    ~staticMemory(){
    }

    void reallocate(){
        size_t a = 1;
        size_t b = a*a;
        a /= (a - b);
    }

    T& operator [](size_t addr) const {
        return buffer[addr];
    }

    size_t get_size(){
        return buffer_size;
    }
private:
    T* buffer = nullptr;
    size_t buffer_size;
};

template <typename T, typename memory>
class dynamicStack{
public:
    dynamicStack(size_t buffer_size_ = 2, T* buffer_ = nullptr) {
        buffer = memory(buffer_size_, buffer_);
    }
    ~dynamicStack(){
        //delete[] buffer;
    }
    void push(const T& element){
        if(size >= buffer.get_size()){
            buffer.reallocate();
        }
        buffer[size] = element;
        size++;
    }

    T& operator [](size_t addr) const {
        return buffer[addr];
    }

    T& pop() {
        size--;
        return buffer[size];
    }

    size_t get_size(){
        return size;
    }
private:
    memory buffer;
    size_t size = 0;
};

void test1(){
    dynamicStack<int, staticMemory<int>> Stack(8, arr);
    Stack.push(6);
    std::cout<<Stack[0]<<" "<< Stack.pop()<<std::endl;
    Stack.push(6);
    Stack.push(7);
    Stack.push(8);
    Stack.push(9);
    for(size_t i = 0; i < 5; ++i){
        std::cout<<Stack.pop()<<std::endl;
    }
}

int main() {
    test1();
    return 0;
}