/*fare un programma che consenta di recuperare un file dal formato generato dall'esercizio1.
demytx file1 ddd.tx
deve creare il file 'file1' recuperando il contenuto dal file generato da myt2 dell'esercizio1*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stddef.h>



int main(int argc, char *argv[]){

char a;
char *filename, f[BUFSIZ];
struct stat s;
FILE *stream, *new;
int file_size;
char buf[BUFSIZ];
int l=0, ltot=0;

//open directory
filename=argv[1];

stream=fopen(argv[2], "r");
if(stream==NULL){
  puts("cannot open this file");
  exit(1);
}

strcat(filename,"\n");

//scan directory's files

//f prende tutta la riga, f[i] prende il puntatore al carattere in ascii
while(fgets(f, BUFSIZ, stream)){//f legge riga per riga
    if(!strcmp(f+strlen(f)-strlen(filename), filename)){
      l=atoi(f); //l ha la lunghezza del filename
    }
   //sommo la lunghezza dei file che precedono quello che sto cercando
   if(l==0){
	strcat(buf,strtok(f," "));
   }
   ltot+=atoi(buf);
   strcpy(buf,"");//svuoto il buffer

  if(f[0]==10){//se troviamo come primo carattere un \n
	break;
  }
 }
filename=strtok(filename,"\n");
new=fopen(filename,"w");
if (new == NULL) {
      puts("Not able to open this file");
      fclose(stream);
      exit(1);
}


for(int i=0; i<=ltot; i++){
      fgetc(stream);
}

ltot=0;
while (ltot<l){
     a = fgetc(stream);
     fputc(a, new);
     ltot++;
  }

 fclose(stream);
 fclose(new);
 return 0;
}
