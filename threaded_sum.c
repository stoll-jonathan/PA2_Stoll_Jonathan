/*
Jonathan Stoll
CS 446 - HW2
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<sys/time.h>

typedef struct _thread_data_t {
    const int *data;
    int startInd;
    int endInd;
    pthread_mutex_t *lock;
    long long int *totalSum;
} thread_data_t;

int readFile(char[], int[]);
void* arraysum(void*);

int main(int argc, char* argv[]) {

    // validate param count
    if (argc != 3) {
        printf("%s\n", "Not enough parameters");
        return -1;
    }
    
    // parse user input and validate thread count
    int* arr = malloc(sizeof(int) * 100000000);
    char* filename = argv[1];
    int threadsRequested = atoi(argv[2]);
    int valuesRead = readFile(filename, arr);

    if (threadsRequested > valuesRead) {
        printf("%s\n", "Too many threads requested!");
        return -1;
    }


    // start timer and create mutexes and thread_data array
    long long int totalSum = 0;
    struct timeval start, end;
    gettimeofday(&start, NULL);
    pthread_mutex_t lock;
    pthread_mutex_init(&lock, NULL);
    thread_data_t threadData[threadsRequested];


    // divide the array and fill each thread
    int sliceSize = valuesRead / threadsRequested;
    int remainderSize = valuesRead % threadsRequested;

    for (int i = 0; i < threadsRequested; i++) {
        threadData[i].data = arr;
        threadData[i].startInd = i * sliceSize;
        threadData[i].endInd = (i + 1) * sliceSize;
        
        // last thread takes remainder
        if (i == threadsRequested - 1) {
            threadData[i].endInd += remainderSize;
        }

        threadData[i].lock = &lock;
        threadData[i].totalSum = &totalSum;
    }


    // create threads and fill using arraysum, then wait for threads to finish
    pthread_t threads[threadsRequested];

    for (int i = 0; i < threadsRequested; i++) {
        pthread_create(&threads[i], NULL, arraysum, &threadData[i]);
    }

    for (int i = 0; i < threadsRequested; i++) {
        pthread_join(threads[i], NULL);
    }


    // end timer and print results
    gettimeofday(&end, NULL);
    double elapsed = ((end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)/1000000.0) * 1000;
    
    printf("Total sum: %lld\n", totalSum);
    printf("Execution time: %.3f ms\n", elapsed);


    // cleanup
    pthread_mutex_destroy(&lock);
    free(arr);

    return 0;
}

int readFile(char filename[], int arr[]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File not found...\n");
        return -1;
    }

    int count = 0;
    while (fscanf(file, "%d", &arr[count]) == 1) {
        count++;
    }

    fclose(file);
    return count;
}

void* arraysum(void* data) {

    // Cast void* data to thread_data_t*
    thread_data_t* threadData = (thread_data_t*)data;

    // Sum the current slice of the array
    long long int threadSum = 0;
    for (int i = threadData->startInd; i < threadData->endInd; i++) {
        threadSum += threadData->data[i];
    }

    // Add threadSum to the shared totalSum
    pthread_mutex_lock(threadData->lock);
    *(threadData->totalSum) += threadSum;
    pthread_mutex_unlock(threadData->lock);

    return NULL;
}