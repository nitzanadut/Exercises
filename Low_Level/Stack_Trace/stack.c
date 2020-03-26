//gcc -m32 -o stack stack.c -fno-stack-protector

#include <stdio.h>
#include <execinfo.h>
#include <stdlib.h>
#include "asm.h"
#include <unistd.h>
#include <sys/types.h>

void a();
void b();
void c();

int main() {
    a();
    return 0;
}

void a() {
    b();
}

void b() {
    c();
}

void c() {
    printf("0x%px\n", __builtin_return_address(0));
    /*void* callstack[128];
    int i, frames = backtrace(callstack, 128);
    char** strs = backtrace_symbols(callstack, frames);
    for (i = 0; i < frames; ++i) {
        printf("%s\n", strs[i]);
    }
    free(strs);*/
}