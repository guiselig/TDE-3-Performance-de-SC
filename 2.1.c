#include <stdio.h>
#include <pthread.h>
#include <locale.h> //Usando para os números ficarem melhores

int T = 8;
int M = 250000;
int count = 0;

void* counts() {
    for (int i = 0; i < M; i++) {
        count++; 
    }
    return 0;
}

int main() {
    
    setlocale(LC_NUMERIC, "pt_BR.UTF-8");//Função para colocar os pontos nas centenas

    pthread_t threads[T];
    int valor_esperado = T * M;

    printf("\nIniciando %d threads\nIncrementos de %'d\n\n", T, M);
    
    for (int i = 0; i < T; i++) {
        pthread_create(&threads[i], 0, counts, 0);
    }

    for (int i = 0; i < T; i++) {
        pthread_join(threads[i], 0);
    }

    printf("Valor Esperado = %'d\n", valor_esperado);
    printf("Valor Obtido = %'d\n", count);
    printf("Incrementos perdidos = %'d\n\n", valor_esperado - count);

    return 0;
}