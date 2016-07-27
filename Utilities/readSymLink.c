#include <stdio.h>
#include <stdlib.h>


//took from http://www.gnu.org/software/libc/manual/html_node/Symbolic-Links.html
char *readlink_malloc (const char *filename){
  int size = 128;
  char *buffer = NULL;

  while (1)    {
      //attempts to resize the memory block pointed to by ptr that was previously allocated with a call to malloc or callo
      buffer = (char *) xrealloc (buffer, size); 
      int nchars = readlink (filename, buffer, size);
      if (nchars < 0)
        {
          free (buffer);
          return NULL;
        }
      if (nchars < size)
        return buffer;
      size *= 2;
    }
}
