#include <iostream>

#include "secure_header.h"

template <typename T>
class dynamicStack{
public:
    dynamicStack(size_t buffer_size_ = 2) {
        buffer_size = buffer_size_;
        buffer = new T[buffer_size];
    }
    ~dynamicStack(){
        delete[] buffer;
    }
    void push(const T& element){
        if(size >= buffer_size){
            reallocate();
        }
        buffer[size] = element;
        size++;
    }
    T& operator [](size_t addr) const {return buffer[addr];}

private:
    void reallocate(){
       std::cout<<"reallocating"<<std::endl;
       size_t new_buffer_size = buffer_size * 2;
       T* new_buffer = new T[new_buffer_size];
       for(size_t i = 0; i < size; ++i){
           new_buffer[i] = buffer[i];
       }
       delete[] buffer;
       buffer = new_buffer;
       buffer_size = new_buffer_size;
    }

    T* buffer;
    size_t size = 0;
    size_t buffer_size = 0;
};

int main() {
    dynamicStack<int> Stack(4);
    Stack.push(6);
    std::cout<<Stack[1];
    std::cout << "Hello, World!" << std::endl;
    return 0;
}