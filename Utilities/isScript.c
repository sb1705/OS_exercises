#include <stdio.h>

int isScript(char *file){
    FILE *fp;
    fp = fopen(file, "r");
	if (fgetc(fp)==35){//#
        if(fgetc(fp)==33){// !
            fclose(fp);
            return 1;
        }

    }
    fclose(fp);
    return 0;
}
