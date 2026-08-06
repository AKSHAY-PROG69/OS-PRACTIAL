/* Q15. Organize the file using two level directory structure */
#include <stdio.h>
#include <string.h>
#define MAX 10

struct file {
    char name[50];
};

struct user {
    char uname[50];
    struct file files[MAX];
    int fcount;
};

int main() {
    struct user users[MAX];
    int ucount = 0, choice, ui, i;
    char uname[50], fname[50];

    while (1) {
        printf("\n1. Create user\n2. Create file under user\n3. Display all\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter user name: ");
            scanf("%s", uname);
            strcpy(users[ucount].uname, uname);
            users[ucount].fcount = 0;
            ucount++;
        } else if (choice == 2) {
            printf("Enter user name: ");
            scanf("%s", uname);
            for (ui = 0; ui < ucount; ui++) {
                if (strcmp(users[ui].uname, uname) == 0) {
                    printf("Enter file name: ");
                    scanf("%s", fname);
                    strcpy(users[ui].files[users[ui].fcount].name, fname);
                    users[ui].fcount++;
                    break;
                }
            }
        } else if (choice == 3) {
            for (ui = 0; ui < ucount; ui++) {
                printf("User: %s\n", users[ui].uname);
                for (i = 0; i < users[ui].fcount; i++)
                    printf("  File: %s\n", users[ui].files[i].name);
            }
        } else break;
    }
    return 0;
}
