#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
    int data;
    struct node *next;
};

struct node *head = NULL;
struct node *tail = NULL;

void printQueue(){
    struct node *iter = head;

    printf("Queue: [");
    while (iter != NULL){
        printf("%d, ", iter->data);
        iter = iter->next;
    }
    printf("]\n");
}
bool empty(){
    if (head == NULL)
        return true;
    else return false;
}

void enqueue(int data){
    struct node *newnode = (struct node *)malloc(sizeof(struct node));

    if (empty()){
        newnode->next = NULL;
        head = tail = newnode;
    }
    else {
        newnode->next = NULL;
        tail->next = newnode;
        tail = newnode;
    }
    newnode->data = data;
}

int dequeue(){
    struct node *temp = head;
    int popped;

    if(empty())
        return -1;
    else if (head == tail){
        popped = head->data;
        head = tail = NULL;
        free(temp);
    }
    else{
        head = temp->next;
        free(temp);
    }
    return popped;
}

void main(void){
    printQueue();
    /*
    empty
    enqueue(data)
    dequeue
    */
}
