// if command1=ls, command2=tac
// my_system returns "ls | tac"

int my_system (const char *command1, const char *command2){ //inspired by GNU C Library 26.9 Process Creation Example
  int pipefd[2];
  int status;
  pid_t pid;

  /* Create pipe */
  if (pipe (pipefd)){
      fprintf (stderr, "Pipe failed.\n");
      return EXIT_FAILURE;
  }

  switch (fork()) {
    case 0: dup2(pipefd[0],0);
            close(pipefd[0]);
            close(pipefd[1]);
             execsp (command1);//"execl" sta' per "execute and leave", che significa che un processo sara' eseguito e poi terminato dalla stessa execl.
            _exit (EXIT_FAILURE); 
            break;
    case -1:
            exit(1);
    default: dup2(pipefd[1],1);
             close(0);
             close(pipefd[0]);
             close(pipefd[1]);
             execsp (command2);
  }

}
