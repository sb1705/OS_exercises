/* Scrivere un programma che abbia come primo parametro
un numero di segnale e come successivi parametri un comando coi rispettivi argomenti.
Ad esempio
sigstart 10 xclock -update 1
sigstart deve rimanere in attesa e lanciare una istanza del comando ogni volta che riceve un segnale del tipo
indicato (in questo caso SIGUSR1=10).*/


#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <signal.h>

#define COMMAND_SIZE 1024

char *myargv[COMMAND_SIZE];

void handler (int sig){
	
	
	printf("Ricevuto!\n");

	int j=0;
		while(myargv[j]!=NULL){
			printf("Argv[%d] : %s", j, myargv[j]);
			j++;
		}

	int pid;
	if ( (pid = fork()) == -1) {
		fprintf(stderr, "fork error");
	}

	if (pid == 0) {	//child
		printf("Sono nel figlio\n");
		execvp(myargv[0], myargv);
		fprintf(stderr, "exec error");

	} 
	return;
}


int main(int argc, char *argv[]){
	
	
	if (argc < 2){
		fprintf(stderr, "Expected at least 2 parameters");
		return(-1);
	}
	
	int j=0,i;
	int sig=atoi(argv[1]);
	
	struct sigaction signalStruct;
	

	printf("That's my pid: %d, so sig me maybe!\n", getpid());

	
	for ( i =2; i<argc;i++){
		
		myargv[i-2]=argv[i];
		
		j++;
	}
	myargv[j]=NULL;

	printf("Aspetto il segnale n° %d \n", sig);
	signal(sig, handler);
	i = pause(); // si mette in attesa di un segnale


	return 0;
}
