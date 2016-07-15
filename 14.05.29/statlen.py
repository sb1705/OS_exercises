'''
Il comando che dovrete implementare come script shell o programma python e' statlen.
Data una directory statlen fa una statistica sulla lunghezza dei nomi dei file presenti in tutto il sottoalbero con radice nella
directory passata come parametro.
es.
$ statlen /tmp
2: 2
3: 10
5: 4
...
significa che in tmp (e in tutte le sottodir.ectory di /tmp) ci sono 2 file con nome di due caratteri, 10 con nomi di 3 caratteri e
cosi' via.
'''

''' 	WITHOUT COUNTER		'''
'''
import sys, os

if len(sys.argv) > 1:

	dic = {}
	for root, subdir, files in os.walk(sys.argv[1]):
		for filename in files:
			leng =len (filename)
			if leng > 0:
				dic[leng]=dic.get(leng, 0) + 1

	for elem in sorted(dic): #slice the list
		print "%s : %s" % (elem, dic[elem])

else:
	print "needed 1 argument"
'''



'''		WITH COUNTER	'''

import sys, os
from collections import Counter

if len(sys.argv) > 1:
	cnt = Counter()
	for root, subdir, files in os.walk(sys.argv[1]):
		for filename in files:
			cnt[len(filename)] += 1

	for elem in sorted(cnt): #slice the list
		print "%s : %s" % (elem, cnt[elem])

else:
	print "needed 1 argument"
