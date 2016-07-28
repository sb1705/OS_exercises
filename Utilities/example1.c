/*     http://man7.org/linux/man-pages/man2/waitpid.2.html  */
       #include <sys/wait.h>
       #include <stdlib.h>
       #include <unistd.h>
       #include <stdio.h>

       int
       main(int argc, char *argv[])
       {
           pid_t cpid, w;
           int wstatus;

           cpid = fork();
           if (cpid == -1) {
               perror("fork");
               exit(EXIT_FAILURE);
           }

           if (cpid == 0) {            /* Code executed by child */

                printf("Child PID is %ld\n", (long) getpid());

		/*  If no command-line argument is
	          supplied to the program, then the child suspends its execution using
	          pause(2), to allow the user to send signals to the child.*/

               if (argc == 1)
                   pause(); /* Wait for signals */

		/*Otherwise,
      		 if a command-line argument is supplied, then the child exits
       		 immediately, using the integer supplied on the command line as the
       		 exit status.*/

               _exit(atoi(argv[1]));

           } else {                    /* Code executed by parent */

		/*The parent process executes a loop that monitors the
       		child using waitpid(), and uses the W*() macros described above to
       		analyze the wait status value.*/
               do {
                   w = waitpid(cpid, &wstatus, WUNTRACED | WCONTINUED);
                   if (w == -1) {
                       perror("waitpid");
                       exit(EXIT_FAILURE);
                   }

                   if (WIFEXITED(wstatus)) {

                       printf("exited, status=%d\n", WEXITSTATUS(wstatus));

                   } else if (WIFSIGNALED(wstatus)) {

                       printf("killed by signal %d\n", WTERMSIG(wstatus));

                   } else if (WIFSTOPPED(wstatus)) {

                       printf("stopped by signal %d\n", WSTOPSIG(wstatus));

                   } else if (WIFCONTINUED(wstatus)) {

                       printf("continued\n");

                   }
               } while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
               exit(EXIT_SUCCESS);
           }
       }
