/*
 * veridata.h (magic numbers of the Veridata EL-486S/25e notebook)
 */

#define HDD_TIMEOUT_PORT 0x01f2 /* port used to send the harddisk timeout value to */
#define HDD_NOTIFY_PORT  0x01f7 /* port used to activate the new value */
#define HDD_NOTIFY_VALUE 0xe3   /* value to send to HDD_NOTIFY_PORT to activate the new value */
/* note: there is no way get the current value of the harddisk */

#define VERIDATA_PORT   0x05f0 /* port used for "powersaving" instructions */

/*
 * out VERIDATA_PORT,value:
 *   
 * effect  | speed | backlight | COM1 | inverse | blank  | ? | ? | bat. led
 * bit nr  |   1   |    2      |  3   |    4    |   5    | 6 | 7 |     8   
 * ------------------------------------------------------------------------
 *   1     | turbo |    on     |  on  | inverse | normal |   |   |    off   
 *   0     | slow  |    off    |  off | normal  | blank  |   |   |    on    
 *
 * ! if you switch from blank screen to normal screen, then backlight is
 *   always wrong.
 *   to blankscreen: backlight=off + blank=blank
 *   to unblankscreen: blank=normal + backlight=previous state (you have
 *                     remember the state yourself)
 *
 * We will put (bit 6)=0 and (bit 7)=0 (since the BIOS does this also 
 * in MS-DOS), so you should use (value & SAFETY_MASK)
 *
 *
 * in VERIDATA_PORT,value:
 *   
 * effect  | speed | backlight | COM1 | inverse | blank  | source | power
 * bit nr  |   1   |    2      |  3   |    4    |   5    |    6   |  7-8!
 * ----------------------------------------------------------------------
 *   1     | turbo |    on     |  on  | inverse | normal | extern | 
 *   0     | slow  |    of     |  off | normal  | blank  | intern |
 *
 * ! power status
 * ---------------------
 *   7  |   8   | status
 * ---------------------
 *   1  |   1   | ok
 *   1  |   0   | level1
 *   0  |   0   | level2
 */

#define SAFETY_MASK   0xf9   /* 11111001 */

#define CPU_FAST      0x80   /* 10000000 */
#define BACKLIGHT_ON  0x40   /* 01000000 */
#define COM1_ENABLE   0x20   /* 00100000 */
#define INVERSE_ON    0x10   /* 00010000 */
#define BLANK_OFF     0x08   /* 00001000 */
#define POWER_EXT     0x04   /* 00000100 */
#define BAT_LOW_OFF   0x01   /* 00000001 */

#define POWER_MASK    0x03   /* 00000011 */
#define POWER_OK      0x03   /* 00000011 */
#define POWER_LVL1    0x02   /* 00000010 */
#define POWER_LVL2    0x00   /* 00000000 */

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
