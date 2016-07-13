//To copy the contents of file tail to the end of file head

#include <stdio.h>
#include <stdlib.h>

void append(FILE *head, FILE *tail){
    char buf[BUFSIZ];
    size_t n;
    while ((n = fread(buf, 1, sizeof buf, tail)) > 0)
        if (fwrite(buf, 1, n, head) != n)
            abort();
    if (ferror(tail))
        abort();
}

int main(void){
    FILE *head = fopen("head", "ab");
    FILE *tail = fopen("tail", "rb");
    if (!head || !tail)
        abort();
    append(head, tail);

    fclose(head);
    fclose(tail);

    exit(EXIT_SUCCESS);
}
