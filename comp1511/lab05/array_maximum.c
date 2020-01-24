// COMP1511 Week 5 Lab: Array Maximum
//
// This program was written by YOUR-NAME-HERE (z5555555)
// on INSERT-DATE-HERE
//
// This program calculates the maximum value in an array of integers.
//

#include <stdio.h>


int array_maximum(int size, int array[size]) {

    int max = 0;
    int x = 0;
    while (x < size) {
        if (array[x] >= max) {
            max = array[x];
        }
        x++;
    }

    return max;
}


#define MAX_SIZE 100

int main(void) {
    int size1 = 7;
    int array1[MAX_SIZE] = {3, 14, 15, 9, 2, 6, 5};

    int result1 = array_maximum(size1, array1);
    printf("The largest value from array1 is: %d\n", result1);

    int size2 = 10;
    int array2[MAX_SIZE] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};

    int result2 = array_maximum(size2, array2);
    printf("The largest value from array2 is: %d\n", result2);

    // Note: you can add more tests here (but they won't be marked).

    return 0;
}



