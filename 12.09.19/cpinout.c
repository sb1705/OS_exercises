/*Scrivere un programma cpinout che copi i dati letti dal file standard input nel file standard output e che:
–
al ricevimento del segnale SIGUSR1 indichi sul file standard error quanti byte sono stati copiati al momento attuale
–
mostri la propria attivita' sovrascrivendo un carattere (stampando –, \, |, / e poi ritornando a – per dare l'iimpressione
di un'asta che gira. 
Provate il programma con un comando come:
cat /dev/zero | ./cpinout | cat >/dev/null
da un altro terminale poi mandate segnali con kill -USR1 xxxx, dove xxx e' il umero del processo cpinout

*/


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
 
#define BUFSIZE 1024
 
long int n = 0;
 
void handler(int sig_num){
 
	signal(SIGUSR1, handler);
	fprintf(stderr, "\n%ld Bytes copied until now\n", n);
 
}
 
int main(){
 
	int nread, nwritten,
	    i = 0;
	char buffer[BUFSIZE],
	     cool_gui[] = "-\\|/";
 
	signal(SIGUSR1, handler);
	fprintf(stderr, "Copying   ");
 
	while( (nread = read(STDIN_FILENO, buffer, BUFSIZE)) > 0 ){
		if(nread < 0){
			perror("Read error: ");
			exit(EXIT_FAILURE);
		}
 
		nwritten = write(STDOUT_FILENO, buffer, nread);
                if(nwritten < 0){
                        perror("Write error: ");
                        exit(EXIT_FAILURE);
                }
 
		n += nwritten;
		fprintf(stderr, "\b\b%c ",cool_gui[i%4]);
		(i == INT_MAX) ? (i=0) : (i++); 	
	}
 
	fprintf(stderr, "\nDone\n");
 
	return EXIT_SUCCESS;
 
}
