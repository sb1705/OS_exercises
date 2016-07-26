'''
Scrivere un programma python o uno script bash che conti l'ampiezza totale in byte di tutti i file di una directory divisi per
suffisso (i.e. Si considera suffisso tutto cio' che segue il primo carattere 'punto' nel filename). I file privi di suffisso vengono
ignorati.
Es:
$
suffixlen dir
.c: 44320
.o: 123000
.tar.gz: 555333
.jpg: 44332
'''

import sys, os


coppie = {}

for f in os.listdir(sys.argv[1]):
    path=os.path.join(sys.argv[1],f)
    size=os.path.getsize(path) #get the size of the file
    filename, extension = os.path.splitext(path)
    if(extension==""):
        continue
    else:
        if coppie.has_key(extension):
            coppie[extension]=coppie[extension]+size
        else:
            coppie[extension]=size


for key, siz in coppie.items():
    print('{} : {}'.format(key, siz))
    
    
'''
Soluzione Giulio
Lui ha considerato tutto il sottoalbero

import sys, os

ext_len={}

for root, dirs, files in os.walk(sys.argv[1], topdown=True):
	for file in files:
		path=os.path.join(sys.argv[1],file)
		filename, file_extension = os.path.splitext(path)
		if file_extension=='':
			continue
		size=os.path.getsize(path)
		if not file_extension in ext_len:
			ext_len[file_extension]=size
		else:
			ext_len[file_extension] += size

print ext_len
'''
