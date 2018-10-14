#include <iostream>

#include "secure_header.h"
#include "memory_classes.cpp"
#include "canarey.h"
#include "exceptions.h"
#include "counter.cpp"

int arr[8] = {0, 1, 2, 3, 4, 5, 6, 7};

template <typename T, typename memory>
class Stack{
public:
    Stack(size_t buffer_size_ = 2, T* buffer_ = nullptr) {
        buffer = memory(buffer_size_, buffer_);
        recount_summ();
    }

    ~Stack(){
    }

    void push(const T& element){
        try {
            if (size >= buffer.get_size()) {
                buffer.reallocate();
            }
        }
        catch (outOfMemoryException) {
            std::cout<<"ti loh";
        }
        buffer[size] = element;
        size++;
        recount_summ();
    }

    T& operator [](size_t addr) const {
        return buffer[addr];
    }

    T pop() {
        size--;
        recount_summ();
        T ans = buffer[size];
        buffer.voidValue(size);
        return ans;
    }

    size_t get_size(){
        return size;
    }

    void dump(std::ostream &out = std::cout) const {
        std::cout<<std::endl;
        out<<"this is logging" << std::endl;
        out<<"canary1 = " << canary1 << ", correct value is " << CANARY1 <<
           "[" << (canary1 == CANARY1 ? "OK"  : "Fail") << "]" <<std::endl;
        buffer.log(out);
        out<<"canary2 = " << canary2 << ", correct value is " << CANARY1 <<
           "[" << (canary2 == CANARY1 ? "OK"  : "Fail") << "]" <<std::endl;
        std::cout<<"size= "<<size<<std::endl;
        out<<"canary3 = " << canary3 << ", correct value is " << CANARY1 <<
           "[" << (canary3 == CANARY1 ? "OK"  : "Fail") << "]" <<std::endl;
        out<<"cumsum = "  << cumsum  << ", correct value is " << count_summ() <<
           "[" << (cumsum == count_summ() ? "OK"  : "Fail") << "]" <<std::endl;
        out<<"canary4 = " << canary4 << ", correct value is " << CANARY1 <<
           "[" << (canary4 == CANARY1 ? "OK"  : "Fail") << "]" <<std::endl;
    }
private:
    long count_summ() const {
        long sum1 = countSum((char*)&canary1, (char*)&cumsum);
        long sum2 = countSum((char*)&canary4, &end);
        feedValue(sum1, sum2);
    }
    void recount_summ (){
        cumsum=count_summ();
    }
    const unsigned int canary1 = CANARY1;
    memory buffer;
    const unsigned int canary2 = CANARY1;
    size_t size = 0;
    const unsigned int canary3 = CANARY1;
    long cumsum = 0;
    const unsigned int canary4 = CANARY1;
    const char end=0;
};
