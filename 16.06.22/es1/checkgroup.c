#include "checkgroup.h"

#ifdef ASTRUBALE
  struct passwd {
    char   *pw_name;       /* username */
    char   *pw_passwd;     /* user password */
    uid_t   pw_uid;        /* user ID */
    gid_t   pw_gid;        /* group ID */
    char   *pw_gecos;      /* user information */
    char   *pw_dir;        /* home directory */
    char   *pw_shell;      /* shell program */
};

#endif

int checkgroup(const char *u, const char *g){
  struct passwd *p;
  struct group *group;
  if((p=getpwnam(u))==NULL){
    fprintf(stderr, "Error : cannot find the user \n");
  	return -1;
  }else{
    group = getgrgid (p->pw_gid);
    if (!group) //cannot  find information about usr group
      {
        printf ("Couldn't find out about group %d.\n",
                (int) p->pw_gid);
        exit (EXIT_FAILURE);
      }

    if(!strcmp(group->gr_name,g)){
      return 1;

    }
    else{
      return 0;
    }

  }


}
