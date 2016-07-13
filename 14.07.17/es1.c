/*Write a program that calls gcc -c for all "file.c" in the current directory, unless a "file.o" most recently updated already exists.

Es:
genobj  -I . -ggdb
if in the current directory there are uno.c, due.c, due.o the program must call
gcc -I. -ggdb -c uno.c
and, only if due.o has been modified after due.c, it must call also
gcc -I. -ggdb -c due.c

*/

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
#include <sys/wait.h>

#define MAX_DIM 500
#define SHELL "/bin/sh"

#ifdef	ASTRUBALE
 struct stat {
dev_t       st_dev;     /* ID del dispositivo contenente file */
ino_t       st_ino;     /* numero dell'inode */
mode_t      st_mode;    /* protezione */
nlink_t     st_nlink;   /* numero di hard links */
uid_t       st_uid;     /* user ID del proprietario */
gid_t       st_gid;     /* group ID del proprietario */
dev_t       st_rdev;    /* ID del dispositivo (se il file speciale) */
off_t       st_size;    /* dimensione totale, in byte */
blksize_t   st_blksize; /* dimensione dei blocchi di I/O del filesystem */
blkcnt_t    st_blocks;  /* numero di blocchi assegnati */
time_t      st_atime;   /* tempo dell'ultimo accesso */
time_t      st_mtime;   /* tempo dell'ultima modifica */
time_t      st_ctime;   /* tempo dell'ultimo cambiamento */
	};
#endif

int my_system (const char *command)
{
  int status;
  pid_t pid;

  pid = fork ();
  if (pid == 0)
    {
      /* This is the child process.  Execute the shell command. */
      execlp ("gcc", command, NULL);
      _exit (EXIT_FAILURE);
    }
  else if (pid < 0)
    /* The fork failed.  Report failure.  */
    status = -1;
  else
    /* This is the parent process.  Wait for the child to complete.  */
    if (waitpid (pid, &status, 0) != pid)
      status = -1;
  return status;
}

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

int myexec (const char *line){
  int status;
  pid_t pid;

	char *buf=strdup(line);
	int argc=split(buf,NULL);
	char **command=calloc(argc+1,sizeof(char *));
	buf=strdup(line);
	split(buf,command);


  pid = fork ();
  if (pid == 0)
    {
      /* This is the child process.  Execute the shell command. */
      execvp(command[0], command);
      _exit (EXIT_FAILURE);
    }
  else if (pid < 0)
    /* The fork failed.  Report failure.  */
    status = -1;
  else
    /* This is the parent process.  Wait for the child to complete.  */
    if (waitpid (pid, &status, 0) != pid)
      status = -1;
  return status;

}


//Returns the extension of a file from the filename
const char *get_ext(const char *filename) {
	const char *dot = strrchr(filename, '.'); //Returns a pointer to the last occurrence of char "." in the string filename
	if(!dot || dot == filename) return "";
	return dot + 1;
}


int main(int argc, char *argv[]){
DIR *FD, *FD2;
struct dirent *c_scan, *o_scan;
char *filename;
struct stat s1,s2;
time_t time1, time2;
char myArgv[MAX_DIM];
int i;



//open current directory
FD = opendir (".");
FD2= opendir (".");


if(FD==NULL ||FD2==NULL){
	fprintf(stderr, "Error : Failed to open directory %s\n", strerror(errno));
	return -1;
}

//scan current directory's files
while(c_scan=readdir(FD)){

  if(!strcmp(get_ext(c_scan->d_name),"c")){//if a file.c is found

    filename=c_scan->d_name;
    printf("Filename prima del ciclo: %s\n",filename);
		while(o_scan=readdir(FD2)){

      printf("Cerco il .o in: %s\n",o_scan->d_name);
			if((!strncmp(filename, o_scan->d_name, strlen(o_scan->d_name)-2)) && (!strcmp(get_ext(o_scan->d_name), "o"))){

          //if a file.o is found
			    stat(filename,&s1);
          time1= s1.st_mtime;
          printf("Filename: %s\n",filename);
          stat(o_scan->d_name,&s2);
          time2=s2.st_mtime;
          printf("o_scan :%s\n",o_scan->d_name);
          if(difftime(time1,time2)>0){
            strcpy(myArgv, "gcc ");
            for(i=1; i<argc; i++){ strcat(myArgv,argv[i]);}
            strcat(myArgv," -c ");
            strcat(myArgv,filename);
            printf("%s\n",myArgv);
            myexec(myArgv);

			}

		  }
	  }
 }
 closedir (FD2);
 FD2= opendir (".");
 if(FD2==NULL){
 	fprintf(stderr, "Error : Failed to open directory %s\n", strerror(errno));
 	return -1;
 }
}
}
