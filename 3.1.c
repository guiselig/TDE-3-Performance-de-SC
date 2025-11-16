#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock_A;
pthread_mutex_t lock_B;

void* thread_1() {
    printf("\nT1 está tentando pegar Lock A...\n");
    pthread_mutex_lock(&lock_A);
    printf("T1 pegou Lock A.\n");

    sleep(1);

    printf("\nT1 está tentando pegar Lock B...\n");
    pthread_mutex_lock(&lock_B);
    printf("T1 pegou Lock B.\n");

    pthread_mutex_unlock(&lock_B);
    pthread_mutex_unlock(&lock_A);
    return 0;
}

void* thread_2() {
    printf("\nT2 está tentando pegar Lock B...\n");
    pthread_mutex_lock(&lock_B);
    printf("T2 pegou Lock B.\n");

    sleep(1);

    printf("\nT2 está tentando pegar Lock A...\n");
    pthread_mutex_lock(&lock_A);
    printf("T2 pegou Lock A.\n");

    pthread_mutex_unlock(&lock_A);
    pthread_mutex_unlock(&lock_B);
    return 0;
}

int main() {
    pthread_t t1, t2;

    pthread_mutex_init(&lock_A, 0);
    pthread_mutex_init(&lock_B, 0);
    
    pthread_create(&t1, 0, thread_1, 0);
    pthread_create(&t2, 0, thread_2, 0);

    pthread_join(t1, 0);
    pthread_join(t2, 0);

    return 0;
}