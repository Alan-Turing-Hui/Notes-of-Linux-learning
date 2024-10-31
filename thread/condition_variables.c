#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutexFuel;
pthread_cond_t condFuel;

int fuel = 0;

void* fuel_filling(void* arg) {
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutexFuel);
        fuel += 20;
        printf("Filled fuel... %d\n", fuel);
        pthread_mutex_unlock(&mutexFuel);
        // pthread_cond_signal(&condFuel);
        pthread_cond_broadcast(&condFuel);
        sleep(1);
    }
    return NULL;
}

void* car(void* arg) {
    pthread_mutex_lock(&mutexFuel);
    while(fuel < 40) {
        printf("No fuel, waiting...\n");
        pthread_cond_wait(&condFuel, &mutexFuel);
        // Equivalent to:
        // pthread_mutex_unlock(&mutexFuel);
        // wait for a signal on condFuel
        // pthread_mutex_lock(&mutexFuel);
    }
    fuel -= 40;
    printf("Got fuel. Now left: %d\n", fuel);
    pthread_mutex_unlock(&mutexFuel);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t th[5];
    pthread_mutex_init(&mutexFuel, NULL);
    pthread_cond_init(&condFuel, NULL);
    for (int i = 0; i < 5; i++) {
        if (i == 3 || i == 4) {
            if (pthread_create(th + i, NULL, fuel_filling, NULL) != 0) {
                perror("Failed to create threads\n");
                return 1;
            }
        } else {
            if (pthread_create(th + i, NULL, car, NULL) != 0) {
                perror("Failed to create threads\n");
                return 1;
            }
        }
    }
    for (int i = 0; i < 5; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("pthread_join failed\n");
            return 2;
        } 
    }
    pthread_mutex_destroy(&mutexFuel);
    pthread_cond_destroy(&condFuel);
    return 0;
}