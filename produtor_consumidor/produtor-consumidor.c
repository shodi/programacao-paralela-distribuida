#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define true 1
#define false 0

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int buff_index = 0;

sem_t full,empty;
pthread_mutex_t mutex;

void *produz(void* args) {
    while (true) {
        volatile int i = 0xFFFFF;
        while (i --> 0) {}
        sem_wait(&empty);
		pthread_mutex_lock(&mutex);
		int item = rand() % 100;
		buffer[buff_index++] = item;
		printf("Produziu o item %d\n", item);
		pthread_mutex_unlock(&mutex);
		sem_post(&full);
    }
}

void *consome(void* args) {
    while (true) {
        volatile int i = 0xFFFFFFF;
        while (i --> 0) {}
		sem_wait(&full);
		pthread_mutex_lock(&mutex);
		int item = buffer[--buff_index];
		printf("Consumiu o item %d\n", item);
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);
    }
}


int main(int argc, char **argv) {
    
    pthread_t produtor, consumidor;
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFFER_SIZE);
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&produtor, NULL, produz, NULL);
    pthread_create(&consumidor, NULL, consome, NULL);
    pthread_exit(NULL);

    return 0;
}