Questa funzione e' definita come segue:

     int scanf(char *format, args ...)

  Legge dallo stdin e mette l'input negli indirizzi delle variabili 
  specificate nella lista di args; ritorna il numero di caratteri letti.

  La stringa di controllo del formato e' simile a quella vista per printf.

  E' importante notare che la funzione scanf richiede di specificare 
  l'indirizzo di ogni variabile, oppure un puntatore ad essa:

     scanf("%d",&i);

  E' anche possibile dare solamente il nome di un array o di una stringa a
  scanf, poiche' questo corrisponde all'indirizzo di partenza dell'array/
  stringa:

     char string[80];

     scanf("%s",string);
