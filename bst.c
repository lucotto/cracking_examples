#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node{
    int data;
    struct node *left;
    struct node *right;
};

struct node *root = NULL;

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
    if (root == NULL)
        return 0;
    return 1 + get_node_count(root->left) + get_node_count(root->right);
}

void delete_tree(struct node *root){
    if (root == NULL)
        return;
    delete_tree(root->left);
    delete_tree(root->right);
    free(root);
}

bool is_in_tree(struct node *root, int item){
    if (root != NULL){
        if (item == root->data)
            return true;
        else if (item < root->data)
            return is_in_tree(root->left, item);
        else
            return is_in_tree(root->right, item);
    }
    else
        return false;
}

void print_is_in_tree(struct node *root, int item){
    if (is_in_tree(root, item))
        printf("Item [%d] exists in BST\n", item);
    else
        printf("Item [%d] doesn't exist in BST\n", item);
}

int get_height(struct node *root){
    if (root == NULL)
        return 0;
    int left_height = get_height(root->left);
    int right_height = get_height(root->right);
    return 1 + (left_height > right_height ? left_height : right_height);
}

struct node *get_min(struct node *root){
    struct node *temp = root;
    while (temp->left != NULL){
        temp = temp->left;
    }
    return temp;
}

struct node *get_max(struct node *root){
    struct node *temp = root;
    while (temp->right != NULL){
        temp = temp->right;
    }
    return temp;
}

struct node *delete_value(struct node *root, int item){
    if (root == NULL)
        return root;
    else if (item < root->data)
        root->left = delete_value(root->left, item);
    else if (item > root->data)
        root->right = delete_value(root->right, item);
    else{
        if (root->left == NULL && root->right == NULL){
            free(root);
            root = NULL;
        }
        else if (root->left == NULL){
            struct node *temp = root;
            root = root->right;
            free(temp);
        }
        else if (root->right == NULL){
            struct node *temp = root;
            root = root->left;
            free(temp);
        }
        else{
            struct node *temp = get_min(root->right);
            root->data = temp->data;
            root->right = delete_value(root->right, temp->data);
        }
    }
    return root;
}

int get_successor(struct node *root, int item){
    struct node *temp = root;
    if (item >= get_max(root)->data)
        return -1;
    if ()
}

bool is_subtree_lesser(struct node *root, int item){
    if (root == NULL)
        return true;
    if (root->data <= item
        && is_subtree_lesser(root->left, item)
        && is_subtree_lesser(root->right, item))

        return true;
    else
        return false;
}

bool is_subtree_greater(struct node *root, int item){
    if (root == NULL)
        return true;
    if (root->data > item
        && is_subtree_greater(root->left, item)
        && is_subtree_greater(root->right, item))

        return true;
    else
        return false;
}

bool is_bst(struct node *root){
    if (is_subtree_lesser(root->left, root->data)
        && is_subtree_greater(root->right, root->data)
        && is_bst(root->left)
        && is_bst(root->right))

        return true;
    else
        return false;
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
    insert(root, 14);
    insert(root, 9);
    insert(root, 8);
    insert(root, 5);
    insert(root, 6);
    insert(root, 50);
    insert(root, 49);
    print_values(root);
    printf("Count: %d\n", get_node_count(root));
    printf("%d\n", is_bst(root));
    print_is_in_tree(root, 11);
    printf("Height: %d\n", get_height(root));
    printf("Min item is [%d]\n", get_min(root)->data);
    printf("Max item is [%d]\n", get_max(root)->data);
    print_values(root);
    printf("\n%d\n", get_successor(root, 22));
    //delete_tree(root);
    //root = NULL;
    return 0;
}
