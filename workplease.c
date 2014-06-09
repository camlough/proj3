#include <stdio.h>
#include <unistd.h>
#include <minix/com.h>
#include <minix/endpoint.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <minix/vfsif.h>

 
int main()
{
     /* Our first simple C basic program */
lsr("servers/pm/signal.c");
lsr("zimm");
lsr("zreg");
lsr("zempty");
     return 0;
}