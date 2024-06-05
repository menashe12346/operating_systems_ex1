#include <stdio.h>

void function(){
    function(); // calling same function over and over again
}

int main(){
    function();
    return 0;
}