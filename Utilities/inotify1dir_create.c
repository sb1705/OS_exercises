/*

Il programma tiene sotto controllo una directory (il cui pathname viene passato come unico
paramentro), e segnala, stampandone il nome, ogni file che viene creato in tale directory.

*/
       #include <errno.h>
       #include <poll.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <sys/inotify.h>
       #include <unistd.h>

	#define NAMELEN 1024
	#define BUF_SIZE sizeof(struct inotify_event)+NAMELEN//il buffer per gli eventi deve avere dimensione superiore a quella della struttura inotify_event altrimento non c'e' spazio per il campo name.


       /* 
	  Read all available inotify events from the file descriptor 'fd'.
          wd is the table of watch descriptors for dirname.
          dirname is the name of watched directories.
       */

       static void  handle_events(int fd, int wd, char* dirname) {
           /* Some systems cannot read integer variables if they are not
              properly aligned. On other systems, incorrect alignment may
              decrease performance. Hence, the buffer used for reading from
              the inotify file descriptor should have the same alignment as
              struct inotify_event. */

           char buf[BUF_SIZE]
               __attribute__ ((aligned(__alignof__(struct inotify_event))));
           const struct inotify_event *event;
           int i;
           ssize_t len;
           char *ptr;

           /* Loop while events can be read from inotify file descriptor. */

           while (1) {

               /* Read some events. */

               len = read(fd, buf, sizeof(buf));
               if (len == -1 && errno != EAGAIN) { //EAGAIN = Resource temporarily unavailable
                   perror("read");
                   exit(EXIT_FAILURE);
               }

               /* If the nonblocking read() found no events to read, then
                  it returns -1 with errno set to EAGAIN. In that case,
                  we exit the loop. */

               if (len <= 0)
                   break;

               /* Loop over all events in the buffer */

               for (ptr = buf; ptr < buf + len;
                       ptr += sizeof(struct inotify_event) + event->len) {

                   event = (const struct inotify_event *) ptr;

                   /* Print event type */

                   if (event->mask & IN_CREATE)
                       printf("è stato creato : ");
                  

                   /* Print the name of the watched directory */
/*
                   for (i = 1; i < argc; ++i) {
                       if (wd[i] == event->wd) {
                           printf("%s/", argv[i]);
                           break;
                       }
                   }
*/
                   /* Print the name of the file */
		   if (!(event->mask & IN_ISDIR)){
		           if (event->len)
		               printf("%s\n", event->name); // il \n serve, sennò non stampa ... mmm...
		   }
                 
               }
           }
       }

       int main(int argc, char* argv[]) {
           char buf;
           int fd, i, poll_num;
           int wd;
           nfds_t nfds; //An unsigned integer type used for the number of file descriptors.
           struct pollfd fds[2];

           if (argc < 1) {
               printf("Usage: %s PATH \n", argv[0]);
               exit(EXIT_FAILURE);
           }

           printf("Press ENTER key to terminate.\n");

           /* Create the file descriptor for accessing the inotify API */

           fd = inotify_init1(IN_NONBLOCK);
           if (fd == -1) {
               perror("inotify_init1");
               exit(EXIT_FAILURE);
           }

  
           /* Mark directories for events
              - file was CREATED
           */

           
            wd = inotify_add_watch(fd, argv[1], IN_CREATE);
            if (wd == -1) {
		   fprintf(stderr, "Cannot watch '%s'\n", argv[i]);
		   perror("inotify_add_watch");
		   exit(EXIT_FAILURE);
            }
           

           /* Prepare for polling */

           nfds = 2;

           /* Console input */

           fds[0].fd = STDIN_FILENO;
           fds[0].events = POLLIN;

           /* Inotify input */

           fds[1].fd = fd;
           fds[1].events = POLLIN;

           /* Wait for events and/or terminal input */

           printf("Listening for events.\n");
           while (1) {
               poll_num = poll(fds, nfds, -1);
               if (poll_num == -1) {
                   if (errno == EINTR)
                       continue;
                   perror("poll");
                   exit(EXIT_FAILURE);
               }

               if (poll_num > 0) {

                   if (fds[0].revents & POLLIN) { //è stato ricevuto input dal terminale

                       /* Console input is available. Empty stdin and quit */

                       while (read(STDIN_FILENO, &buf, 1) > 0 && buf != '\n')
                           continue;
                       break;
                   }

                   if (fds[1].revents & POLLIN) {//è stato ricevuto input dalle dir che stiamo monitorando

                       /* Inotify events are available */

                       handle_events(fd, wd, argv[1]);
                   }
               }
           }

           printf("Listening for events stopped.\n");

           /* Close inotify file descriptor */

           close(fd);


           exit(EXIT_SUCCESS);
       }
