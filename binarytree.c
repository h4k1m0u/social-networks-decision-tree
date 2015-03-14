#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char *val;
    struct node *left;
    struct node *right;
} node_t;

void generate_tree(int i, node_t *parent) {
    if (i == 0)
        return;

    // attach left and right children to parent 
    node_t *left = malloc(sizeof(node_t));
    node_t *right = malloc(sizeof(node_t));
    left->val = malloc(sizeof(char) * 100);
    right->val = malloc(sizeof(char) * 100);
    sprintf(left->val, "%s > left%d", parent->val, i);
    sprintf(right->val, "%s > right%d", parent->val, i);
    parent->left = left;
    parent->right = right;

    // repeat same process with each child
    generate_tree(i - 1, left);
    generate_tree(i - 1, right);
}

void preorder_traversal(node_t *node) {
    if (node == NULL)
        return;
    printf("Node: %s\n", node->val);
    preorder_traversal(node->left);    
    preorder_traversal(node->right);    
}

int main() {
    // init decision tree from file
    node_t *root = malloc(sizeof(node_t));
    root->val = "root";
    root->left = NULL;
    root->right = NULL;

    // recursively generate a binary tree (depth=3)
    generate_tree(3, root);

    // recursively print tree
    preorder_traversal(root);

    return 0;
}
