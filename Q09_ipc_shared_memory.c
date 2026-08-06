/* Q9. Inter-process communication using shared memory
   Note: Requires a POSIX/Linux environment with System V IPC support (works on most online GDB Linux backends) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    int shmid;
    key_t key = 1234;
    char *str;

    shmid = shmget(key, 1024, IPC_CREAT | 0666);
    if (shmid < 0) { perror("shmget failed"); exit(1); }

    str = (char *) shmat(shmid, NULL, 0);
    if (str == (char *) -1) { perror("shmat failed"); exit(1); }

    printf("Write data to shared memory: ");
    fgets(str, 1024, stdin);

    printf("Data read from shared memory: %s\n", str);

    shmdt(str);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
