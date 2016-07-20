
// serve per capire se un file è un file di testo
int is_text(FILE *stream){
  int c;
  while((c=fgetc(stream)) != -1){ // -1 è l'eof
    if((c>127)||(c<0)){
      return 0;
    }
  }
  return 1;


}





