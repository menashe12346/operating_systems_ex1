#include <stdio.h>

int function(){
    int* p = (int *)0xdeadbeef;
    *p = 10;
    return *p;
}

int main(){
    int num = function();
    return 0;
}