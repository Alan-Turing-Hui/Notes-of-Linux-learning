#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

void *roll_dice(void *arg) {
    int value = (rand() % 6) + 1;
    int* result = malloc(sizeof(int));
    *result = value;
    // printf("%d\n", value);
    printf("Thread result: %p\n", result);
    return (void*) result;
}

int main(int argc, char *argv[]) {
    int* res;
    srand(time(NULL));
    pthread_t th;
    if (pthread_create(&th, NULL, roll_dice, NULL) != 0) {
        perror("Failed to create threads\n");
        return 1;
    }
    if (pthread_join(th, (void**) &res) != 0) {
        perror("pthread_join failed\n");
        return 2;
    } 
    printf("Main result: %p\n", res);
    printf("Result: %d\n", *res);
    free(res);
    return 0;
}