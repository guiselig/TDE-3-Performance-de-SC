#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 5

pthread_mutex_t garfos [N];

void* jantar_dos_filosofos (void* num) {
    
    int numfilosofo = *(int*)num; 
    
    int garfo_esq = numfilosofo;
    int garfo_dir = (numfilosofo + 1) % N;

    printf("Filosofo %d está pensando...\n\n", numfilosofo + 1);

    sleep(1);

    printf("Filosofo %d está com fome, ele quer os garfos %d e %d.\n\n", numfilosofo + 1, garfo_esq + 1, garfo_dir + 1);

    printf("Filosofo %d está tentando pegar o garfo esquerdo %d.\n\n", numfilosofo + 1, garfo_esq + 1);

    pthread_mutex_lock(&garfos[garfo_esq]);

    printf("Filosofo %d pegou o garfo esquerdo %d.\n\n", numfilosofo + 1, garfo_esq + 1);

    sleep(2); 

    printf("Filosofo %d está tentando pegar o garfo direito %d.\n\n", numfilosofo + 1, garfo_dir + 1);

    pthread_mutex_lock(&garfos[garfo_dir]);

    printf("Filosofo %d pegou o garfo direito %d.\n\n", numfilosofo + 1, garfo_dir + 1);

    sleep(2);

    printf("Filosofo %d está comendo...\n\n", numfilosofo + 1);

    sleep(1);

    pthread_mutex_unlock(&garfos[garfo_dir]);
    pthread_mutex_unlock(&garfos[garfo_esq]);
    
    return 0;
}

int main() {
    pthread_t threads[N];
    int numfilosofo[N];

    for (int i = 0; i < N; i++)
        pthread_mutex_init(&garfos[i], 0);

    for (int i = 0; i < N; i++) {
        numfilosofo[i] = i;
        pthread_create(&threads[i], 0, jantar_dos_filosofos, &numfilosofo[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(threads[i], NULL);

    return 0;
}