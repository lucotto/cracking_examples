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

// insert new node at first location
void push_front(int data)
{
    // create a new node
    struct node *newnode = (struct node*)malloc(sizeof(struct node));

    // assign value to node
    newnode->data = data;

    // pointer of new node (next) points to old "second" node (starting at NULL)
    newnode->next = head;

    // head points to this node (which is the first, old was NULL)
    head = newnode;
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


// add element to end of linked list
void push_back(struct node **ptr, int data)
{
    // allocate memory for newnode
    struct node *newnode = (struct node*)malloc(sizeof(struct node)),
    // declare temp pointer to iterate
                *iter = *ptr;

    // set newnode's data/pointer
    newnode->data = data;
    newnode->next = NULL;

    // iterate to old last node
    while (iter->next != NULL)
        iter = iter->next;
    // point old last to new node
    iter->next = newnode;
}

// remove last element of linked list
void pop_back(struct node **ptr)
{
    // declare temp pointer to iterate
    struct node *iter = *ptr;

    // iterate till SECOND TO LAST node
    while (iter->next->next != NULL)
        iter = iter->next;
    iter->next = NULL;
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
    struct node *iter = head;

    // iterate till last node
    while (iter->next != NULL)
    {
        iter = iter->next;
    }

    // last item is pointed to by second to last node's pointer
    printf("Back item is: [%d]\n", iter->data);
}

// return number of items in list
int size()
{
    int count;
    struct node *ptr = head;

    while (ptr != NULL)
    {
        ptr = ptr->next;
        count++;
    }

    printf("There are %d items in the list\n", count);
    return count;
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
    // if index is negative raise error
    if (index < 0)
    {
        printf("Index has to be >= 0 to be valid");
        return -1;
    }
    // count starts at -1 so if list is empty -1 is no valid index
    int count = -1;
    struct node *iter = head;

    // iterates till the node before the wanted index
    if (empty()) // come posso chiamare empty senza il printf?
        printf("There is no item at index [%d] (Empty list)\n", index);
    while (count <= index - 1)
    {
        iter = iter->next;
        count++;
    }
    // if iteration came to the end of list
    if (iter == NULL)
        printf("There are less than [%d] (index + 1) nodes in this list\n", index+1);
    // else print the data at given index
    else
        printf("The item at index [%d] is [%d]\n", index, iter->data);
}

int insert(struct node **ptr, int index, int data)
{
    if (index < 0)
    {
        printf("Index has to be >= 0 to be valid");
        return -1;
    }
    else if (index == 0)
    {
        push_front(data);
        return 0;
    }
    else if (index >= size())
    {
        push_back(&head, data);
        return index;
    }

    struct node *newnode = (struct node*)malloc(sizeof(struct node)),
                *iter = *ptr;
    int count = 1;

    while (count < index)
    {
        iter = iter->next;
        count++;
    }

    newnode->data = data;
    newnode->next = iter->next;
    iter->next = newnode;
}

int pop_index(struct node **ptr, int index)
{
    if (index < 0)
    {
        printf("Index has to be >= 0 to be valid");
        return -1;
    }
    else if (index == 0)
    {
        pop_front();
        return 0;
    }
    else if (index >= (size()-1))
    {
        pop_back(&head);
        return index;
    }

    struct node *iter = *ptr;
    int count = 1;

    while (count < index)
    {
        iter = iter->next;
        count++;
    }

    iter->next = iter->next->next;
}

void remove_value(struct node **ptr, int data)
{
    struct node *iter = *ptr;
    int index = 0;

    if (iter->data == data)
    {
        pop_front();
        printf("Successfully removed first node carrying [%d] value\n", data);
        return 0;
    }

    while (iter->data != data)
    {
        iter = iter->next;
        index++;
        if (iter == NULL)
            break; // non posso uscire direttamente dalla funzione qui?
    }
    if (iter == NULL)
    {
        printf("There's no node with [%d] value\n", data);
        return 0;
    }

    pop_index(&head, index);
    printf("Successfully removed first node carrying [%d] value\n", data);

}

int main()
{
    push_front(1);
    push_front(2);
    //printList();
    //pop_front();
    //printList();
    push_back(&head, 100);
    //push_front(0);
    //printList();
    //pop_back(&head);
    //printList();
    //front();
    //back();
    //size();
    //empty();
    //value_at(0);
    insert(&head, 3, 5000);
    //printList();
    //pop_index(&head, 4);
    remove_value(&head, 2);
    printList();
}
