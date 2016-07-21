/*Myuntar fa l'operazione inversa:
myuntar ddd.mytar newddd
crea la directory indicata come secondo parametro e, in essa, tutti i file registrati in ddd.mytar
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stddef.h>


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

int main(int argc, char *argv[]){

char *dirname;
DIR *D_FD;
char filename[BUFSIZ], f[BUFSIZ], *buf;
struct stat s;
FILE *stream, *new;
int file_size;

int l=0, i, finito=0;

//create directory
if (stat(argv[2], &s) == -1) {
  if(mkdir(argv[2], 0700) == -1){
    fprintf(stderr, "Error : Cannot create directory \n");
    return -1;
  }
}
opendir(argv[1]);

stream=fopen(argv[1], "r");

//f prende tutta la riga, f[i] prende il puntatore al carattere in ascii
while(1){//f legge riga per riga
    buf=fgets(f, BUFSIZ, stream);//nome file
    i=0;
    while(buf[i]!=0)printf("%d",buf[i]); //filename[i]=buf[i];
    if(f[0]==10){

      printf("Sono arrivato alla fine\n");
      break;
    }
    l=atoi(fgets(f, BUFSIZ, stream));//lunghezza file
      printf("filename: %s\n", filename);
      printf("size: %i\n", l);
		new=fopen(filename, "w");

    if (stream == NULL) {
          puts("Not able to create this file");
          exit(1);
    }

    i=0;
    while (i<l){
         char a = fgetc(stream);
         fputc(a, new);
    		 i++;
      }

		fclose(new);
 }

 return 0;
}
