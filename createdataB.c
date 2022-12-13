#include <stdio.h>

int main(void) {
    FILE *psFile;
    unsigned int uiAddress;
    char* name = "Jacob";
    int i;

    psFile = fopen("data", "w");

    for (i = 0; i < 5; i++) {
        char n = *name;
        /* fwrite(&n, sizeof(char), 1, psFile); */
        fprintf(psFile, "%c", n);
        name++;
    }

    putc('\0', psFile);

    for (i = 0; i < 42; i++) {
        fprintf(psFile, "%c", i);
    }
   
    uiAddress = 0x400858;

    fwrite(&uiAddress, sizeof(unsigned int), 1, psFile);
    fclose(psFile);
    return 0;
}

