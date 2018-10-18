#include "stack.cpp"

void test1() {
    Stack<int, dynamicMemory<int>> stack(2);
    /*Stack<int, staticMemory<int>> stack(8, arr);*/
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.pop();
    stack.pop();
    stack.dump();
}

int main() {
    try {
        test1();
    } catch (outOfMemoryException ex) {
        std::cout << ex.description << std::endl;
    } catch (emptyStackTrasactionException ex) {
        std::cout << ex.description << std::endl;
    }
    return 0;
}