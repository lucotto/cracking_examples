// https://alexandra-zaharia.github.io/posts/implementing-a-vector-in-c/
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    void **data;        // information in the vector
    size_t count;       // number of currently stored elements in the vector
    size_t capacity;    // capacity of the vector
} Vector;

const size_t VECTOR_INIT_CAPACITY = 16;

Vector *vector_create()
{
    Vector *vector = (Vector *)malloc(sizeof(Vector));  // allocate memory for vector
    if (!vector) return NULL;                           // null if fails

    vector->count = 0;                          // refers to member "count" from the struct "vector" points to
    vector->capacity = VECTOR_INIT_CAPACITY;    // same with capacity

    vector->data = (void *)malloc(vector->capacity * sizeof(void *));   // allocate memory for data array
    if (!vector->data)
    {
        vector_free(vector);        // free vector and return NULL if fails
        return NULL;
    }

    return vector;      // return pointer to the new vector
}

void vector_free(Vector *vector)
{
    if (vector)                 // if vector is not NULL
    {
        if (vector->data)       // if data underlying vector is not NULL
            free(vector->data); // free data
        free(vector);           // free vector itself
    }
}

static int resize(Vector *vector, size_t capacity)
{
    void **data = realloc(vector->data, capacity * sizeof(void *));
    vector->capacity = capacity;

    if (!data) return -1;
    if (data != vector->data)
        vector->data = data;
    data = NULL;

    return 0;
}

int push(Vector *vector, void *item)
{
    if (!vector || !vector->data) return -1;

    if (vector->count == vector->capacity)
    {
        if (resize(vector, 2 * vector->capacity) == -1)
            return -1;
    }

    vector->data[vector->count++] = item;
    printf("Successfully added item: [%d]\n", item);
    return 0;
}

int insert(Vector *vector, void *item, int index)
{
    if (!vector || !vector->data) return -1;
    if (index < 0 || index > vector->count) return -1;

    if (index == vector->count) {
        if (push(vector, item) == -1) return -1;
    } else {
        if (vector->count == vector->capacity) {
            if (resize(vector, 2 * vector->capacity) == -1)
                return -1;
        }

        for (int i = vector->count; i > index; i--)
            vector->data[i] = vector->data[i-1];

        vector->data[index] = item;
        vector->count++;
        printf("Successfully added item [%d] at index %d\n", item, index);
      }

      return 0;
}

int vdelete(Vector *vector, int index)
{
    if (!vector || !vector->data) return -1;
    if (index < 0 || index >= vector->count) return -1;

    vector->count--;
    // FIX THIS
    printf("Successfully removed item [%d] at index %d\n", vector->data[index], index);

    for (int i = index; i < vector->count; i++)
        vector->data[i] = vector->data[i+1];

    if (vector->count == vector->capacity / 4 && vector->capacity > VECTOR_INIT_CAPACITY)
    {
        if (resize(vector, vector->capacity / 2) == -1)
            return -1;
    }
}

// MAIN WITH TESTS

void vector_int_print(Vector *vector);
int size(Vector *vector);
int capacity(Vector *vector);
int is_empty(Vector *vector);
int prepend(Vector *vector, int item);
int pop(Vector *vector);

int main(void)
{
    Vector *vector = vector_create();   // init vector
    size(vector);
    capacity(vector);
    is_empty(vector);
    push(vector, 3);
    insert(vector, 2, 0);
    prepend(vector, 1);
    size(vector);
    pop(vector); // FIX POP IN VDELETE
    size(vector);

    return EXIT_SUCCESS;
}

// print current number of items in vector
int size(Vector *vector)
{
    printf("Current amount of items in vector: %d \n", vector->count);
    return vector->count;   // return num of items (for func like is_empty)
}

// print current size of vector
int capacity(Vector *vector)
{
    printf("Current size of vector: %d \n", vector->capacity);
}

// check if vector is empty
int is_empty(Vector *vector)
{
    if (size(vector) == 0)
        printf("This vector is currently empty\n");
    else printf("This vector contains items\n");
}

// insert item at index 0
int prepend(Vector *vector, int item)
{
    insert(vector, item, 0);
}

// remove item from end
int pop(Vector *vector)
{
    vdelete(vector, (vector->count)-1);
}

// print vector as array []
void vector_int_print(Vector *vector)
{
    printf("[ ");
    for (size_t i = 0; i < vector->count; i++)
        printf("%d ", *((int * ) vector->data[i]));
    printf("]\n");
}
