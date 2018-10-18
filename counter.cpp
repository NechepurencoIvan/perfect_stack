#pragma once

long feedValue(long sum, long val) {
    return sum + val;
}

long countSum(const char* begin, const char* end) {
    long sum = 0;
    for(const char* counter = begin; counter < end; ++counter) {
        sum = feedValue(sum, *counter);
    }
    return sum;
}

