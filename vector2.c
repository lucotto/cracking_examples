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

