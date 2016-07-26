/*Scrivere un programma testeventfd che faccia uso della system call eventfd.
In particolare il programma deve eseguire una fork, quando l'utente digita un numero letto dal processo padre, il processo
figlio deve stampare un numero uguale di x. (negli esempi e' riportato in grassetto cio' che l'utente digita).
$
testeventfd
3
x
x
x
2
x
x
*/


#include <sys/eventfd.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>             /* Definition of uint64_t */
#include <signal.h>


#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char *argv[]){

int pid;
int efd = eventfd(0, 0);
uint64_t u=1;
int i=0;



if (efd == -1)
    handle_error("eventfd");


switch (pid=fork()) {

case 0: //siamo nei figli
        while(1){

            read(efd, &u, sizeof(uint64_t));
            for(i=0; i<u; i++)  printf("x\n");

        }
        break;

case -1:
        handle_error("fork");
        break;

default:
        while(u){ //quando legge 0 il programma termina

            scanf("%lu", &u );
            write(efd, &u, sizeof(uint64_t));
        }
       break;

  }
}
