/*Si scriva un programma C chiamato “colonnandir”. Il risultato del programma, stampato su standard output, deve essere un
solo numero intero: la somma del numero di caratteri presenti nelle n-me colonne di tutti i file regolari, di testo, non nascosti (il
primo carattere deve essere diverso da punto) della directory passata come parametro, ovvero della directory corrente se
colonnandir viene lanciato senza specificare parametri.*/

//  NB: ho deciso di considerare anche \n come carattere se trovato nella n-esima colonna

// 1° parametro = n
// 2° parametro = nome_directory (opzionale)

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
int i, n, count;

char *buf;
size_t bsize=BUFSIZ;



strcpy(dirname, ".");


if(argc>2){
  strcpy(dirname, argv[2]);
}




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
          while((i=getline(&buf,&bsize,stream))!=-1){
            if(i>=n){
              count++; //considero anche lo spazio come carattere
            }
            else{
              continue;
            }
          }
          free(buf);

        }/*else{
          printf("%s : non è un file di testo\n", fnc );
        }*/
        fclose(stream);
      }
    }/*else{
        printf("%s : non è un file regolare\n", fnc );
      }*/
}
printf("%d\n",count );
return 0;
}
}
