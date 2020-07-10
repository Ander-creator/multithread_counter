 /*
  * nome: Anderson Santos Silva
  * RA: 166191
  * Laboratório 5 - EA876
  * Objetivo: implementar um reconhecedor de números primos em que 
  * o reconhecimento de cada número recebido será feito por um thread
  * diferente, podendo haver até 4 threads ao mesmo tempo.
  */
  
  /*inclusão das bibliotecas*/
  #include <stdio.h>
  #include <stdlib.h>
  #include <time.h>
  #include <pthread.h>
  #include <unistd.h>
  
  /*trava que impedirá de ter concorrencia*/
  pthread_mutex_t trava;
	/* numeros é o vetor que armazenará cada número recebido*/
  unsigned long long int  numeros[1000];
  /*n_primos vai registrar o numero de primos
    n_numeros regista o quat de numeros recebidos
    paralelas registra quantas threads estão funcionando em paralelo
  */
  int n_primos = 0;
  int n_numeros= 0;
  int paralelas = 0;
  /*função de threads*/
  void* primos(void *arg){
    int* N = (int*)arg;
    int k = (*N);
    /*travando enquanto reconhece o número.*/
    pthread_mutex_lock(&trava);

    if(numeros[k]!=2 && numeros[k]!=3 && numeros[k]!=5 && numeros[k]!=7){   
      if(numeros[k]<=1);
      else if(numeros[k]%2==0);
      else if(numeros[k]%3==0);
      else if(numeros[k]%5==0);
      else if(numeros[k]%7==0);
      else n_primos++;
    }
    else n_primos++;
    paralelas--;
    pthread_mutex_unlock(&trava);
    return NULL;
  }
  
  int main(int argc, char **argv){
    char c;
    
    /*bloco de leitura dos números*/ 
    while(c!='\n'){
      scanf("%lld", &numeros[n_numeros]);
      scanf("%c", &c);
      n_numeros++;
    }
    
    /*vetor threads*/
    pthread_t threads[n_numeros];
    int thread_args[n_numeros];
    
    /*for que inicia os threads*/
    for (int j = 0; j < n_numeros; j++) {
      thread_args[j] = j;
      pthread_create(&(threads[j]), NULL, primos, &(thread_args[j]));
      paralelas++;
      while(paralelas == 3);
    }
  
    /* Esperando threads terminarem! */
    for (int i = 0; i < n_numeros; i++) {
      pthread_join(threads[i], NULL);
    }
    
    /*printando a quantidade de primos analizadas*/
    printf("%d\n",n_primos);
    
    return 0;
  }

