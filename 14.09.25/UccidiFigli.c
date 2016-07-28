/*Scrivere un programma che preso come parametro un file contenente un elenco di comandi (con I relativi parametri) li attivi
tutti in esecuzione concorrente e rimanga in attesa. Quando il primo termina, vengono terminati (con segnale SIGTERM) tutti
gli altri. (consiglio: puo' essere utile usare la mia libreria s2argv-execs)
esempio:
wta commands
il file commands contiene:
./ttest 40
./ttest 10
./ttest 20
lo script ./ttest contiene:
#!/bin/bash
echo waiting for $1 seconds
sleep $1
echo done $i
l'ouptut sara':
waiting for 40 seconds
waiting for 10 seconds
waiting for 20 seconds
done 10
e poi basta perche' gli altri processi verranno terminati.*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <unistd.h>

#include <signal.h>
#include <poll.h>
#include <sys/wait.h>


#define NUM_RIGHE 10


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

	char *buf=strdup(line);
	int argc=split(buf,NULL);
	char **command=calloc(argc+1,sizeof(char *));
	buf=strdup(line);
	split(buf,command);
	execvp(command[0], command);

}

int main (int argc, char *argv[]){

 	if (argc != 2){
 		fprintf(stderr, "Expected 1 parameter");
 		return(-1);
 	}

    char *buf;
    size_t bsize=BUFSIZ;

    FILE *stream;
 	int i=0, j, status;
    char *filename;
    char *array[NUM_RIGHE];
    pid_t pid, w;
    filename=argv[1];

    int fd[2]; //pipe fd for process sinc
	struct pollfd fds; //struct for poll


	//opening the pipe for pollin
	if((pipe(fd)) == -1){
		perror("Pipe");
		return(EXIT_FAILURE);
	}
	fds.fd = fd[0];
	fds.events=POLLIN;

    stream = fopen(filename, "r" );
    buf=malloc(bsize);

    while((j=getline(&buf,&bsize,stream))!=-1){

        strtok(buf,"\n");//getline salva nel buffer anche \n

        array[i]=malloc(j-1);

        strcpy(array[i], buf);

        i++;
    }

    for(j=0;j<i;j++) {

		switch (pid = fork()){

            case -1:
    			printf("fork fail\n");
    			return(EXIT_FAILURE);


            case 0: //child

    			poll(&fds,1,-1); //struct poll, size of fds array and -1 for block until interrupt call
    							//wait until all processes are ready

    			myexec(array[j]);

    			perror(array[j]);
    			return(EXIT_FAILURE);
                break;

            /*default:
                signal(SIGTERM, SIG_IGN);//ignoro la sigterm
*/
		}

	}



    //tell to all the processes to start
	write(fd[1], "g", 1);


    printf("ho detto ai tipi di partire\n" );

    wait(&status);
    if (w == -1) {
          perror("waitpid");
          exit(EXIT_FAILURE);
    }
    kill(-1*getpid(), SIGKILL);
    //kill(0, SIGTERM);

    return 0;

}
