#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// initialize node class storing data and a pointer to the next node
struct node {
    int data;
    struct node *next;
};

// initialize two pointers, head and "current" being NULL
struct node *head = NULL;
struct node *current = NULL;

void printList()
{
    // declare new pointer with head address
    struct node *ptr = head;
    printf("\n[ ");

    // while pointer isn't last (which points to NULL)
    while(ptr != NULL)
    {
        printf("%d, ", ptr->data);
        // set pointer to next node, results in addresses iterations till the end
        ptr = ptr->next;
    }
    printf(" ]");
}

// insert link node at first location
void push_front(int data)
{
    // create a link node
    struct node *link = (struct node*)malloc(sizeof(struct node));

    // assign value to node
    link->data = data;

    // pointer of new node (next) points to old "second" node (starting at NULL)
    link->next = head;

    // head points to this node (which is the first, old was NULL)
    head = link;
}

void pop_front()
{
    struct node *toPop = head;

    head = head->next;

    return toPop;
}

int main()
{
    push_front(1);
    push_front(2);
    printList();
    pop_front();
    printList();
}
