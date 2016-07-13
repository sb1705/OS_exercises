/*dopo la riga bianca inserire nel file di output (ordinatamente) il contenuto di tutti i file.
(quindi nel caso sopra i 12 byte di file1 seguiti dai 235 di “file di prova”)*/


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

int is_regular_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}



void append(FILE *head, FILE *tail){
    char buf[BUFSIZ];
    size_t n;
    while ((n = fread(buf, 1, sizeof buf, tail)) > 0)
        if (fwrite(buf, 1, n, head) != n)
            abort();
    if (ferror(tail))
        abort();
}


int main(int argc, char *argv[]){
DIR *FD;
struct dirent *scan;
char *filename, fnc[MAX_DIM];
struct stat s;
FILE *stream, *rstream, *astream;
long int size=0;

int i;

//open directory
FD = opendir (argv[1]);

if(FD==NULL){
	fprintf(stderr, "Error : Failed to open directory %s\n", strerror(errno));
	return -1;
}

stream=fopen(argv[2], "w");
if (stream == NULL) {
   puts("cannot open stream this file");
   exit(1);
}
astream=fopen(argv[2], "aw");
if (astream == NULL) {
   puts("cannot open astream this file");
   exit(1);
}

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
      rstream = fopen(fnc, "r");
      if (rstream == NULL) {
         puts("cannot open this file");
         exit(1);
      }
      fprintf(astream, "\n");
      append(astream,rstream);
      fclose(rstream);
    }

 }
 fclose(stream);
 fclose(astream);

 closedir (FD);


}
