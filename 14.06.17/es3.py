'''
Il comando che dovrete implementare come script shell o programma python e'  maxfreq.
Maxfreq ha come parametro un carattere alfanumerico e una directory.
Es:
maxfreq q  mydir
Cerca in tutto il sottoalbero del file system originato da mydir il file che ha la maggior frequenza della lettera indicata (in
questo caso la maggior frequenza di 'q'). Fornisce in output il nome del file e la frequenza in percentuale.
'''

import sys, os
from collections import Counter

if len(sys.argv) > 2:

	frequency = []
	for root, subdir, files in os.walk(sys.argv[2]):
		for filename in files:
			path = os.path.join(root, filename) #per avere il path assoluto
			with open(path) as f:
				t=f.read()
				leng = len(t)
				c = Counter(t.strip())
				if leng > 0:
					frequency.append((filename, "{0:.2f}".format(float(c[sys.argv[1]])*100/leng)))
					#add to the list the filename and the frequency in percentage (but formatted to show only 2 decimals
	frequency.sort(key=lambda tup: tup[1], reverse = True)

	print frequency[0]

else:
	print "needed 2 arguments"
