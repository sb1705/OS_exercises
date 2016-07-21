'''la directory /home/students contiene le home directory di tutti gli studenti. 
Scrivere un programma python checonsiderando solo i nomi del directory service centralizzato 
(del tipo nome.cognome) mostri la classifica dei5 nomi più comuni fra gli studenti di informatica
(i file .old e .tgz sono di servizio e non vanno considerati)'''

import sys, os, collections
from collections import Counter

path='students'
names = []
allnames = []



for (dirpath, dirnames, filenames) in os.walk(path):
    names.extend(dirnames)
    break


for c in names:
    (name, ext) = os.path.splitext(c)
    allnames.append(name)


for n,c in Counter(allnames).most_common(5):
    print n
