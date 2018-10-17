#include "stack.cpp"

void test1() {
    Stack<int, staticMemory<int>> stack(8, arr);


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