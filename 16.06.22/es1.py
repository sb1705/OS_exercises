'''
Scrivere la funzione : int checkgroup(cont char *user, const char *group);
che deve restituire:
0 se l'utente non appartiene al gruppo
1 se l'utente appartiene al gruppo
-1 in caso di errore (es. l'utente non esiste)
Creare i file checkgroup.c checkgroup.h e un main.c contenente un programma principale che prenda come
argv[1] e argv[2] i due parametri della funzione e ne stampi il risultato.
Produrre un makefile opportuno


Ho provato a farlo anche in python
'''

import grp, sys

username = sys.argv[1]
group= sys.argv[2]
i=0

#groups = [g.gr_name for g in grp.getgrall() if username in g.gr_mem]
for g in grp.getgrall():
    if g.gr_name==group and username in g.gr_mem:
        i=1
        break;


print i
