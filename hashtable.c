#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX 10

// key value pair struct
struct item{
    int key;
    int value;
};

//flag 0 = never used, flag 1 = currently used, flag 2 = used before
struct hashtable_item{
    int flag;
    struct item *data;
};

// array struct
int size = 0;
struct hashtable_item array[MAX];

// init array with 0 flags
void init_array(){
    for (int i = 0; i < MAX; i++){
        array[i].flag = 0;
        array[i].data = NULL;
    }
}

// hash f
int hash(int key){
    return (key % MAX);
}

// add module
void add(key, value){
    // hashed index
    int index = hash(key);
    int i = index;

    // memory alloc for new item + assignments
    struct item *new_item = (struct item*)malloc(sizeof(struct item));
    new_item->key = key;
    new_item->value = value;

    // if [i] is occupied
    while (array[i].flag == 1){
        // if key already exists
        if (array[i].data->key == key){
            printf("Updating %d\n", key);
            // update its value
            array[i].data->value = value;
            return;
        }
        // else linear-probe through indexes
        i = (i + 1) % MAX;
        // if every index is occupied
        if (i == index){
            printf("Hash table is full\n");
            return;
        }
    }

    // assignments
    array[i].flag = 1;
    array[i].data = new_item;
    size++;
    printf("Key %d has been inserted\n", key);
    return;
}

// exists O(1)
bool exists(key){
    if (array[hash(key)].flag == 1)
        return true;
    else return 0;
}

// get value by key
int get(key){
    if (exists(key))
        return array[hash(key)].data->value;
    else return 0;
}

void ht_remove(key){
    if (exists(key)){
        array[hash(key)].data = NULL;
        array[hash(key)].flag = 2;
        printf("Successfully removed (%d) key\n", key);
        return;
    }
    else
        printf("No such key in HT\n");
}

void printTable(){
    printf("HashTable(k,v): {\n");
    for (int i = 0; i < MAX; i++)
        if (array[i].data != NULL)
            printf("(%d, %d)\n", array[i].data->key, array[i].data->value);
    printf("}\n");
}

void main(){
    init_array();
    int choice, key, value;

    printf("Hash Table initialized\n");

    for(;;){
        printf("\n\nChoose a method\n1. Add key-value\n2. Remove by key\n3. Check existence\n4. Get value by key\n5. Print Table\n6. Quit\n\n\n");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                printf("Choose key and value\n");
                scanf("%d %d", &key, &value);
                add(key, value);
                break;
            case 2:
                printf("Choose key to remove\n");
                scanf("%d", &key);
                ht_remove(key);
                break;
            case 3:
                printf("Choose key to check\n");
                scanf("%d", &key);
                exists(key);
                break;
            case 4:
                printf("Choose key to get value from\n");
                scanf("%d", &key);
                if(get(key))
                    printf("(%d) value is (%d)\n", key, get(key));
                else
                    printf("No such key in HT\h");
                break;
            case 5:
                printTable();
                break;
            case 6:
                return 0;
            default:
                printf("Insert a valid entry\n");
                break;
        }
    }
    return 0;
}
