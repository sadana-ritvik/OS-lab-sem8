#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
 
#define SIZE 5
#define NUMB_THREADS 6
#define PRODUCER_LOOPS 2
 
typedef int buffer_t;
int buffer[SIZE];
int buffer_index_write;
int buffer_index_read;
 
pthread_mutex_t buffer_mutex;
sem_t full;
sem_t empty;
 
 
void insert(int value) {
    if (buffer_index_write < SIZE) {
        buffer[buffer_index_write] = value;
        buffer_index_write = (buffer_index_write + 1)%SIZE;
    } else {
        printf("Buffer overflow\n");
    }
}
 
int readbuffer() {
    int val;
    if (buffer_index_read < SIZE && buffer_index_read != buffer_index_write) {
        val = buffer[buffer_index_read];
        buffer_index_read = (buffer_index_read + 1)%SIZE;
        return val;
    } else {
        printf("Buffer underflow\n");
    }
    return 0;
}
 
 
void *producer(void *thread_n) {
    int thread_numb = *(int *)thread_n;
    buffer_t value;
    int i=0;
    while (i++ < PRODUCER_LOOPS) {
        sleep(rand() % 10);
        value = rand() % 100;
        sem_wait(&empty); // sem=0: wait. sem>0: go and decrement it
        pthread_mutex_lock(&buffer_mutex); 
        insert(value);
        pthread_mutex_unlock(&buffer_mutex);
        sem_post(&full); // post (increment) emptybuffer semaphore
        printf("Producer %d added %d to buffer\n", thread_numb, value);
    }
    pthread_exit(0);
}
 
void *consumer(void *thread_n) {
    int thread_numb = *(int *)thread_n;
    int value;
    int i=0;
    while (i++ < PRODUCER_LOOPS) {
        sem_wait(&full);
        pthread_mutex_lock(&buffer_mutex);
        value = readbuffer();
        pthread_mutex_unlock(&buffer_mutex);
        sem_post(&empty); // post (increment) fullbuffer semaphore
        printf("Consumer %d removed %d from buffer\n", thread_numb, value);
   }
    pthread_exit(0);
}
 
int main() {
    buffer_index_read = 0;
    buffer_index_write = 0;
 
    pthread_mutex_init(&buffer_mutex, NULL);
    sem_init(&empty,  0,SIZE); 
    sem_init(&full, 0, 0);
    pthread_t thread[NUMB_THREADS];
    int thread_numb[NUMB_THREADS];
    int i;
    for (i = 0; i < NUMB_THREADS; ) {
        thread_numb[i] = i;
        pthread_create(thread + i, NULL, producer,  thread_numb + i);
        i++;
        thread_numb[i] = i;
        // playing a bit with thread and thread_numb pointers...
        pthread_create(&thread[i],  NULL,  consumer,  &thread_numb[i]); 
        i++;
    }
 
    for (i = 0; i < NUMB_THREADS; i++)
        pthread_join(thread[i], NULL);
 
    pthread_mutex_destroy(&buffer_mutex);
    sem_destroy(&full);
    sem_destroy(&empty);
 
    return 0;
}
