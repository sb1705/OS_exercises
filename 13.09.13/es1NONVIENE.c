/*Lo scopo del programma che dovrete scrivere e' di confrontare fra loro i file di una directory, se ne trovate due (o piu') che
hanno lo stesso contenuto dovete unificarli. Alla fine del processo l'elenco dei file della directory deve rimanere invariato ma
i nomi dei file che avevano lo stesso contenuto devono essere link fisici che indicano lo stesso file.
In questo esercizio si richiede che l'intero contenuto dei file venga confrontato. */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>


//controlla se hanno stessa dim o stesso inode
int checkStat(const char *filename1,const char *filename2) {
	struct stat st1,st2;

	if ((stat(filename1, &st1) == 0) && (stat(filename2, &st2) == 0)){
		if(st1.st_size != st2.st_size)return 1;
		if(st1.st_ino == st2.st_ino)return 1;
	}

	return 0;
}

//controlla se i file hanno lo stesso contenuto
int sono_uguali(char *fnc, char*fnc2){
  FILE *fp1, *fp2;
  char ch1, ch2;
  fp1 = fopen(fnc, "r");
  if (fp1 == NULL) {
     printf("Cannot open %s for reading ", fnc);
     exit(1);
  }
  fp2 = fopen(fnc2, "r");
  if (fp2 == NULL) {
    printf("Cannot open %s for reading ", fnc2);
    exit(1);
  }
  ch1 = getc(fp1);
  ch2 = getc(fp2);

  while ((ch1 != EOF) && (ch2 != EOF) && (ch1 == ch2)) {
    ch1 = getc(fp1);
    ch2 = getc(fp2);
  }

 if (ch1 == ch2){
   fclose(fp1);
   fclose(fp2);
   printf("Files %s and %s are identical \n", fnc, fnc2);
   return 1;
 }else{
   fclose(fp1);
   fclose(fp2);
   printf("Files %s and %s are not identical \n", fnc, fnc2);
   return 0;
 }
}


int main(int argc, char *argv[]) {
  // FILE *fp1, *fp2;
   int ch1, ch2;
  // char fname1[40], fname2[40];
   struct dirent *scan, *scan2;
   char *filename, *filename2, fnc[BUFSIZ], fnc2[BUFSIZ];
   struct stat s;
   FILE *stream;
   long int size=0;
   DIR *FD, *FD2;
   char *string, dirname[BUFSIZ];
   int i, count;
   char *buf;
   size_t bsize=BUFSIZ;


   strcpy(dirname, argv[1]);
   //open directory
   FD = opendir (dirname);

   if(FD==NULL){
   	fprintf(stderr, "Error : Failed to open directory %s\n", strerror(errno));
   	return -1;
   }

   count=0;
   //scan directory's files
   while(scan=readdir(FD)){
     if(!strncmp(scan->d_name,".",1)) continue;
     filename=scan->d_name;
     strcpy(fnc, dirname);
     strcat(fnc, "/");
     strcat(fnc, filename);
     printf("Filename: %s  \n", filename);
       while(scan2=readdir(FD2)){
         if(!strncmp(scan2->d_name,".",1)) continue; //file nascosto
         if(!strcmp(scan->d_name,scan2->d_name)) continue;	//stesso file
         if (checkStat(filename,filename2))continue;
         filename2=scan2->d_name;
         strcpy(fnc2, dirname);
         strcat(fnc2, "/");
         strcat(fnc2, filename2);
         printf("Filename2: %s  \n", filename2);

         if(sono_uguali(fnc,fnc2)){
           printf("File con lo stesso contenuto! %s, %s\n", filename,filename2);
           link(filename,filename2);
         }
       }
      rewinddir(FD2);
     }

return (0);
}
