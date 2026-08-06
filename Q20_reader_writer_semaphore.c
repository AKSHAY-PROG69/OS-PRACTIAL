/* Q20. Simulate Reader-Writer problem using semaphores
   Note: Compile with -lpthread */
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex, wrt;
int readCount = 0;
int data = 0;

void *reader(void *arg) {
    int id = *(int *) arg;
    sem_wait(&mutex);
    readCount++;
    if (readCount == 1) sem_wait(&wrt);
    sem_post(&mutex);

    printf("Reader %d read data = %d\n", id, data);
    sleep(1);

    sem_wait(&mutex);
    readCount--;
    if (readCount == 0) sem_post(&wrt);
    sem_post(&mutex);

    return NULL;
}

void *writer(void *arg) {
    int id = *(int *) arg;
    sem_wait(&wrt);
    data++;
    printf("Writer %d wrote data = %d\n", id, data);
    sleep(1);
    sem_post(&wrt);
    return NULL;
}

int main() {
    pthread_t r[3], w[2];
    int rid[3] = {1,2,3}, wid[2] = {1,2};
    int i;

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    for (i = 0; i < 2; i++)
        pthread_create(&w[i], NULL, writer, &wid[i]);
    for (i = 0; i < 3; i++)
        pthread_create(&r[i], NULL, reader, &rid[i]);

    for (i = 0; i < 2; i++)
        pthread_join(w[i], NULL);
    for (i = 0; i < 3; i++)
        pthread_join(r[i], NULL);

    return 0;
}
