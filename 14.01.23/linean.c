/*Scrivere un programma in C “linean” che prenda come parametro il pathname di un file e un numero intero (che chiameremo
n). Il programma deve stampare come output il numero di caratteri presenti nella n-ma riga del file se il file e' un file regolare
di testo, non deve stampare nulla negli altri casi. Un file viene considerato di testo se tutti i suoi byte hanno valori compresi nel
range 1-127. Per controllare se il file e' “regolare” usare la system call lstat*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <unistd.h>
//#include <time.h>
//#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>

#define SIZE 1024

int is_text(FILE *stream){
  int c;
  while((c=fgetc(stream)) != -1){
    if((c>127)||(c<0)){
      return 0;
    }
  }
  return 1;

}

int main(int argc, char *argv[]){
int i, n, count;
struct stat s;
FILE *stream, *new;
char *buf;
size_t size=BUFSIZ;


i=lstat(argv[1], &s);
if(i!=0){
  fprintf(stderr, "Error : stat - %s\n", strerror(errno));
	return -1;
}

if(S_ISREG(s.st_mode)){
  stream=fopen(argv[1], "r");
  if(stream==NULL){
    fprintf(stderr, "Error : open - %s\n", strerror(errno));
    return -1;
  }
  if(is_text(stream)){
    rewind(stream);
    n=atoi(argv[2]);
    count=0;
    buf=(char *)malloc(BUFSIZ + 1);
    for(i=0;i<n;i++){
      count=getline(&buf,&size,stream);
      if(count == -1) {
        printf("Il file ha meno di n linee\n");
        exit(1);
      }
      count--;//non conto anche \n come carattere
    }
    free(buf);
    buf=NULL;
    printf("%d\n",count );
  }else{
    printf("Non è un file di testo\n" );
  }

  }else{

    printf("Non è un file regolare\n" );
  }

  return 0;
  }
