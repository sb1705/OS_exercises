/*Si scriva un programma C chiamato “lineandir”. Il risultato del programma, stampato su standard output, deve essere un solo
numero intero: la somma del numero di caratteri presenti nelle n-me righe di tutti i file regolari, di testo, non nascosti (il primo
carattere deve essere diverso da punto) della directory corrente. */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

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

if(argc==1){
  printf("Inserire almeno un parametro\n");
  return -1;
}
else{

struct dirent *scan;
char *filename, fnc[BUFSIZ];
struct stat s;
FILE *stream;
long int size=0;

DIR *FD;
char *string, dirname[BUFSIZ];
int i, n, count, found;

char *buf;
size_t bsize=BUFSIZ;



strcpy(dirname, ".");

//open directory
FD = opendir (dirname);

if(FD==NULL){
	fprintf(stderr, "Error : Failed to open directory %s\n", strerror(errno));
	return -1;
}

n=atoi(argv[1]);
count=0;

//scan directory's files
while(scan=readdir(FD)){

    filename=scan->d_name;

    if(filename[0]==46){//il filename inizia con . (in ascii . = 46)
      continue;

    }
    strcpy(fnc, dirname);
    strcat(fnc, "/");
    strcat(fnc, filename);

    stat(fnc,&s);
    if(S_ISREG(s.st_mode)){
      size=s.st_size;
      if(size>n){
        stream = fopen(fnc, "r" );
        if(is_text(stream)){
          rewind(stream);
          buf=(char *)malloc(BUFSIZ + 1);
          found=0;
          for(i=0;i<n-1;i++){
            if(getline(&buf,&size,stream)==-1){
              found=1;
            }
          }
          if(!found) i=getline(&buf,&size,stream);
          if(i<0){
            continue;
          }else{
            count+=i-1;//non considero il \n quindi faccio -1
          }
          free(buf);

        }
        fclose(stream);
      }
    }
}
printf("%d\n",count );
return 0;
}
}
