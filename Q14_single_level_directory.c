/* Q14. Organize the file using single level directory */
#include <stdio.h>
#include <string.h>
#define MAX 20

struct file {
    char name[50];
};

int main() {
    struct file dir[MAX];
    int n = 0, choice, i, k;
    char fname[50];

    while (1) {
        printf("\n1. Create file\n2. Display files\n3. Delete file\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter file name: ");
            scanf("%s", fname);
            strcpy(dir[n].name, fname);
            n++;
            printf("File created.\n");
        } else if (choice == 2) {
            printf("Files in directory:\n");
            for (i = 0; i < n; i++)
                printf("%s\n", dir[i].name);
        } else if (choice == 3) {
            printf("Enter file name to delete: ");
            scanf("%s", fname);
            for (i = 0; i < n; i++) {
                if (strcmp(dir[i].name, fname) == 0) {
                    for (k = i; k < n - 1; k++)
                        dir[k] = dir[k + 1];
                    n--;
                    printf("File deleted.\n");
                    break;
                }
            }
        } else break;
    }
    return 0;
}
