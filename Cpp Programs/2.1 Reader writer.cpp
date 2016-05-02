#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex, writeblock;
int data = 0,rcount = 0;

void *reader(void *arg)
{
    int f;
    f = ((int)arg);
    sem_wait(&mutex);
    rcount = rcount + 1;
    if(rcount==1)
        sem_wait(&writeblock);
    
    sem_post(&mutex);
    
    printf("Data read by the reader%d is %d\n",f,data);
    
    sem_wait(&mutex);
    rcount = rcount - 1;
    
    if(rcount==0)
        sem_post(&writeblock);

    sem_post(&mutex);
}

void *writer(void *arg)
{
    int f;
    f = ((int) arg);
    sem_wait(&writeblock);
    data++;
    printf("Data writen by the writer%d is %d\n",f,data);
    //sleep(1);
    sem_post(&writeblock);
}

int main()
{
    int i,j=0,b;
    pthread_t thread[10];
    sem_init(&mutex,0,1);
    sem_init(&writeblock,0,1);
    
    for(i=0;j<=2;i++,j++)
    {
        pthread_create(&thread[i],NULL,writer,(void *)j);
        i++;
        pthread_create(&thread[i],NULL,reader,(void *)j);
    }
    int k = i;
    for(i=0;i<=k;i++)
    {
        pthread_join(thread[i],NULL);
    }
return 0;
}
