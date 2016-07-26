'''Scrivere un programma python o uno script bash per cercare all'interno
della directory corrente
 tutti i file che abbiano lo stesso
contenuto.'''

import filecmp, os

def cmpT(t1, t2):
	return sorted(t1) == sorted(t2)

coppie = []
for f in os.listdir("."):
    for f2 in os.listdir("."):
        path=os.path.join(".",f)
        path2=os.path.join(".", f2)
        if (os.path.isfile(path) and os.path.isfile(path2) and path!=path2):
                if(filecmp.cmp( f,f2)):
                    if not coppie:
                        coppie.append((f,f2))
                    else:
                        for elem in coppie:
                            if not cmpT(elem, (f,f2)):
                                coppie.append((f,f2))
print coppie
