#include "btree.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp = fopen("btree.dat", "rb");
    if (!fp) {
        printf("Failed to open file.\n");
        return 1;
    }

    // Read root offset from file
    long root_offset;
    fseek(fp, 0, SEEK_SET);
    fread(&root_offset, sizeof(long), 1, fp);

    if (root_offset == 0) {
        printf("Empty tree.\n");
        fclose(fp);
        return 0;
    }

    // Print tree using offsets
    printf("B-tree structure loaded from file:\n");
    PrintBTree(fp, root_offset, 0);

    fclose(fp);
    return 0;
}
