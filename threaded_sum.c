/*
Jonathan Stoll
CS 446 - HW2
*/

#include<stdio.h>
#include<string.h>
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

    if (argc != 3) {
        printf("%s\n", "Not enough parameters");
        return -1;
    }
    else {
        int arr[100000000];
        char filename = argv[1];
        int threadsRequested = argv[2];
        int valuesRead = readFile(filename, arr);

        if (threadsRequested > valuesRead) {
            printf("%s\n", "Too many theads requested!");
            return -1;
        }
    }

    long long int totalSum = 0;

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

}