TDE 3

Aluno: Guilherme Selig
Disciplina: Performance de Sistemas de Computação

Link para o Vídeo de 10 Minutos (Explicação):
https://youtu.be/YV9ad33dfbU

Lembrete: Com a autorização do professor, todos os códigos foram feitos na linguagem C, ao invés de Java. Os códigos por exemplo da parte dois, foram traduzidos para a linguagem C para poder fazer o exercício.

Parte 1: O Jantar dos Filósofos (Deadlock)

1.1:
	•	Código: 1.1.c

O primeiro código mostra onde 5 filósofos tentam pegar, em ordem, o garfo da esquerda e depois o garfo da direita.
Análise do Impasse:
O programa trava (entra em deadlock) pois as quatro Condições de Coffman são satisfeitas:
	1	Exclusão Mútua: Os garfos são pthread_mutex_t, apenas um filósofo pode usá-lo por vez.
	2	Manter e Esperar Cada filósofo segura o garfo da esquerda (lock) enquanto espera pelo garfo da direita.
	3	Não Preempção: O sistema operacional não pode tomar o garfo de um filósofo à força.
	4	Espera Circular: O Filósofo 0 espera o 1, que espera o 2, que espera o 3, que espera o 4, que, por sua vez, espera o 0.

1.2:
	•	Código: 1.2.c

A solução usa a estratégia do Árbitro (Garçom). A main atua como o garçom, organizando quem pode comer em cada rodada, visando que filósofos vizinhos nunca compitam pelos mesmos recursos simultaneamente.
Análise da Solução:
Este protocolo quebra a condição de Espera Circular. Como o garçom só permite que filósofos que não sejam vizinhos (ex: 1 e 3) comam ao mesmo tempo, o círculo de dependência (0 espera 1, 1 espera 2, …) é impossível de se formar.

Pseudocódigo do Protocolo Árbitro

Filósofos 0-4 (mapeados para 1-5 no PRINT)
Garfos 0-4 

INÍCIO

Rodada 1: Ímpares comem

PRINT "-- Grupo 1: Filósofos 1 e 3 --" 

INICIAR THREAD(Filósofo 0, AÇÃO = COMER) 
INICIAR THREAD(Filósofo 2, AÇÃO = COMER) 
INICIAR THREAD(Filósofo 1, AÇÃO = PENSAR) 
INICIAR THREAD(Filósofo 3, AÇÃO = PENSAR) 
INICIAR THREAD(Filósofo 4, AÇÃO = PENSAR) 
ESPERAR THREAD(0) e THREAD(2) TERMINAREM.

Rodada 2: Pares comem 

PRINT "-- Grupo 2: Filósofos 2 e 4 --" 

INICIAR THREAD(Filósofo 1, AÇÃO = COMER) 
INICIAR THREAD(Filósofo 3, AÇÃO = COMER) 
INICIAR THREAD(Filósofo 0, AÇÃO = PENSAR) 
INICIAR THREAD(Filósofo 2, AÇÃO = PENSAR) 
INICIAR THREAD(Filósofo 4, AÇÃO = PENSAR) 
ESPERAR THREAD(1) e THREAD(3) TERMINAREM.

Rodada 3: Último come 

PRINT "-- Grupo 3: Filósofo 5 --" 

INICIAR THREAD(Filósofo 4, AÇÃO = COMER) 
INICIAR THREAD(Filósofo 0, AÇÃO = PENSAR) 
INICIAR THREAD(Filósofo 1, AÇÃO = PENSAR) 
INICIAR THREAD(Filósofo 2, AÇÃO = PENSAR) 
INICIAR THREAD(Filósofo 3, AÇÃO = PENSAR) 
ESPERAR THREAD(4) TERMINAR. 


FIM

Parte 2: Contador Concorrente (Condição de Corrida)

2.1:
	•	Código: 2.1.c

O código lança 8 threads, cada uma executando 250.000 incrementos usando um “for”. O valor esperado é 2.000.000.

Análise do Problema:
O código sem sincronização falha em produzir o resultado correto. O valor obtido é consistentemente menor que o esperado.
Exemplo:
Valor Esperado = 2.000.000
Valor Obtido = 1.994.066
Incrementos perdidos = 5.934

Isso ocorre devido à Condição de Corrida. Múltiplas threads leem o mesmo valor antes que outras possam salvá-lo, resultando em perda de incrementos.

2.2:
	•	Código: 2.2.c

Análise da Solução (e Descoberta no macOS):
	1	Foi implementada a solução com <semaphore.h> (sem_init(..., 1)). No entanto, testes no macOS (Apple Silicon) mostraram que esta implementação ainda perdia incrementos. O log de compilação apontou que sem_init é deprecated (obsoleto) no macOS e não é confiável para este tipo de sincronização entre threads.
	2	Para testar, o código foi rodado no site onlinegdb.com.

Parte 3: Deadlock Simples (A/B)

3.1:
	•	Código: 3.1.c

O código implementa o cenário exato do TDE:
	•	Thread 1: lock(A) -> sleep(1) -> lock(B)
	•	Thread 2: lock(B) -> sleep(1) -> lock(A)

Análise do Problema:
O programa trava (deadlock) assim que ambas as threads pegam seus primeiros locks. Os logs evidenciam a Espera Circular:
	•	A Thread 1 segura A e espera indefinidamente pela Thread 2 (para soltar B).
	•	A Thread 2 segura B e espera indefinidamente pela Thread 1 (para soltar A).

3.2:
	•	Código: 3.2.c

A correção segue a estratégia de Hierarquia de Recursos. Ambas as threads são forçadas a adquirir os locks na mesma ordem (A, depois B).
	•	   •	Thread 1: lock(A) -> sleep(1) -> lock(B)
	•	Thread 2: lock(A) -> sleep(1) -> lock(B)

Análise da Solução:
O programa agora executa sem deadlock visto que a Espera Circular é quebrada. A Thread 2 simplesmente "espera" na fila pelo Lock A (se a Thread 1 o tiver).
