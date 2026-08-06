/* Q17. Deadlock avoidance using Banker's algorithm */
#include <stdio.h>
#define P 5
#define R 3

int main() {
    int alloc[P][R] = {{0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2}};
    int max[P][R] = {{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};
    int avail[R] = {3,3,2};
    int need[P][R];
    int finish[P] = {0};
    int safeSeq[P];
    int i, j, k, count = 0;

    for (i = 0; i < P; i++)
        for (j = 0; j < R; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    while (count < P) {
        int found = 0;
        for (i = 0; i < P; i++) {
            if (!finish[i]) {
                int canRun = 1;
                for (j = 0; j < R; j++) {
                    if (need[i][j] > avail[j]) { canRun = 0; break; }
                }
                if (canRun) {
                    for (k = 0; k < R; k++)
                        avail[k] += alloc[i][k];
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) {
            printf("System is not in a safe state.\n");
            return 0;
        }
    }

    printf("System is in a safe state.\nSafe sequence: ");
    for (i = 0; i < P; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");
    return 0;
}
