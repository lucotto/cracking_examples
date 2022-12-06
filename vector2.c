// https://alexandra-zaharia.github.io/posts/implementing-a-vector-in-c/
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    void **data;        // information in the vector
    size_t count;       // number of currently stored elements in the vector
    size_t capacity;    // capacity of the vector
} Vector;

const size_t VECTOR_INIT_CAPACITY = 4;

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

static int _vector_resize(Vector *vector, size_t capacity)
{
    void **data = realloc(vector->data, capacity * sizeof(void *));
    vector->capacity = capacity;

    if (!data) return -1;
    if (data != vector->data)
        vector->data = data;
    data = NULL;

    return 0;
}

int vector_add(Vector *vector, void *item)
{
    if (!vector || !vector->data) return -1;

    if (vector->count == vector->capacity)
    {
        if (_vector_resize(vector, 2 * vector->capacity) == -1)
            return -1;
    }

    vector->data[vector->count++] = item;

    return 0;
}

int vector_insert(Vector *vector, void *item, int index)
{
    if (!vector || !vector->data) return -1;
    if (index < 0 || index > vector->count) return -1;

    if (index == vector->count) {
        if (vector_add(vector, item) == -1) return -1;
    } else {
        if (vector->count == vector->capacity) {
            if (_vector_resize(vector, 2 * vector->capacity) == -1)
                return -1;
        }

        for (int i = vector->count; i > index; i--)
            vector->data[i] = vector->data[i-1];

        vector->data[index] = item;
        vector->count++;
      }

      return 0;
}

int vector_delete(Vector *vector, int index)
{
    if (!vector || !vector->data) return -1;
    if (index < 0 || index >= vector->count) return -1;

    vector->count--;

    for (int i = index; i < vector->count; i++)
        vector->data[i] = vector->data[i+1];

    if (vector->count == vector->capacity / 4 && vector->capacity > VECTOR_INIT_CAPACITY)
    {
        if (_vector_resize(vector, vector->capacity / 2) == -1)
            return -1;
    }
}

void vector_int_print(Vector *vector);

int main(void)
{
    int i;
    Vector *vector = vector_create();
    if (!vector) {
        fprintf(stderr, "Cannot allocate vector.\n");
        exit(EXIT_FAILURE);
    }

    int even[3] = {2, 4, 6};
    for (i = 0; i < 3; i++)
        vector_add(vector, &even[i]);
    vector_int_print(vector);

    int odd[3] = {1, 3, 5};
    vector_insert(vector, &odd[0], 0);
    vector_insert(vector, &odd[1], 2);
    vector_insert(vector, &odd[2], 4);
    vector_int_print(vector);

    for (i = 5; i > 2; i--)
        vector_delete(vector, i);
    vector_int_print(vector);

    vector_free(vector);

    return EXIT_SUCCESS;
}

void vector_int_print(Vector *vector)
{
    printf("[ ");
    for (size_t i = 0; i < vector->count; i++)
        printf("%d ", *((int * ) vector->data[i]));
    printf("]\n");
}
