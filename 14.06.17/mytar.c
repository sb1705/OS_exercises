/*Mytar prende come parametro il nome di una directory e il nome di un file:
mytar ddd ddd.mytar
mytar crea il file indicato come secondo parametro e registra in esso tutti i file regolari presenti nella directory (ddd
nell'esempio). Ogni file e' registrato nel secondo il seguente formato:
nome del file (stringa ASCII terminata da un byte 0)
lunghezza del file (stringa ASCII terminata da 0, la lunghezza e' registrata come stringa in rappresentazione in base 10
per non avere problemi di endianess e di ampiezza dei campi)
contenuto del file (un numero di byte corrispondente alla lunghezza indicata sopra)*/

#define _GNU_SOURCE   //need for asprintf
#define MAX_DIM BUFSIZ

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>





int main(int argc, char *argv[]){
DIR *FD;
struct dirent *scan;
char *filename, fnc[MAX_DIM], buf[MAX_DIM];
struct stat s;
FILE *stream, *F_FD;
long int size=0;
int readbytes;
char *string;
//open directory
FD = opendir (argv[1]);

if(FD==NULL){
	fprintf(stderr, "Error : Failed to open directory %s\n", strerror(errno));
	return -1;
}

stream=fopen(argv[2], "w");
//scan directory's files
while(scan=readdir(FD)){
    filename=scan->d_name;

    strcpy(fnc, argv[1]);
    strcat(fnc, "/");
    strcat(fnc, filename);

    stat(fnc,&s);
    if(S_ISREG(s.st_mode)){
    size=s.st_size;
    asprintf(&string, "%ld", size);//try to convert long int into string
    fprintf(stream, "%s\n",filename);
    fprintf(stream, "%s\n",string );
    free(string);
		F_FD = fopen(fnc, "r" );
		while( (readbytes = fread( buf, 1, MAX_DIM, F_FD ) )> 0 ){
                        fwrite( buf, 1 , readbytes, stream);
                }
		fclose(F_FD);


  }


    /*      stat(c_scan->d_name,&s2); //last mod file.c
          time2=s2.st_mtime;
          printf("c_scan :%s\n",c_scan->d_name);
          if(difftime(time1,time2)>0){

            strcpy(myArgv, "gcc ");
            for(i=2; i<argc; i++){ strcat(myArgv,argv[i]);}
            strcat(myArgv," -o ");
						strcat(myArgv,argv[1]);
						strcat(myArgv," ");
            strcat(myArgv,c_scan->d_name);
            printf("%s\n",myArgv);
            myexec(myArgv);
					}else{

						printf("%s:run genobj first\n",filename );

					}

		  }
	*/
 }
 fclose(stream);
 closedir (FD);


}
