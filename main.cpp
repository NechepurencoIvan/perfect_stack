#include "stack.cpp"

void test1(){
    Stack<int, staticMemory<int>> stack(8, arr);
    stack.dump();
    stack.push(6);
    stack.dump();
    stack.push(7);
    stack.push(8);
    stack.push(9);
    std::cout<<stack.pop()<<std::endl;
    std::cout<<stack.pop()<<std::endl;
    std::cout<<stack.pop()<<std::endl;
    std::cout<<stack.pop()<<std::endl;
    //stack.pop();
    stack.dump();
}

int main() {
    test1();
    return 0;
}