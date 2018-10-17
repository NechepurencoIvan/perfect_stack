#include <iostream>

#include "secure_header.h"
#include "memory_classes.cpp"
#include "canarey.h"
#include "exceptions.h"
#include "counter.cpp"

int arr[8] = {0, 1, 2, 3, 4, 5, 6, 7};

template<typename T, typename memory>
class Stack {
public:
    Stack(size_t buffer_size_ = 2, T *buffer_ = nullptr) {
        buffer = memory(buffer_size_, buffer_);
        recount_summ();
    }

    ~Stack() {

    }

    void push(const T &element) {
        if (size >= buffer.get_size()) {
            buffer.reallocate();
        }
        buffer[size] = element;
        size++;
        recount_summ();
    }

    T pop() {
        if (size == 0) {
            throw emptyStackTrasactionException("nothing to pop");
        }
        size--;
        T ans = buffer[size];
        buffer.voidValue(size);
        recount_summ();
        return ans;
    }

    size_t get_size() const {
        return size;
    }

    Stack<T, memory> *operator&() {
        std::cout << "https://www.youtube.com/watch?v=K-9S0OMQuBk" << std::endl;
        return nullptr;
    }

    void dump(std::ostream &out = std::cout) const {
        std::cout << std::endl;
        out << "this is logging" << std::endl;
        checkCanary(out, "canary1", canary1, CANARY1);
        buffer.log(out);
        checkCanary(out, "canary2", canary2, CANARY1);
        std::cout << "size= " << size << std::endl;
        checkCanary(out, "canary3", canary3, CANARY1);
        out << "cumsum = " << cumsum << ", correct value is " << count_summ() <<
            "[" << (cumsum == count_summ() ? "OK" : "Fail") << "]" << std::endl;
        checkCanary(out, "canary4", canary4, CANARY1);
    }

private:
    long count_summ() const {
        long sum1 = countSum((char *) &canary1, (char *) &cumsum);
        long sum2 = countSum((char *) &canary4, &end);
        feedValue(sum1, sum2);
    }

    void recount_summ() {
        cumsum = count_summ();
    }

    const unsigned int canary1 = CANARY1;
    memory buffer;
    const unsigned int canary2 = CANARY1;
    size_t size = 0;
    const unsigned int canary3 = CANARY1;
    long cumsum = 0;
    const unsigned int canary4 = CANARY1;
    const char end = 0;
};
