/* Q8. Simulate Round Robin scheduling algorithm */
#include <stdio.h>
#define MAX 20

int main() {
    int n, tq, i, time = 0;
    int bt[MAX], rem[MAX], wt[MAX], tat[MAX];
    int allDone;
    float avwt = 0, avtat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        printf("Enter burst time for P%d: ", i + 1);
        scanf("%d", &bt[i]);
        rem[i] = bt[i];
    }
    printf("Enter time quantum: ");
    scanf("%d", &tq);

    while (1) {
        allDone = 1;
        for (i = 0; i < n; i++) {
            if (rem[i] > 0) {
                allDone = 0;
                if (rem[i] > tq) {
                    time += tq;
                    rem[i] -= tq;
                } else {
                    time += rem[i];
                    wt[i] = time - bt[i];
                    rem[i] = 0;
                }
            }
        }
        if (allDone) break;
    }

    printf("\nProcess\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        avwt += wt[i];
        avtat += tat[i];
        printf("P%d\t%d\t%d\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }
    printf("\nAverage Waiting Time = %.2f\n", avwt / n);
    printf("Average Turnaround Time = %.2f\n", avtat / n);
    return 0;
}
