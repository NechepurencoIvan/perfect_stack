#pragma once

#define CANARY1 0xDEADBEEF
#define CANARY2 0xDED32DED

void checkCanary(std::ostream &out, char* var_name, unsigned int real_val, unsigned int right_val){
    out<<var_name<<" = " << real_val << ", correct value is " << right_val <<
       "[" << (real_val == right_val ? "OK"  : "Fail") << "]" <<std::endl;
}