#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void* routine(void* arg) {
    int index = *(int*)arg;
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += primes[index + i];
    }
    *(int*)arg = sum;
    return (void*)arg;
}

int main(int argc, char *argv[]) {
    pthread_t th[2];
    for (int i = 0; i < 2; i++) {
        int* a = malloc(sizeof(int));
        *a = i * 5;
        if (pthread_create(th + i, NULL, routine, a) != 0) {
            perror("Failed to create threads\n");
            return 1;
        }
    }
    int globalSum = 0;
    for (int i = 0; i < 2; i++) {
        int* res;
        if (pthread_join(th[i], (void**)&res) != 0) {
            perror("pthread_join failed\n");
            return 2;
        } 
        globalSum += *res;
        free(res);
    }
    printf("Global sum is %d\n", globalSum);
    return 0;
}