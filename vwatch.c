/*
 * vwatch.c (monitor the power status of the Veridata EL-486S/25e notebook)
 */

#include "veridata.h"
#include "sound.h"

main()
{
   unsigned int status,
                level1_cnt, /* beep in level1 if this becomes 0 */
                led_on;     /* true if "Bat. Low" led is on */

   /* make sure we are in a known state */
   status=_inp8(VERIDATA_PORT) & SAFETY_MASK | BAT_LOW_OFF;
   _outp8(VERIDATA_PORT,status);
   led_on=FALSE;
   level1_cnt=0;
  
   while (TRUE) {
      status=_inp8(VERIDATA_PORT);
      switch (status & POWER_MASK) {
      case POWER_OK:
         if (led_on) {
            _outp8(VERIDATA_PORT,status | BAT_LOW_OFF & SAFETY_MASK);
            led_on=FALSE;
         } 
         break;
      case POWER_LVL1:
         if (level1_cnt == 0) {
            level1_cnt=4;
            beep(0xc8,0x02,50);
         } else {
            level1_cnt--;
         }
         if (led_on) {
            _outp8(VERIDATA_PORT,status | BAT_LOW_OFF & SAFETY_MASK);
            led_on=FALSE;
         } else {
            led_on=TRUE;
            _outp8(VERIDATA_PORT,status & ~BAT_LOW_OFF & SAFETY_MASK);
         }
         break;
      case POWER_LVL2:
         beep(0x50,0x02,50);
         if (!led_on) {
            led_on=TRUE;
            _outp8(VERIDATA_PORT,status & ~BAT_LOW_OFF & SAFETY_MASK);
         }
         break;
      }
    sleep(1);
  }
}
