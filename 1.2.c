#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 5

pthread_mutex_t garfos[N];

void* pensando(void* num) {
    int numfilosofo = *(int*)num;
    printf("Filósofo %d está pensando...\n\n", numfilosofo + 1);
    sleep(1);
    return NULL;
}

void* jantar_dos_filosofos(void* num) {
    int numfilosofo = *(int*)num;

    int garfo_esq = numfilosofo;
    int garfo_dir = (numfilosofo + 1) % N;

    printf("Filósofo %d está com fome, ele quer os garfos %d e %d.\n\n", numfilosofo + 1, garfo_esq + 1, garfo_dir + 1);

    printf("Filósofo %d está tentando pegar o garfo esquerdo %d.\n\n", numfilosofo + 1, garfo_esq + 1);
    pthread_mutex_lock(&garfos[garfo_esq]);
    printf("Filósofo %d pegou o garfo esquerdo %d.\n\n", numfilosofo + 1, garfo_esq + 1);

    sleep(1);

    printf("Filósofo %d está tentando pegar o garfo direito %d.\n\n", numfilosofo + 1, garfo_dir + 1);
    pthread_mutex_lock(&garfos[garfo_dir]);
    printf("Filósofo %d pegou o garfo direito %d.\n\n", numfilosofo + 1, garfo_dir + 1);

    printf("Filósofo %d está comendo...\n\n", numfilosofo + 1);
    sleep(2);

    pthread_mutex_unlock(&garfos[garfo_dir]);
    pthread_mutex_unlock(&garfos[garfo_esq]);

    printf("Filósofo %d terminou de comer e soltou os garfos.\n\n", numfilosofo + 1);

    return 0;
}

int main() {
    pthread_t threads[N];
    int numfilosofos[N];

    for (int i = 0; i < N; i++) {
        pthread_mutex_init(&garfos[i], 0);
    }

    for (int i = 0; i < N; i++) {
        numfilosofos[i] = i;
    }


    printf("-- Grupo 1: Filósofos 1 e 3 --\n\n");

    for (int i = 0; i < N; i++) {
        if (i == 0 || i == 2) {
            continue;
        } else {
            pthread_create(&threads[i], 0, pensando, &numfilosofos[i]);
        }   
    }

    usleep(200);

    for (int i = 0; i < N; i++) {
        if (i == 0 || i == 2) {
            pthread_create(&threads[i], 0, jantar_dos_filosofos, &numfilosofos[i]);  
        } else {
            continue;
        }
          
    }

    pthread_join(threads[0], 0);
    pthread_join(threads[2], 0);


    printf("-- Grupo 2: Filósofos 2 e 4 --\n\n");

    for (int i = 0; i < N; i++) {
        if (i == 1 || i == 3) {
            continue;
        } else {
            pthread_create(&threads[i], 0, pensando, &numfilosofos[i]);
        }   
    }

    usleep(200);

    for (int i = 0; i < N; i++) {
        if (i == 1 || i == 3) {
            pthread_create(&threads[i], 0, jantar_dos_filosofos, &numfilosofos[i]);  
        } else {
            continue;
        }
          
    }

    pthread_join(threads[1], 0);
    pthread_join(threads[3], 0);


    printf("-- Grupo 3: Filósofo 5 --\n\n");

    for (int i = 0; i < N; i++) {
        if (i == 4) {
            continue;
        } else {
            pthread_create(&threads[i], 0, pensando, &numfilosofos[i]);
        }   
    }

    usleep(200);

    for (int i = 0; i < N; i++) {
        if (i == 4) {
            pthread_create(&threads[i], 0, jantar_dos_filosofos, &numfilosofos[i]);  
        } else {
            continue;
        }
          
    }

    pthread_join(threads[4], 0);

    return 0;
}