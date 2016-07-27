/*La scelta di quali file eseguire deve essere selezionabile con parametri:
-p: palindromo
-b: script (i primi due caratteri del file contengono la stringa “!#”).
-c: in modo concorrente. Se -c non e' specificato viene lanciato un programma alla volta e si attende la terminazione
prima di attivare il successivo
Quindi:
lanciax -p -c
ha lo stesso effetto del programma dell'esercizio 1
lanciax
lancia tutti gli eseguibili uno dopo l'altro
lanciax -b -p
esegue tutti gli script che hanno il nome palindromo (non il bib dell'esempio sopra), uno alla volta.

  NON FUNZIONA
*/


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

int isScript(char *file){
    FILE *fp;
    fp = fopen(file, "r");
	if (fgetc(fp)==35){//#
        if(fgetc(fp)==33){// !
            fclose(fp);
            return 1;
        }

    }
    fclose(fp);
    return 0;
}

void esegui(char *filename, int c, struct pollfd fds){
	int pid;
	char *path;
	switch (pid=fork()) {
		case -1:
			printf("fork fail\n");
			return(EXIT_FAILURE);
			break;
		case 0:
			path=malloc(strlen(filename)+3);
			strcpy(path, "./");
			strcat(path, filename);


			if(c==1)	poll(&fds,1,-1); //struct poll, size of fds array and -1 for block until interrupt call
				//wait until all processes are ready

			myexec(path);

			perror(path);
			return(EXIT_FAILURE);
	}
}

int main(int argc, char *argv[]){
  DIR           *d;
  struct dirent *dir;
  //char *path;
  char args[1];
  int fd[2]; //pipe fd for process sinc
  int i, c=0, p=0, b=0;
  //list lista = NULL;
  //int pid;
  int status;
  struct pollfd fds; //struct for poll

  for(i=1; i<argc; i++){

      if(!strcmp(argv[i],"-c")){
          c=1;
      }else if(!strcmp(argv[i],"-b")){
          b=1;
      }else if(!strcmp(argv[i],"-p")){
          p=1;
      }else{
          printf("PARAMETRO NON VALIDO\n");
          exit(EXIT_FAILURE);
      }

  }




  d = opendir(".");
  if(d==NULL){
      printf ("Non riesco ad aprire la directory corrente");
      exit(1);

  }

  if(c==1){
	  //opening the pipe for pollin
	  if((pipe(fd)) == -1){
	      perror("Pipe");
	      return(EXIT_FAILURE);
	  }
	  fds.fd = fd[0];
	  fds.events=POLLIN;
  }




//    fgets(input,254,stdin);
	printf("Sto partendo\n");
    while ((dir = readdir(d)) != NULL) {
		printf("Analizzo : %s\n", dir->d_name);

		if(!(strncmp(dir->d_name, ".", 1))||(strcmp(dir->d_name, "lanciax"))){//ignora i file nascosti
			if(eseguibile(dir->d_name)){
				printf("\n %s è eseguibile \n", dir->d_name);
				if(((p==1)&&palindroma(dir->d_name))||((b==1)&&isScript(dir->d_name))){
					printf("%s è palindroma o script \n", dir->d_name);
					esegui(dir->d_name, c, fds);

                    }
                }
        }
		printf("Ho finito di analizzare : %s\n", dir->d_name);
    }
	printf("Chiuso il while \n");
	if(c==1)  write(fd[1], "g", 1);

	return(0);
}
