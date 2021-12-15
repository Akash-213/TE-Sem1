#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>


#define MaxItems 5 // Maximum items a producers can producers or a consumers can consumerssume
#define BufferSize 10 // Size of the buffer


// counting semaphores
sem_t empty;
sem_t full;

// prod & cons index
int prodIndex = 0;
int consIndex = 0;

// buffer array
int *buffer;

// producers & consumers count
int prodsCount,consCount;

// mutex lock
pthread_mutex_t mutex;


void *producersfunc(void *pno)
{   
    int item;
    for(int i = 0; i < prodsCount; i++) {
        item = rand(); // producersduce an random item

        //decrements value as new item is produced 
        // it will take up one empty space in buffer
        sem_wait(&empty);

        //lock the mutex
        pthread_mutex_lock(&mutex);

		//now critical section starts

        //store in buffer
        buffer[prodIndex] = item;

        printf("Producers %d: Insert Item %d at %d\n", *((int *)pno),buffer[prodIndex],prodIndex);
        
        // index updated
        prodIndex = (prodIndex+1)%BufferSize;

        // lock removed
        pthread_mutex_unlock(&mutex);

        //increments the value
        sem_post(&full);
    }
}

void *consumersfunc(void *cno)
{   
    for(int i = 0; i < consCount; i++) {

        // decrement the value
        sem_wait(&full);

        // lock the mutex
        pthread_mutex_lock(&mutex);
        
        // removed from buffer
        int item = buffer[consIndex];
        printf("Consumers %d: Remove Item %d from %d\n",*((int *)cno),item, consIndex);
        
        // index updated
        consIndex = (consIndex+1)%BufferSize;

        //unlock the mutex
        pthread_mutex_unlock(&mutex);

        // decrement the value
        sem_post(&empty);
    }
}

int main()
{  
    printf("Enter the number of producers: \n");
	scanf("%d",&prodsCount);	
	printf("Enter the number of consumers: \n");
	scanf("%d",&consCount);

    // create threads array
    pthread_t producers[prodsCount],consumers[consCount];

    // intializaing the lock
    pthread_mutex_init(&mutex, NULL);

    // initialising empty and full
    sem_init(&empty,0,BufferSize);
    sem_init(&full,0,0);

    // Just used for numbering the producers and consumers
    int a[5] = {1,2,3,4,5}; 

    int *loc;
    int res;

    printf("Producers Threads are being created....\n");
    for(int i = 0; i < prodsCount; i++) {
		printf("Creating producers number :  %d \n",i);

		//allocate memory
		loc=(int *) malloc(sizeof(int));

		//associate value at memory
        // *loc = &a[i];
		*loc=i;
        
		//create thread
		res = pthread_create(&producers[i], NULL, (void *)producersfunc,loc);
		if (res != 0) {
			perror("Error in thread creation!");
			exit(EXIT_FAILURE);
		}
    }

    printf("Consumer Threads are being created....\n");
    for(int i = 0; i < consCount; i++) {
        printf("Creating Consumer for : %d \n",i);
		//allocate memory
		loc=(int *) malloc(sizeof(int));

		//associate value at memory
        // *loc = &a[i];
		*loc=i;

  		//create thread
        res = pthread_create(&consumers[i],NULL,(void *) consumersfunc,loc);
		if (res != 0) {
			perror("Error in thread creation!");
			exit(EXIT_FAILURE);
		}

      }

    printf("Producer Threads are being joined ... \n");
    for(int i = 0; i < prodsCount; i++) {
        
        printf("Producer Thread joined");
        res = pthread_join(producers[i], NULL);
		if(res!=0){
		    printf("Error in thread join: \n");
		    exit(EXIT_FAILURE);
		}
    }

    printf("Consumer Threads are being joined ... \n");
    for(int i = 0; i < consCount; i++) {

        printf("Customer Thread joined");
        res = pthread_join(consumers[i], NULL);
		if(res!=0){
		    printf("Error in thread join: \n");
		    exit(EXIT_FAILURE);
		}
    }

    // destroying the variables
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
    
}

