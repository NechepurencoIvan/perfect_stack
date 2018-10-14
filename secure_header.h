#pragma once
//#define BADSYMBOL =

#define VOIDSYMBOL 0xDEADBEEF

template <typename T>
void voidVal(T* voidvalue) {
    T* ending = voidvalue + 1;
    for(char* explorer = (char*)voidvalue; explorer < (char*)ending; explorer++){
        *explorer = VOIDSYMBOL;
    }
}