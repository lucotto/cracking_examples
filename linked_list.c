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

// print front item
void front()
{
    // print it directly
    printf("Front item is: [%d]\n", head->data);
}

// print back item
void back()
{
    struct node *ptr = head;

    // iterate till SECOND TO LAST node
    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }

    // last item is pointed to by second to last node's pointer
    printf("Back item is: [%d]\n", ptr->data);
}

// return number of items in list
void size()
{
    int count;
    struct node *ptr = head;

    while (ptr != NULL)
    {
        ptr = ptr->next;
        count++;
    }

    printf("There are %d items in the list\n", count);
}

// return true if empty
bool empty()
{
    if (head == NULL) {
        printf("The list is empty\n");
        return true;
    }
    else {
        printf("The list is not empty\n");
        return false;
    }
}

// return item at index
void value_at(int index)
{
    // count starts at -1 so if list is empty -1 is no valid index
    int count = -1;
    struct node *ptr = head;

    // iterates till the node before the wanted index
    if (empty()) // come posso chiamare empty senza il printf?
        printf("There is no item at index [%d] (Empty list)\n", index);
    while (count < index - 1)
    {
        ptr = ptr->next;
        count++;
    }
    if (ptr == NULL)
        printf("There are less than [%d] (index + 1) nodes in this list", index+1);
    else
        printf("The item at index [%d] is [%d]\n", index, ptr->data);


}

int main()
{
    push_front(1);
    push_front(2);
    printList();
    //pop_front();
    //printList();
    //push_back(100);
    //push_front(0);
    //printList();
    //pop_back();
    //printList();
    //front();
    //back();
    //size();
    //empty();
    value_at(2);
}
