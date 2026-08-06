/* Q13. Implement the various memory allocation strategies (First / Best / Worst Fit) */
#include <stdio.h>
#define MAX 20

int main() {
    int bsize[MAX], psize[MAX], bno, pno;
    int allocation[MAX];
    int i, j, choice;
    int tempBsize[MAX];

    printf("Enter number of blocks: ");
    scanf("%d", &bno);
    printf("Enter size of each block:\n");
    for (i = 0; i < bno; i++)
        scanf("%d", &bsize[i]);

    printf("Enter number of processes: ");
    scanf("%d", &pno);
    printf("Enter size of each process:\n");
    for (i = 0; i < pno; i++)
        scanf("%d", &psize[i]);

    printf("Choose strategy: 1-First Fit  2-Best Fit  3-Worst Fit: ");
    scanf("%d", &choice);

    for (i = 0; i < pno; i++)
        allocation[i] = -1;
    for (i = 0; i < bno; i++)
        tempBsize[i] = bsize[i];

    for (i = 0; i < pno; i++) {
        int best = -1;
        for (j = 0; j < bno; j++) {
            if (tempBsize[j] >= psize[i]) {
                if (choice == 1) { best = j; break; }
                else if (choice == 2) {
                    if (best == -1 || tempBsize[j] < tempBsize[best]) best = j;
                } else if (choice == 3) {
                    if (best == -1 || tempBsize[j] > tempBsize[best]) best = j;
                }
            }
        }
        if (best != -1) {
            allocation[i] = best;
            tempBsize[best] -= psize[i];
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (i = 0; i < pno; i++) {
        if (allocation[i] != -1)
            printf("%d\t\t%d\t\t%d\n", i + 1, psize[i], allocation[i] + 1);
        else
            printf("%d\t\t%d\t\tNot Allocated\n", i + 1, psize[i]);
    }
    return 0;
}
