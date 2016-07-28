/*Scrivere un programma C di nome filepipe che abbia come unico parametro il pathnae di un file di testo.
Questo file contiene due comandi con I rispettivi parametri, uno per riga.
Il programma deve mettere in esecuzione concorrente I due comandi in modo che l'output del primo venga fornito
come input del secondo usando una pipe.
Il programma deve terminare quando entrambi I comandi sono terminati.
Esempio: se il file ffff contiene:
ls -l
tac
il comando:
filepipe ffff
deve restituire lo stesso output del comando:
ls -l | tac*/




#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int split(char line[], char **command){

	int counter=0;
	char *token;

	strtok(line, "\n");
	token = strtok(line, " ");
	counter++;
	while( token != NULL )
	{
		if(command){
			command[counter-1] = token;
		}
		token = strtok(NULL, " ");
		counter++;
	}


	return counter;
}

void myexec (const char *line){
	//The strdup() function returns a pointer to a new string which is a duplicate of the string s. Memory for the new string is obtained with malloc(3), and can be freed with free(3). */
	char *buf/*=strdup(line)*/;

	int argc=split(buf,NULL);

	char **command=calloc(argc+1,sizeof(char *));//come malloc ma setta la mem allocata a 0

	buf=strdup(line);
	split(buf,command);
	execvp(command[0], command);

}

int main(int argc, char *argv[]) {
	
	if (argc != 2){
		fprintf(stderr, "Expected 1 parameter");
		return(EXIT_FAILURE);
	}
	FILE *f;
	int fd[2];  //fd[0] is set up for reading, fd[1] is set up for writing
	char *command = NULL;
	size_t n;
	
	//The fopen() function shall open the file whose pathname is the string pointed to by filename, and associates a stream with it. -> r stands for read only
	
	if((f = fopen(argv[1], "r")) == NULL){
		fprintf(stderr, "Cannot open the file");
		return(EXIT_FAILURE);
	}
	else{
		
		getline(&command, &n, f);
		
		if((pipe(fd)) == -1){
			perror("Pipe");
			return(EXIT_FAILURE);
		}
		else{
			
			
			switch (fork()) {
				case -1:
					
					fprintf(stderr, "Fork error");
					return(EXIT_FAILURE);
					
					break;
					
				case 0:
					
					close(fd[0]);
					
					//The dup() system call creates a copy of the file descriptor oldfd,useing the file descriptor number specified in newfd
					dup2(fd[1], STDOUT_FILENO); //redirect STDOUT to write to fd[1]->fd[0]
					myexec(command);
					return(EXIT_FAILURE); //???
					
				default:
					
					close(fd[1]);
					dup2(fd[0], STDIN_FILENO);	//redirect STDIN to read from fd[0]<-fd[1]
					wait(NULL);	//wait for child to terminate
					lseek (fd[1], 0, SEEK_SET);	//reposition STDOUT read offset to the start
					free(command);
					command = NULL;
					getline(&command, &n, f);	//get second command
					myexec(command);
					return(EXIT_FAILURE);
			}
			
		}
		
		
		
	}
	
	return 0;
}
