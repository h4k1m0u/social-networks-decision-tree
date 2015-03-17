#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char *val;
    struct node *left;
    struct node *right;
} node_t;

int get_total_file_lines(char *filename) {
    // open file for reading
    FILE *f = fopen(filename, "r");

    // count number of newline characters
    int num_lines = 0;
    char c;
    do {
        c = fgetc(f);
        if (c == '\n')
            num_lines++;
    } while (c != EOF);

    fclose(f);

    return num_lines;
}

node_t* generate_tree_from_file(char *filename) {
    // get number of nodes
    int num_nodes = get_total_file_lines(filename);

    // open file for reading
    char *line = NULL;
    FILE *f = fopen(filename, "r");
    size_t len = 0;
    ssize_t read;

    // save file content into arrays
    int i = 1;
    char *nodes_vals[num_nodes + 1];
    int nodes_children[num_nodes + 1][2];
    node_t *nodes[num_nodes + 1];
    char *child_left, *child_right;
    node_t *node;

    while ((read = getline(&line, &len, f)) != -1) {
        // save node val
        nodes_vals[i] = malloc(sizeof(char) * (strlen(line) - 5));
        strncpy(nodes_vals[i], line + 6, strlen(line) - 7);

        // save node children indexes
        child_left = malloc(sizeof(char) * 2);
        child_right = malloc(sizeof(char) * 2);
        strncpy(child_left, line, 2);
        strncpy(child_right, line + 3, 2);
        nodes_children[i][0] = atoi(child_left);
        nodes_children[i][1] = atoi(child_right);

        // save node
        node = malloc(sizeof(node_t));
        node->val = nodes_vals[i];
        node->left = NULL;
        node->right = NULL;
        nodes[i] = node;

        i++;
    }

    // close file
    free(line);
    fclose(f);

    // build decision tree by updating nodes relations
    for (int i = 1; i <= num_nodes; i++) {
        node_t *node = nodes[i];
        node->left = (nodes_children[i][0] != 0 ? nodes[nodes_children[i][0]] : NULL);
        node->right = (nodes_children[i][1] != 0? nodes[nodes_children[i][1]] : NULL);
        nodes[i] = node;
    }

    // return root of the decision tree
    return nodes[1];
}

int main() {
    // generate a decision tree from file
    node_t *root = generate_tree_from_file("decisiontree.txt");
    printf("________________________________________________________________\n\n");
    printf("Answer these questions to find your ideal Social Network [y/n/q]:\n");
    printf("________________________________________________________________\n\n");

    // decision tree traversal (game loop)
    node_t *node = root;
    int c;
    while (node->right != NULL && node->left != NULL) {
        printf("%s: ", node->val);

        // read char from stdin (only one char at a time)
        c = getchar();
        while (getchar() != '\n');
        switch (c) {
            case 'y':
                node = node->left;
                break;
            case 'n':
                node = node->right;
                break;
            case 'q':
                return 0;
        }
    }

    // print found result
    printf("\nYour ideal Social Network is: %s", node->val);

    return 0;
}
