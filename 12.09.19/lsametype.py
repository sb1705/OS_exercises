'''Scrivere uno script bash o un programma python che presi in input un file e una directory fornisca la lista dei file nella
directory e in tutto il sottoalbero generato che hanno lo stesso tipo del file (cioe' tutti i file per i quali il comando file fornisca lo stesso output)
es: 
$lsametype file.c /tmp/test
f1.c
helloworld.c
(sono tutti di tipo C source, ASCII text)'''


import sys, os

fiile=sys.argv[1]

name, ext = os.path.splitext(fiile)


for root, dirs, files in os.walk(sys.argv[2], topdown=True):
	for filee in files:
		path=os.path.join(sys.argv[2],filee)
		filename, file_extension = os.path.splitext(path)
		if file_extension==ext:
			print filee

