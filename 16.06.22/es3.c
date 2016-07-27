/*
la directory /home/students contiene le home directory di tutti gli studenti.
Scrivere un programma python checonsiderando solo i nomi del directory service centralizzato
(del tipo nome.cognome) mostri la classifica dei5 nomi più comuni fra gli studenti di informatica
(i file .old e .tgz sono di servizio e non vanno considerati)

Ho provato a farlo in c, non è finito

Sono riuscita a mettere in una lista tutti i nomi che troviamo,
l'inserimento è in testa per cui la lista non è ordinata

Manca solo da stampare i 5 più frequenti,
idee: 
1. Non credo convenga:
inserisci ordinatamente, cioè in coda 
e ogni volta che incrementi il contatore di quelcuno lo sposti 
dietro a qualcuno che ha il count > del suo.

2. Penso sia l'algoritmo migliore, anche se non ci ho pensato molto:
scorrere una volta la lista tenendo un'altra lista di 5 elementi, l'ultimo con next nullo
e un int (0/1) che indica se la lista è "piena"
Inserisci in testa il primo che trovi.
Quelli dopo:
Perogni el della lista (while el!=NULL)
controlla se ha count > el.count --> inserisci prima di el in testa
  se la lista era piena togli l'ultimo el

*/

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

struct lista_nomi{
    char nome[BUFSIZ];
    int count;
    struct lista_nomi *next;
};

//ritorna un puntatore all'elemento con quel nome, NULL se non lo trova
struct lista_nomi *search(struct lista_nomi *head, char *nome){
    printf("sto cercando %s \n", nome);
    struct lista_nomi *tmp;
    tmp=head;
    while(tmp!=NULL){
        if(!strcmp(tmp->nome,nome)){
            printf("TROVATO %s\n", nome );
            break;
        }
        tmp=tmp->next;
    }
    return tmp;

}

struct lista_nomi *insert (struct lista_nomi * head, char *nome){
    
    printf("sto provando a inserire\n" );
	struct lista_nomi *tmp;
    tmp=malloc (sizeof(struct lista_nomi));

	strcpy(tmp->nome,nome);

	tmp->count=1;

	tmp->next= head;

	head=tmp;
    return head;
}

int main(int argc, char *argv[]){
    DIR           *d;
    struct dirent *dir;
    char *ext, *entry_name, *name;
    char args[1];
    int fd[2]; //pipe fd for process sinc
    int i, last_len;
    struct lista_nomi *head, *elem;
    head=NULL;
    
    
    d = opendir("students");
    if(d==NULL){
      printf ("Non riesco ad aprire la directory\n");
      exit(1);
    }


    while ((dir = readdir(d)) != NULL) {
        if(!strncmp(dir->d_name, ".", 1)){
            continue;
        }
        entry_name=malloc(strlen(dir->d_name));
        strcpy(entry_name, dir->d_name);
        printf("entry_name : %s \n",entry_name);

        ext=entry_name+strlen(entry_name)-3;
        if( !strcmp(ext, "tgz") || !strcmp(ext,"old") ){
            printf("Ignoro il file %s\n\n", dir->d_name);
            continue;
        }

        name = strtok(entry_name, ".");
        printf("Prima dell'if\n");
        elem=search(head, name);
        printf("Dopo search\n" );
        if(elem!=NULL){
            elem->count+=1;
            printf("Count : %d\n\n ", elem->count );
            printf("next : %s\n\n ", elem->next);
        }
        else{
            head=insert(head, name);
            printf("ho inserito nella lista : %s\n\n ", head->nome );
            printf("Count : %d\n\n ", head->count );
            printf("next : %s\n\n ", head->next);
        }
    }
    

}
