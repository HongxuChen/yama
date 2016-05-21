// RUN: %cc %s -emit-llvm -std=c99 -c -o %t1
// RUN: %opt -instnamer -mem2reg -break-crit-edges %t1 -o %t2
// RUN: %yopt -vssa %t1 -o %t2

#include<stdio.h>

int foo() {
    int k = 0;
    while (k < 100) {
        int i = 0;
        int j = k;
        while (i < j) {
            i = i + 1;
            j = j - 1;
        }
        k = k + 1;
    }
    return k;
}

int main(int argc, char **argv) { printf("%d\n", foo()); }
