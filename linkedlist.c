#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char val;
    struct node *next;
} node_t;

int main(int argc, char *argv[]) {
    // init root
    node_t *root = malloc(sizeof(node_t));   
    root->val = 'a';
    root->next = NULL;

    // init list
    node_t *prev = root;
    for (char c = 'b'; c <= 'z'; c++) {
        node_t *node = malloc(sizeof(node_t));
        node->val = c;
        node->next = NULL;

        // link to previous node
        prev->next = node;
        prev = node;
    }

    // print list
    node_t *node = root;
    while (node != NULL) {
        printf("Node %c\n", node->val);
        node = node->next;
    }
}
