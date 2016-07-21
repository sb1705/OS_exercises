/*Scrivere la funzione: char **get_user_groups(void);
che deve restituire un array (generato dinamicamente) di stringhe (anch'esse allocate dinamicamente) contenente lo username relativo all'uid
del processo chiamante nel primo elemento (indice 0). Gli elementi successivi
del vettore dovranno contenere gli identificativi di tutti i gruppi al quale l'utente appartiene. L'array è terminato con un elemento nullo.*/
#include <grp.h>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main (void){
    uid_t me;
    struct passwd *my_passwd;
    struct group *my_group;
    char **array;//  *array[]
    int i=0;
    int j;
    int ngroups;


    /* Get information about the user ID. */
    me = getuid ();
    my_passwd = getpwuid (me);
    if (!my_passwd) {
        printf ("Couldn't find out about user %d.\n", (int) me);
        exit (EXIT_FAILURE);
    }

    //Find out how many groups the user has

    ngroups = getgroups (0, NULL);//Since the first parameter is zero getgroups just returns the total number of supplementary group IDs
    printf("Numero gruppi, %d\n", ngroups );

    //Allocate Memory for array[][]

    printf("La dim del nome è %lu\n", sizeof(my_passwd->pw_name));
    printf("La dim del gruppo id è %lu\n", sizeof (gid_t));
    array = malloc(((ngroups) * sizeof (gid_t))+sizeof(my_passwd->pw_name));
    printf("Allocato l'array di grandezza %lu\n", ((ngroups) * sizeof (gid_t))+sizeof(my_passwd->pw_name) );

    array[0]=malloc(sizeof(my_passwd->pw_name));
    strcpy(array[0],my_passwd->pw_name);
    printf("in array[0] ci sta %s\n", array[0] );
    gid_t groups[ngroups * sizeof (gid_t)];
    printf("la posizione 0 sta all'indirizzo %d\n", *array[0] );
    int val = getgroups ((ngroups * sizeof (gid_t)), groups);
    if (val < 0) // CONDIZIONE ERRORE ->RIGUARDA
      {
        printf("ERRORE\n" );
        exit (EXIT_FAILURE);
      }

    for(j=1; j<=ngroups; j++){
      printf("\nDentro il ciclo: in array [0] ci sta %s\n\n",array[0]);
      array[j]=(char *) malloc (sizeof (gid_t));//allochiamo lo spazio
      sprintf(array[j],"%d",groups[j]); //convert int to str

      printf("alla posizione %d abbiamo %s\n", j, array[j] );

      printf("la posizione %d sta all'indirizzo %d\n", j, *array[j] );

      printf("\n in fondo: in array [0] ci sta %s\n\n",array[0]);

    }
    array[j]=NULL;





//    listofgroups = malloc(ng * sizeof (char));

    i=0;
    while(array[i]!=NULL)
    {
      printf("%s\n",array[i]);
      i++;
    }
}
