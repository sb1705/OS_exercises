/*
2013.01.25

Scrivere   un   programma   listexe   che   fornisca   in   output   l'elenco   dei   processi   attivi   nel   sistema   mettendo   in   output   per   ogni
processo il pid e il path dell'eseguibile.
L'informazione puo' essere trovata scandendo la directory proc, infatti ad ogni processo attivo corrisponde una directory in
/proc che ha come nome il numero del processo (ad esempio al processo 9801 corrisponde la directory /proc/9801) e all'interno
di queste directory il file exe e' un link simbolico all'eseguibile.
Esempio:
$ ls -l /proc/9801/exe
lrwxrwxrwx 1 renzo renzo 0 Jan 22 18:26 /proc/9801/exe -> /bin/bash
l'output del programma listexe dovrebbe essere:
$ listexe
.....
9801 /bin/bash
9933 /usr/bin/vim*/


#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
 
int main(void){
 
	int pid,max_size=10000;
	char *path, *dove=malloc(max_size);
	path="/proc";
	size_t size=max_size;
	struct dirent **namelist;
        int n;
	int c=0;
	/*int scandir (const char *dir, struct dirent ***namelist, int (*selector) (const struct dirent *), int (*cmp) (const struct dirent **, const struct dirent **))
	scandisce la directory con nome dir, 
	salva le entry in una namelist 
	si puo' mettere un selettore come terzo argomento (se questa funz da un valore da un valore diverso da zero allora si inserisce l'argomento nella namelist, altrimenti no), pero' noi gli abbiamo dato 0, quindi seleziona tutto
	l'ultima e' una funzione di ordinamento, alphasort e' una delle predefinite
	
	restituisce il numero di elementi inseriti nella namelist
	*/
 
        n = scandir(path, &namelist, 0, alphasort);
    if (n < 0){
        perror("scandir");
    }
    else{
        while(n--){
 
        	DIR *cartella;
        	path=malloc(1000);
        	path[0]='\0';
			strcat(path,"/proc/");
       		strcat(path,namelist[n]->d_name);
       		//printf("%s\n",path);
       		cartella=opendir(path);
 
       		if (cartella != NULL){
       			strcat(path,"/exe");
       			readlink(path,dove,size);//legge il link simbolico associato
       			pid=atoi(namelist[n]->d_name);
       			if (pid!=0){
       				printf("%s ha pid: %d il path %s\n",namelist[n]->d_name,pid,dove);
       			}
       		}
 
       		free(path);
        }  	
        printf("%d",c);
    }
}
