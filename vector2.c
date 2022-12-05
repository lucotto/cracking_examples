// https://alexandra-zaharia.github.io/posts/implementing-a-vector-in-c/

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

    if (index == vector->count {
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

