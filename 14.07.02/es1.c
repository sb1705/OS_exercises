
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stddef.h>


#define MAX_DIM 500




int is_regular_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int main(int argc, char *argv[]){
DIR *FD;
struct dirent *scan;
char *filename, fnc[MAX_DIM];
struct stat s;
FILE *stream;
long int size=0;

int file=0;

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
      size= s.st_size;

      fprintf(stream, "%ld %s\n",size, filename);
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
