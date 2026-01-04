#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define SIZE 5

int buffer[SIZE];
int in = 0, out = 0;
sem_t empty, full;
pthread_mutex_t lock;

void* producer(void* arg) {
    for(int i=0; i<5; i++) {
        int item = i+1;
        sem_wait(&empty);
        pthread_mutex_lock(&lock);
        buffer[in] = item;
        printf("Producer produces %d at %d\n", item, in);
        in = (in+1) % SIZE;
        pthread_mutex_unlock(&lock);
        sem_post(&full);
        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg) {
    for(int i=0; i<5; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&lock);
        int item = buffer[out];
        printf("Consumer consumes %d from %d\n", item, out);
        out = (out+1) % SIZE;
        pthread_mutex_unlock(&lock);
        sem_post(&empty);
        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;
    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&lock, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&lock);

    return 0;
}