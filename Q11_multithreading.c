/* Q11. Illustrate the concept of multithreading
   Note: Compile with -lpthread if your compiler requires it */
#include <stdio.h>
#include <pthread.h>

void *printMessage(void *arg) {
    char *msg = (char *) arg;
    printf("Thread says: %s\n", msg);
    pthread_exit(NULL);
}

int main() {
    pthread_t t1, t2;
    char *msg1 = "Hello from thread 1";
    char *msg2 = "Hello from thread 2";

    pthread_create(&t1, NULL, printMessage, (void *) msg1);
    pthread_create(&t2, NULL, printMessage, (void *) msg2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Main thread exiting\n");
    return 0;
}
