#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

int main() {
    char *line = NULL;
    FILE *fp = fopen("decisiontree.txt", "r");
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("%s", line);
    }

    free(line);
    fclose(fp);

    return 0;
}
