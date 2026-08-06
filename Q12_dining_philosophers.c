/* Q12. Simulate the Dining-Philosophers problem
   Note: Compile with -lpthread */
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define N 5

pthread_mutex_t forks[N];
pthread_mutex_t mutex;

void *philosopher(void *num) {
    int id = *(int *) num;
    int left = id;
    int right = (id + 1) % N;

    pthread_mutex_lock(&mutex);
    pthread_mutex_lock(&forks[left]);
    pthread_mutex_lock(&forks[right]);
    pthread_mutex_unlock(&mutex);

    printf("Philosopher %d is eating\n", id);
    sleep(1);

    pthread_mutex_unlock(&forks[left]);
    pthread_mutex_unlock(&forks[right]);
    printf("Philosopher %d has finished eating\n", id);

    return NULL;
}

int main() {
    pthread_t phil[N];
    int ids[N];
    int i;

    pthread_mutex_init(&mutex, NULL);
    for (i = 0; i < N; i++)
        pthread_mutex_init(&forks[i], NULL);

    for (i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&phil[i], NULL, philosopher, &ids[i]);
    }
    for (i = 0; i < N; i++)
        pthread_join(phil[i], NULL);

    return 0;
}
