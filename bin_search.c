#include <stdio.h>
#define LEN 10

void main(){

    int binsearch(int array[LEN], int target, int min, int max, int mid);
    int array[LEN], min, max, mid, target, i;

    target = 80;

    for (i = 0; i < LEN; i++){
        array[i] = i*10;
    }
    min = 0;
    max = LEN - 1;
    mid = LEN / 2;

    int res = binsearch(array, target, min, max, mid);
    if (res == -1)
        printf("No such item\n");
    else
        printf("%d target found at index (%d)\n", target, res);
}

int binsearch(int array[LEN], int target, int min, int max, int mid){

    if (min <= max){
        if (target == array[mid])
            return mid;
        else if (target < array[mid])
            binsearch(array, target, min, mid - 1, (max - min) / 2);
        else if (target > array[mid])
            binsearch(array, target, mid + 1, max, (max+min) / 2);
    }
    else
        return -1;
}
