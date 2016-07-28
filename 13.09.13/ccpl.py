'''
Sia data una directory che contiene file di testo.
Scopo dell'esercizio e' di contare i caratteri delle corrispondenti righe di testo di tutti i file della directory, si vuole cioe' sapere
il numero totale di caratteri presenti nelle prime righe di tutti i file, nelle seconde linee, ecc.
$ ccpl mydir
1 234
2 21
3 333
.....
l'ouput significa che se contiamo tutti i caratteri contenuti nella prima riga di tutti i file in mydir otteniamo 234 (mydir/file1
puo' avere 40 caratteri nella prima riga, mydir/file2 ne puo' avere 20, ecc... procedendo per tutti i file di mydir la somma fa
234).
'''

import sys, os

dic = []

if len(sys.argv) > 1:

        for fname in os.listdir(sys.argv[1]):
            path=os.path.join(sys.argv[1], fname)
            with open(path, 'r') as f:
                i=1;
                for line in f.readlines():
                    dic[i] = dic[i] + len(line)
                    f.close()
        print dic

else:
	print "needed 1 arguments"
