#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *left;
    struct node *right;
};

struct node *root = NULL;
int count = 0;

struct node *new_node(int item){
    struct node *n = (struct node*)malloc(sizeof(struct node));
    n->data = item;
    n->left = NULL;
    n->right = NULL;

    return n;
}

struct node *insert(struct node *root, int item){
    if (root == NULL)
        return new_node(item);
    else if (item > root->data)
        root->right = insert(root->right, item);
    else
        root->left = insert(root->left, item);
    return root;
};

int get_node_count(struct node *root){
    if (root != NULL){
        get_node_count(root->left);
        count++;
        get_node_count(root->right);
    }
    return count;
}

// non arriva al termine???
void delete_tree(struct node *root){
    if (root != NULL){
        delete_tree(root->left);
        delete_tree(root->right);
        printf("deleting %d\n", root->data);
        free(root);
    }
}

void print_values(struct node *root){
    if (root != NULL){
        print_values(root->left);
        printf(" %d ", root->data);
        print_values(root->right);
    }
}

void main(void){
    root = new_node(20);
    insert(root, 10);
    insert(root, 15);
    insert(root, 35);
    print_values(root);
    printf("Count: %d\n", get_node_count(root));
    delete_tree(root);
    print_values(root);
    printf("Count: %d\n", get_node_count(root));
    return 0;
}
