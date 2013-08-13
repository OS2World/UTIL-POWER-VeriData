/*
 * vmode.c (utilities for the Veridata EL-486S/25e notebook)
 * Time-stamp: <04 Aug 94 (15:07:59) by pive@ruca.ua.ac.be>
 */

#include <stdio.h>
#include <unistd.h>
#include "veridata.h"

void usage(char *name)
{
   fprintf(stderr,"Usage: %s ",name);
   fprintf(stderr,"-b on|off -i on|off -s on|off -t on|off -d timeout -h\n");
   fprintf(stderr,"\t-b -> backlight\n");
   fprintf(stderr,"\t-i -> inverse video\n");
   fprintf(stderr,"\t-s -> serial port 0\n");
   fprintf(stderr,"\t-t -> turbo mode (why would you use this?)\n");
   fprintf(stderr,"\t-d -> harddisk timeout value in seconds\n");
   fprintf(stderr,"\t      (0<= timeout <= 1200) (0 is no timeout)\n");
   fprintf(stderr,"\t-h -> this screen\n");
}

void print_status()
{
   unsigned int status;

   status=_inp8(VERIDATA_PORT);
   printf("notebook status:\n");
   printf("\tturbo mode:\t%s\n",(status&CPU_FAST)?"on":"off");
   printf("\tbacklight:\t%s\n",(status&BACKLIGHT_ON)?"on":"off");
   printf("\tserial 0:\t%s\n",(status&COM1_ENABLE)?"enabled":"disabled");
   printf("\tvideo mode:\t%s\n",(status&INVERSE_ON)?"inverse":"normal");
   /* it works, but is not usefull
   printf("\tblank mode:\t%s\n",(status&BLANK_OFF)?"normal":"blank");
   */
   printf("\tpower mode:\t%s\n",(status&POWER_EXT)?"extern":"intern");
   printf("\tpower level:\t");
   switch (status & POWER_MASK) {
   case POWER_OK:
      printf("ok\n"); 
      break;
   case POWER_LVL1:
      printf("level 1\n"); 
      break;
   case POWER_LVL2:
      printf("level 2\n"); 
      break;
   }
}

main(int argc, char *argv[])
{
   unsigned int status,i;
   int          sec;
   extern char  *optarg;
   extern int   optind;

   /* initialise the status variable, clear bit 6 and 7 */
   status=_inp8(VERIDATA_PORT) & SAFETY_MASK;

   /* parse the commandline arguments */
   while ((i=getopt(argc,argv,"b:d:i:s:t:h")) != -1)
      switch(i) {
      case 'b':
        if (!strcmp(optarg,"off"))
           status &= ~BACKLIGHT_ON;
        else
           status |= BACKLIGHT_ON;
        break;
      case 'd':
        if ((sscanf(optarg,"%i",&sec)) && (0 <= sec) && (sec <= 1200)) {
           sec=sec/5;
           _outp8(sec,HDD_TIMEOUT_PORT);
           _outp8(HDD_NOTIFY_VALUE,HDD_NOTIFY_PORT);
           printf("Using new harddisk timeout: %i sec\n",sec*5);
        } else {
           usage(argv[0]);
           exit(0);
        }
        break;
      case 'i':
        if (!strcmp(optarg,"off"))
           status &= ~INVERSE_ON;
        else
           status |= INVERSE_ON;
        break;
      case 's':
        if (!strcmp(optarg,"off"))
           status &= ~COM1_ENABLE;
        else
           status |= COM1_ENABLE;
        break;
      case 't': 
        if (!strcmp(optarg,"off")) {
           printf("Why on earth, would you use this?\n");
           status &= ~CPU_FAST;
        } else
           status |= CPU_FAST;
        break;
      case 'h':
      default:
        usage(argv[0]);
        exit(0);
      }
   _outp8(VERIDATA_PORT,status);
   print_status();
}
