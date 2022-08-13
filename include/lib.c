#ifdef __GNUC__
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#define long 
#else
#define long 
#define NULL ((void *)0)
asm ".entry"
asm "ldr r0,[sp]"
asm "add r1,sp,#4"
asm "stmdb sp!,{r0,r1}"
asm "bl @main"
asm "mov r7,#248"
asm "swi 0"
#include "syscall.c"
#include "mem.c"
#include "malloc.c"
#endif

#include "xmalloc.c"
