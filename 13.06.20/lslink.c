/*Si estenda l'esercizio 1
e lo si trasformi in
un programma che cerchi in una directory la presenza di link (fisici).
Per   ogni   file   avente   piu'   nomi   all'interno   della   directory  deve   stampare   una   riga   contenente   l'elenco   dei   nomi   che   fanno
riferimento allo stesso file. (suggerimento: piu' nomi fanno riferimento allo stesso file se corrisponde in numero di i-node del
file)
$ lslink demo
demo/1.c demo/link.c
demo/l1 demo/l2 demo/l3 */

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

struct node_list{
    struct node *n;
    struct node_list *next;
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
	int i=0, prec=0, stampato=0;
	char *dirname, *filename;
	struct node *nodeArray;
    struct node_list list;


	if(argc <2){
		dirname=malloc(strlen("."));
		dirname=".";
	}
	else{
		dirname=argv[1];
	}

	
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

    filename=NULL;

	for(i=0;i<count;i++){
        //vede qual è l'inode, è uguale al precedente? allora stampalo e stampa il nome precedente e il tuo
        int in=nodeArray[i].inodenum;
        if(prec==in){//dato che sono in ordine, quelli uguali sono vicini
            if(!stampato) {
                printf("%d : \n", nodeArray[i].inodenum);
                stampato=1;
            }
            printf("%s\n", filename);
        }
        else{
            if(stampato==1) printf("%s\n\n", filename);

            stampato=0;

        }
        prec=nodeArray[i].inodenum;
        filename=&(nodeArray[i].name[0]);

	}


	return 0;
}
