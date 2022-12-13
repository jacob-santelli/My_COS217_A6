Jacob Santelli and Joshua Yang

// section 2.1

   // Prolog
   0x400780 <readString>:       sub     sp, sp, #0x50
   0x400784 <readString+4>:     stp     x19, x20, [sp]
   0x400788 <readString+8>:     stp     x21, x30, [sp, #16]

   // First loop setup
   0x40078c <readString+12>:    mov     x19, #0x0                       // #0
   0x400790 <readString+16>:    adrp    x21, 0x420000 <__libc_start_main@got.plt>

   // First loop
   0x400794 <readString+20>:    mov     w20, w19
   0x400798 <readString+24>:    ldr     x0, [x21, #72]
   0x40079c <readString+28>:    bl      0x4005b0 <fgetc@plt>
   0x4007a0 <readString+32>:    cmp     w0, #0xa
   0x4007a4 <readString+36>:    b.eq    0x4007c0 <readString+64>  // b.none
   0x4007a8 <readString+40>:    cmn     w0, #0x1
   0x4007ac <readString+44>:    b.eq    0x4007c0 <readString+64>  // b.none
   0x4007b0 <readString+48>:    add     x1, sp, #0x20
   0x4007b4 <readString+52>:    strb    w0, [x19, x1]
   0x4007b8 <readString+56>:    add     x19, x19, #0x1
   0x4007bc <readString+60>:    b       0x400794 <readString+20>

   // buf[i] = '\0'
   0x4007c0 <readString+64>:    add     x0, sp, #0x20
   0x4007c4 <readString+68>:    strb    wzr, [x0, w20, sxtw]

   // Second loop setup
   0x4007c8 <readString+72>:    mov     x0, #0x0                        // #0
   0x4007cc <readString+76>:    adrp    x2, 0x420000 <__libc_start_main@got.plt>
   0x4007d0 <readString+80>:    add     x2, x2, #0x58

   // Second loop
   0x4007d4 <readString+84>:    add     x1, sp, #0x20
   0x4007d8 <readString+88>:    ldrb    w1, [x0, x1]
   0x4007dc <readString+92>:    strb    w1, [x0, x2]
   0x4007e0 <readString+96>:    add     x0, x0, #0x1
   0x4007e4 <readString+100>:   cmp     x0, #0x30
   0x4007e8 <readString+104>:   b.ne    0x4007d4 <readString+84>  // b.any

   // Epilog and return
   0x4007ec <readString+108>:   ldp     x19, x20, [sp]
   0x4007f0 <readString+112>:   ldp     x21, x30, [sp, #16]
   0x4007f4 <readString+116>:   add     sp, sp, #0x50
   0x4007f8 <readString+120>:   ret


   // Prolog
   0x4007fc <getName>:  sub     sp, sp, #0x10
   0x400800 <getName+4>:        str     x30, [sp]

   // printf("What is your name?\n");
   0x400804 <getName+8>:        adrp    x0, 0x400000
   0x400808 <getName+12>:       add     x0, x0, #0x938
   0x40080c <getName+16>:       bl      0x4005e0 <puts@plt>

   // readString();
   0x400810 <getName+20>:       bl      0x400780 <readString>

   // Epilog and return
   0x400814 <getName+24>:       ldr     x30, [sp]
   0x400818 <getName+28>:       add     sp, sp, #0x10
   0x40081c <getName+32>:       ret

   // Prolog
   0x400820 <main>:     sub     sp, sp, #0x10
   0x400824 <main+4>:   stp     x19, x30, [sp]
   0x400828 <main+8>:   adrp    x19, 0x420000 <__libc_start_main@got.plt>

   // mprotect(...);
   0x40082c <main+12>:  add     x19, x19, #0x58
   0x400830 <main+16>:  and     x0, x19, #0xfffffffffffff000
   0x400834 <main+20>:  mov     x1, #0x1                        // #1
   0x400838 <main+24>:  mov     w2, #0x7                        // #7
   0x40083c <main+28>:  bl      0x400610 <mprotect@plt>

   // getName();
   0x400840 <main+32>:  bl      0x4007fc <getName>

   // if (strcmp(name, "Andrew Appel") != 0) skip assignment to grade
   0x400844 <main+36>:  mov     x0, x19
   0x400848 <main+40>:  adrp    x1, 0x400000
   0x40084c <main+44>:  add     x1, x1, #0x950
   0x400850 <main+48>:  bl      0x4005f0 <strcmp@plt>
   0x400854 <main+52>:  cbnz    w0, 0x400864 <main+68>

   // grade = 'B';
   0x400858 <main+56>:  mov     w1, #0x42                       // #66
   0x40085c <main+60>:  adrp    x0, 0x420000 <__libc_start_main@got.plt>
   0x400860 <main+64>:  strb    w1, [x0, #68]

   // printf("%c is your grade.\n", grade);
   0x400864 <main+68>:  adrp    x0, 0x400000
   0x400868 <main+72>:  add     x0, x0, #0x960
   0x40086c <main+76>:  adrp    x1, 0x420000 <__libc_start_main@got.plt>
   0x400870 <main+80>:  ldrb    w1, [x1, #68]
   0x400874 <main+84>:  bl      0x400600 <printf@plt>

   // printf("Thank you, %s.\n", name);
   0x400878 <main+88>:  adrp    x0, 0x400000
   0x40087c <main+92>:  add     x0, x0, #0x978
   0x400880 <main+96>:  adrp    x1, 0x420000 <__libc_start_main@got.plt>
   0x400884 <main+100>: add     x1, x1, #0x58
   0x400888 <main+104>: bl      0x400600 <printf@plt>

   // Epilog and return 0
   0x40088c <main+108>: mov     w0, #0x0                        // #0
   0x400890 <main+112>: ldp     x19, x30, [sp]
   0x400894 <main+116>: add     sp, sp, #0x10
   0x400898 <main+120>: ret

// section 2.2
   0x420044  0x00000044  grade   

// section 2.3
   0x420058: 'J'
   0x420060: 'a'
   0x420068: 'c'
   0x420070: 'o'
   0x420078: 'b'
   0x420080: '\0'
   0x420088: adr x0, grade (in machine language)
   0x420090: mov x1, 'A' (in machine language)
   0x420098: strb x1, [x0] (in machine language)
   0x420100: b 0x400864 (in machine language)
   ... rest of name is filler to overflow buf

// section 2.4
   Offset | Description 
   0      | X19 from getName()
   8      | X20 from getName()
   16     | X21 from getName()
   24     | X30 from getName()
   32     | buf
   40     | buf
   48     | buf
   56     | buf
   64     | buf
   72     | buf
   80     | X30





