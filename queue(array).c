#include <stdio.h>
#include <stdbool.h>
#define SIZE 5

int queue[SIZE];
int write = -1;
int del = -1;
int size = -1;

bool empty(){
    if (del == -1)
        return true;
    else return false;
}

bool full(){
    if (size == SIZE)
        return true;
    else return false;
}

void enqueue(int item){
    if (size < SIZE){
        if (size < 0){
            queue[0] = item;
            write = del = 0;
            size = 1;
        }
        else if (write == SIZE - 1){
            queue[0] = item;
            write = 0;
            size++;
        }
        else{
            queue[write+1] = item;
            write++;
            size++;
        }
    }
    else
        printf("Queue is full\n");
}

int dequeue(){
    if (size < 0)
        printf("Queue is empty\n");
    else{
        size--;
        del++;
    }
}

void printQueue(){
    int i;

    printf("Queue: [");
    if(write >= del){
        for(i = del; i <= write; i++)
            printf("%d, ", queue[i]);
    }
    else{
        for(i = del; i < SIZE; i++)
            printf("%d, ",queue[i]);
        for(i = 0; i <= write; i++)
            printf("%d, ",queue[i]);
    }
    printf("]\n");
}

void main(){
    printQueue();
    /*
    enqueue(item)
    dequeue
    empty
    full
    */
}
