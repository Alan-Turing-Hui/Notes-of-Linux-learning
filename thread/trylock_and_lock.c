#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;

void* routine(void* arg) {
    if (pthread_mutex_trylock(&mutex) == 0) {
        printf("Got the lock\n");
        sleep(1);
        pthread_mutex_unlock(&mutex);
    } else {
        printf("Didn't get lock\n");
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t th[4];
    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < 4; i++) {
        if (pthread_create(th + i, NULL, routine, NULL) != 0) {
            perror("Failed to create threads\n");
            return 1;
        }
    }
    for (int i = 0; i < 4; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("pthread_join failed\n");
            return 2;
        } 
    }
    pthread_mutex_destroy(&mutex);
    return 0;
}