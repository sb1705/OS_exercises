
#include <errno.h>

#include <pwd.h>

#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <grp.h>

int checkgroup(const char *user, const char *group);
