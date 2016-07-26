//1 se la stringa è palindroma, 0 altrimenti
int palindroma(char *s){
    char *inizio;
    char *fine;
    inizio=s;
    fine=s+strlen(s)-1;
    while(fine>inizio){
        if(*inizio==*fine){
            printf("inizio : %d\n", *inizio);
            printf("fine : %d\n", *fine );
            inizio++;
            fine--;
            continue;
        }
        else return 0;
    }
    return 1;
}
