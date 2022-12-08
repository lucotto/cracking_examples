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
    printf(" ]\n");
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

void pop_front()    // devo liberare la memoria del nodo che poppo?
{
    // reference to first link
    struct node *temp = head;

    // mark next of first link (second link) as the new first
    head = head->next;

    // return deleted link
    return temp;
}

// non funziona, forse servono puntatori doppi?
void push_back(int data)
{
    // declare new pointer with head address
    struct node *ptr = head;
    // allocate memory for new node
    struct node *link = (struct node*)malloc(sizeof(struct node));

    // iterate till last node's pointer
    while (ptr != NULL)
    {
        printf("%d - %d\n", ptr, ptr->data);
        ptr = ptr->next;
    }

    // set new node's data to input
    link->data = data;
    // set new node's pointer to NULL
    link->next = ptr;
    // set old last pointer to new last node
    ptr = link;
}

// non funziona DIO PORCO
void pop_back()
{
    struct node *ptr = head;

    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }

    ptr = ptr->next;

    printf("Successfully removed last node");

}

int main()
{
    push_front(1);
    push_front(2);
    printList();
    //pop_front();
    //printList();
    //push_back(100);
    push_front(0);
    printList();
    pop_back();
    printList();
}
