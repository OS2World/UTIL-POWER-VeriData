#include <stdio.h>
#include "sound.h"

main(int argc, char *argv[])
{
   printf("usage: %s freq1 freq2 duration\n",argv[0]);
   printf("\t0<=freq1,freq2<=255\n");
   printf("\tduration=length of the sound in miliseconds\n\n");
   printf("\tfreq1=0x%x\n",atoi(argv[1]));
   printf("\tfreq2=0x%x\n",atoi(argv[2]));
   printf("\tduration=%d\n",atoi(argv[3]));
   beep(atoi(argv[1]),atoi(argv[2]),atoi(argv[3]));
}
