/*
Scrivere un programma C di nome lanciaxp che esegua in modo concorrente tutti i file eseguibili con nome palindromo nella
directory corrente.
Se la directory corrente contiene i file:
$ ls -l
total 28
-rwxr-xr-x 1 renzo renzo   21 Feb 10 11:10 anna
-rwxr-xr-x 1 renzo renzo 4851 Feb 10 11:12 bib
-rw-r--r-- 1 renzo renzo   82 Feb 10 11:12 bib.c
-rwxr-xr-x 1 renzo renzo   21 Feb 10 11:10 emma
-rw-r--r-- 1 renzo renzo    5 Feb 10 11:13 erre
-rwxr-xr-x 1 renzo renzo   21 Feb 10 11:10 laura

lanciaxp deve  eseguire file anna, emma e bib. Al contrario non devono essere esguiti laura (il nome non e' palindromo), bib.c e
erre(perche' non sono eseguibili). Lanciaxp termina quando tutti i processi attivati sono terminati.*/

#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <poll.h>

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

int palindroma(char *s){
    char *inizio;
    char *fine;
    inizio=s;
    fine=s+strlen(s)-1;
    while(fine>inizio){
        if(*inizio==*fine){

            inizio++;
            fine--;
            continue;
        }
        else return 0;
    }
    return 1;
}

int eseguibile(char *file){
    struct stat sb;
    if (stat(file, &sb) == 0 && sb.st_mode & S_IXUSR){
        return 1;
    }
    else{
        return 0;
    }
}


int main(int argc, char *argv[]){
  DIR           *d;
  struct dirent *dir;
  char *path;
  char args[1];
  int fd[2]; //pipe fd for process sinc


  list lista = NULL;
  //    char input[254];
  int pid;
  //int count=0;
  int status;

  struct pollfd fds; //struct for poll

  d = opendir(".");
  if(d==NULL){
      printf ("Non riesco ad aprire la directory corrente");
      exit(1);

  }

  //opening the pipe for pollin
  if((pipe(fd)) == -1){
      perror("Pipe");
      return(EXIT_FAILURE);
  }
  fds.fd = fd[0];
  fds.events=POLLIN;




//    fgets(input,254,stdin);

    while ((dir = readdir(d)) != NULL) {
        switch (pid=fork()) {
            case -1:
                printf("fork fail\n");
                return(EXIT_FAILURE);
                break;
            case 0:
                if(strncmp(dir->d_name, ".", 1)){//ignora i file nascosti
                    if(eseguibile(dir->d_name)&&palindroma(dir->d_name)){
                        //printf("%s è eseguibile\n", dir->d_name);
                        path=malloc(strlen(dir->d_name)+3);
                        strcpy(path, "./");
                        strcat(path, dir->d_name);
                        printf("%s è il path \n", path);
                        poll(&fds,1,-1); //struct poll, size of fds array and -1 for block until interrupt call
                            //wait until all processes are ready

                        myexec(path);

                        perror(path);
                        return(EXIT_FAILURE);
                    }
                }
        }//end switch

    }
  write(fd[1], "g", 1);



return(0);
}
