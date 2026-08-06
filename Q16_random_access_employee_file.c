/* Q16. Random access file for processing employee details */
#include <stdio.h>
#include <string.h>

struct employee {
    int id;
    char name[50];
    float salary;
};

int main() {
    FILE *fp;
    struct employee emp;
    int choice, recno;

    fp = fopen("employee.dat", "rb+");
    if (fp == NULL) {
        fp = fopen("employee.dat", "wb+");
    }

    while (1) {
        printf("\n1. Add record\n2. Read record\n3. Update record\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter record number, id, name, salary: ");
            scanf("%d %d %s %f", &recno, &emp.id, emp.name, &emp.salary);
            fseek(fp, recno * sizeof(struct employee), SEEK_SET);
            fwrite(&emp, sizeof(struct employee), 1, fp);
        } else if (choice == 2) {
            printf("Enter record number to read: ");
            scanf("%d", &recno);
            fseek(fp, recno * sizeof(struct employee), SEEK_SET);
            fread(&emp, sizeof(struct employee), 1, fp);
            printf("ID: %d, Name: %s, Salary: %.2f\n", emp.id, emp.name, emp.salary);
        } else if (choice == 3) {
            printf("Enter record number to update: ");
            scanf("%d", &recno);
            printf("Enter new id, name, salary: ");
            scanf("%d %s %f", &emp.id, emp.name, &emp.salary);
            fseek(fp, recno * sizeof(struct employee), SEEK_SET);
            fwrite(&emp, sizeof(struct employee), 1, fp);
        } else break;
    }

    fclose(fp);
    return 0;
}
