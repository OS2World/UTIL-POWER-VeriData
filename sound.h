/*
 * sound.h: sound utilities + definitions
 */

#define FREQ_PROG_PORT 0x42 /* port to program the frequentie */
#define FREQ_INIT_PORT 0x43 /* port to initialise the freq. programming */
#define SOUND_PORT     0x61 /* port used to put the sound on/off */

#define FREQ_INIT 0xb6 /* send to the FREQ_INIT_PORT */
#define SOUND_ON  0x03 /* send to SOUND_PORT to enable sound */
#define SOUND_OFF 0xfc /* send to SOUND_PORT to disable sound */

#define beep(freq1,freq2,duration)\
        _outp8(FREQ_INIT_PORT,FREQ_INIT);\
        _outp8(FREQ_PROG_PORT,freq1);\
        _outp8(FREQ_PROG_PORT,freq2);\
        _outp8(SOUND_PORT,_inp8(SOUND_PORT) | SOUND_ON);\
        _sleep2(duration);\
        _outp8(SOUND_PORT,_inp8(SOUND_PORT) & SOUND_OFF);
