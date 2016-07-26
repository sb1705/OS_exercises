/*Scrivere un programma che stampi il numero di inode di ogni file presente in una direcotory passata come argomento (o della
direcotry corrente se il programma viene chiamato senza parametri) e stampi l'elenco in ordine crescente di numero di i-node.
Es:
$
lsino
demo
demo/. 1972484
demo/.. 1971834
demo/1.c 1972528
demo/a.out 1972485
demo/l1 1972486
demo/l2 1972486
demo/l3 1972486
demo/link.c 1972528*/





#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

struct node{
	int inodenum;
	char name[1024];
};

int node_cmp (const void *v1, const void *v2)
{
  const struct node *c1 = v1;
  const struct node *c2 = v2;

  return (c1->inodenum - c2->inodenum);
}

int main (int argc, char *argv[]){
	DIR* FD;
	struct dirent* dir_entry;
	int count=0;
	int i=0;
	char *dirname, *filename;
	struct node *nodeArray;


	if(argc <2){
		dirname=malloc(strlen("."));
		dirname=".";
	}
	else{
		dirname=argv[1];
	}

	printf("%s\n",dirname );
	/* Scanning the in directory */
	if (NULL == (FD = opendir (dirname)))
	{
		fprintf(stderr, "Error : Failed to open input directory - %s\n", strerror(errno));

		return -1;
	}

	//chdir(dirname); <-- PERCHÈ SERVE?

	//conta le directory entry
	while ((dir_entry = readdir(FD)))
	{
		count++;
	}

	rewinddir(FD);

	nodeArray=malloc(count*sizeof(struct node));

	while ((dir_entry = readdir(FD)))
	{

		filename=&(nodeArray[i].name[0]);

		memset(filename,'0',1); //Need to reset the name, without it there may be some rubbish in memory

		//Insert every file name-ino in the array
		strcpy(filename, dirname);
		strcat(nodeArray[i].name, "/");
		strcat(nodeArray[i].name, dir_entry->d_name);

		nodeArray[i].inodenum=dir_entry->d_ino;
		//printf("Array[%d] : nome=%s, inode=%d\n", i, nodeArray[i].name, nodeArray[i].inodenum );
		i++;
	}


	qsort (nodeArray, count, sizeof (struct node), node_cmp);

	for(i=0;i<count;i++){
		printf("%s %d\n",nodeArray[i].name, nodeArray[i].inodenum);
	}


	return 0;
}
