/*
Scrivere la funzione : int checkgroup(cont char *user, const char *group);
che deve restituire:
0 se l'utente non appartiene al gruppo
1 se l'utente appartiene al gruppo
-1 in caso di errore (es. l'utente non esiste)

Creare i file checkgroup.c checkgroup.h e un main.c contenente un programma principale che prenda come
argv[1] e argv[2] i due parametri della funzione e ne stampi il risultato.
Produrre un makefile opportuno

*/
#include "checkgroup.h"

int main(int argc, char *argv[]){

if(argc>=3){
  const char *u,*g;
  int r;

  u=argv[1];
  g=argv[2];
  r=checkgroup(u,g);

  printf("%d\n", r);
  return r;

}else{
  printf("Sono necessari due parametri");
  return -1;
}
}
