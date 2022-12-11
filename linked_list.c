#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// initialize node class storing data and a pointer to the next node
struct node {
    int data;
    struct node *next;
};

// initialize head pointer
struct node *head = NULL;

// print list
void printList()
{
    // declare new pointer with head address
    struct node *ptr = head;
    printf("Linked list = [ ");

    // while pointer isn't last (which points to NULL)
    while(ptr != NULL)
    {
        printf("%d, ", ptr->data);
        // set pointer to next node, results in addresses iterations till the end
        ptr = ptr->next;
    }
    printf(" ]\n");
}

// return true if empty
//--------------> if f viene lanciata da sola (oppure copia funzione per fare il lavoro a parte)
bool empty()
{
    if (head == NULL) {
        // printf("The list is empty\n");
        return true;
    }
    else {
        // printf("The list is not empty\n");
        return false;
    }
}

// return number of items in list
int size()
{
    int count = 0;
    struct node *ptr = head;

    while (ptr != NULL)
    {
        ptr = ptr->next;
        count++;
    }

    return count;
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

    printf("Successfully added new node at front with [%d] value\n", data);
}

int pop_front()
{
    // reference to first link
    struct node *temp = head;

    // store value to return it
    int popped_value = head->data;

    // mark next of first link (second link) as the new first
    head = head->next;

    // free allocated memory
    free(temp);

    // return deleted value
    printf("Successfully removed front node with [%d] value\n", popped_value);
    return popped_value;
}


// add element to end of linked list
void push_back(struct node **ptr, int data)
{
    // allocate memory for newnode
    struct node *newnode = (struct node*)malloc(sizeof(struct node)),
    // declare temp pointer to iterate
                *iter = *ptr;

    if (empty())
        push_front(data);
    else
    {
        // set newnode's data/pointer
        newnode->data = data;
        newnode->next = NULL;

        // iterate to old last node
        while (iter->next != NULL)
            iter = iter->next;
        // point old last to new node
        iter->next = newnode;
    }
}

// remove last element of linked list
int pop_back(struct node **ptr)
{
    // declare temp pointer to iterate
    struct node *iter = *ptr;

    if (size() == 1)
        pop_front();
    else
    {
        // iterate till SECOND TO LAST node
        while (iter->next->next != NULL)
            iter = iter->next;
        iter->next = NULL;
        int popped_item = iter->data;
        free(iter);
        printf("Successfully removed node at back with [%d] value\n", popped_item);
        return popped_item;
    }
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

// return item at index
int value_at(int index)
{
    // count starts at -1 so if list is empty -1 is no valid index
    int count = 1;
    struct node *iter = head;

    // if index is negative raise error
    if (index < 0)
        printf("Index has to be >= 0 to be valid");
    // iterates till the node before the wanted index
    else if (empty())
        printf("There is no item at index [%d] (Empty list)\n", index);
    else
    {
        // iterate till index
        while (count <= index)
        {
            iter = iter->next;
            count++;
        }
        // if iteration came to the end of list
        if (iter == NULL)
            printf("There are less than [%d] (index + 1) nodes in this list\n", index+1);
        // else print the data at given index
        else
        {
            printf("The item at index [%d] is [%d]\n", index, iter->data);
            return iter->data;
        }
    }
}

// insert item at given index
int insert(struct node **ptr, int index, int data)
{
    struct node *newnode = (struct node*)malloc(sizeof(struct node)),
                *iter = *ptr;
    int count = 1;

    // if index is negative raise error
    if (index < 0)
    {
        printf("Index has to be >= 0 to be valid");
        return -1;
    }
    // if index i 0 push front
    else if (index == 0)
    {
        push_front(data);
        return 0;
    }
    // if index is greater than size push back
    else if (index >= size())
    {
        push_back(&head, data);
        return 0;
    }
    // for every other index iterate till that point and insert
    while (count < index)
    {
        iter = iter->next;
        count++;
    }

    newnode->data = data;
    newnode->next = iter->next;
    iter->next = newnode;
}

// pop node at given index
int pop_index(struct node **ptr, int index)
{
    struct node *iter = *ptr;
    int count = 1;

    // negative index error
    if (index < 0)
    {
        printf("Index has to be >= 0 to be valid");
        return -1;
    }
    // index 0 pop front
    else if (index == 0)
    {
        pop_front();
        return 0;
    }
    // index "last" pop back
    else if (index >= (size()-1))
    {
        pop_back(&head);
        return index;
    }
    // every other index iterate and pop
    while (count < index)
    {
        iter = iter->next;
        count++;
    }

    iter->next = iter->next->next;
    printf("Successfully removed node at index %d\n", index);
}

// pop node by value
void pop_value(struct node **ptr, int data)
{
    struct node *iter = *ptr;
    int index = 0;

    // if first node has data pop front
    if (iter->data == data)
        pop_front();
    // else iterate till you find it, error if you come to end
    else
    {
        for(;;)
        {
            if (iter == NULL)
            {
                printf("There is no such value in this list\n");
                break;
            }
            else if (iter->data == data)
            {
                pop_index(&head, index);
                break;
            }
            iter = iter->next;
            index++;
        }
    }
}

// return value of node at position n starting from end
int value_n_from_end(int n)
{
    int size_amount = size();

    if (n < 0)
        return -1;
    else if (n > size_amount-1)
        return -1;
    else
        value_at(size_amount - 1 - n);
}

// reverse
int reverse()
{
    struct node *iter = head;

    if (empty())
        return 0;
    else if (size() == 1)
        return 0;
    else
    {
        int values[size()-1];
        for (int i = 0; i < size() - 1; i++)
        {
            if (i <= (size()-1) / 2)
            {
                values[i] = value_at(size() - 1 - i);
                values[size()-1-i] = iter->data;
            }
            iter->data = values[i];
            iter = iter->next;
        }
        iter->data = values[size()-1];
        return 0;
    }
}

int main()
{
    printList();
    /*
    size
    empty
    value_at
    push_front
    pop_front
    push_back
    pop_back
    front
    back
    insert
    pop_index
    pop_value
    value_n_from_end
    reverse
    */
}
