'''Lo script o il programma python da realizzare deve fornire l'occupazione totale in byte dei file della directory corrente che
corrispondono alla espressione regolare passata come parametro.
e.s.  sizere 'l[a-z]x'
444
significa che la somma delle ampiezze dei file di tre lettere alfabetiche minuscole che iniziano per l finiscono per x, e' di 444
byte.  '''



import sys, os,fnmatch
size=0

path="."


for root, dirs, files in os.walk(".", topdown=True):

	for filename in files:
		
		path = os.path.join(".",filename)
		if fnmatch.fnmatch(filename, sys.argv[1]):
			print path

			size += os.path.getsize(path)
	break;

print size
