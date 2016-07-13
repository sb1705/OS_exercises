#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int split(char line[], char **command){

	int counter=0;
	char *token;

	strtok(line, "\n");
	token = strtok(line, " ");
	counter++;
	while( token != NULL )
	{
		if(command){
			command[counter-1] = token;
		}
		token = strtok(NULL, " ");
		counter++;
	}


	return counter;
}

int myexec (const char *line){
  int status;
  pid_t pid;

	char *buf=strdup(line);
	int argc=split(buf,NULL);
	char **command=calloc(argc+1,sizeof(char *));
	buf=strdup(line);
	split(buf,command);


  pid = fork ();
  if (pid == 0)
    {
      /* This is the child process.  Execute the shell command. */
      execvp(command[0], command);
      _exit (EXIT_FAILURE);
    }
  else if (pid < 0)
    /* The fork failed.  Report failure.  */
    status = -1;
  else
    /* This is the parent process.  Wait for the child to complete.  */
    if (waitpid (pid, &status, 0) != pid)
      status = -1;
  return status;

}
