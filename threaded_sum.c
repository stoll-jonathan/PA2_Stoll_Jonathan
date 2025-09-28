/*
Jonathan Stoll
CS 446 - HW2
*/

#include<stdio.h>
#include <string.h>
#include<pthread.h>

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

    return 0;
}

int readFile(char name[], int arr[]) {
    int count = 0;

    return count;
}

void* arraysum(void* data) {

}