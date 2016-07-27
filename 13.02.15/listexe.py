'''Scrivere un programma python o uno script bash listexe che fornisca in output l'elenco dei processi attivi nel sistema mettendo
in output per ogni processo il pid e il path dell'eseguibile.
L'informazione deve essere trovata scandendo la directory proc, infatti ad ogni processo attivo corrisponde una directory in
/proc che ha come nome il numero del processo (ad esempio al processo 9801 corrisponde la directory /proc/9801) e all'interno
di queste directory il file exe e' un link simbolico all'eseguibile.
Esempio:
$ ls -l /proc/9801/exe
lrwxrwxrwx 1 renzo renzo 0 Jan 22 18:26 /proc/9801/exe -> /bin/bash
l'output del programma listexe dovrebbe essere:
$ listexe
.....
9801 /bin/bash
9933 /usr/bin/vim
.....
(alcuni link simbolici possono essere non leggibili per sicurezza, verranno omessi).

DOVREBBE FUNZIONARE...
'''

import os

pids = [pid for pid in os.listdir('/proc') if pid.isdigit()]

for pid in pids:
    try:
        print('{} : {}'.format(pid, open(os.path.join('/proc', pid, 'cmdline'), 'rb').read()))
    except IOError: # proc has already terminated
        continue
