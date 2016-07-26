/*Scrivere un programma testeventalt che faccia uso di due descrittori aperti con la system call eventfd.
In particolare il programma deve eseguire una fork e fare in modo che i due processi padre e figlio leggano alternativamente da
standard input e riportino in output quanto letto (indicando quale processo sta facendo l'azione)*/



/*

FUNZIONA! Ma stampa solo stringhe lunghe <=8 char perchè eventfd crea un oggetto contenente
un intero senza segno a 64 bit, quindi più di così non ci sta.
Probabilmente si potrebbero fare più passate per leggere stringhe più lunghe, mandandole a gruppi di
8 byte nel "buffer" dell'eventfd e leggendole di volta in volta,
ma per ora non voglio perdere altro tempo su quest'es.


*/

#include <sys/eventfd.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>             /* Definition of uint64_t */
#include <signal.h>
#include <string.h>

#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char *argv[]){

int pid;
int efd = eventfd(0, 0);// il padre ci legge e il figlio ci scrive
int efd2 = eventfd(0, 0); // viceversa

int num_letti;

char string[1024], string2[1024];



if (efd == -1)
    handle_error("eventfd");
if (efd2 == -1)
    handle_error("eventfd");


memset(string, 0, sizeof(string));
memset(string2, 0, sizeof(string2));

printf("Inserire qualcosa\n");
num_letti=scanf("%s",string);
write(efd, &string, sizeof(string)); //riempio il primo eventfd così che il padre possa leggere

switch (pid=fork()) {

case 0: //siamo nel figlio
        while(1){

                read(efd2, &string2, sizeof(string2)); //leggo quello che mi ha scritto il babbo

                printf("Figlio : %s\n", string2); //stampo

                memset(string2, 0, sizeof(string2)); //pulisco la memoria

                scanf("%s",string); //leggo la prossima stringa

                write(efd, &string, sizeof(string)); //scrivo per mio padre

        }
        break;

case -1:
        handle_error("fork");
        break;

default:
        while(num_letti){

                read(efd, &string, sizeof(string)); //aspetta di leggere da efd
                printf("Padre : %s\n", string);

                memset(string, 0, sizeof(string)); //pulisco la memoria

                scanf("%s",string2); // leggo la prossima stringa

                write(efd2, &string2, sizeof(string2)); //la scrivo così il figlio può leggerla

                //num_letti=1;

        }
  }
}
