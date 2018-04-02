#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

#ifdef __cplusplus
extern "C"
#endif
void MCU_init(void); /* Device initialization function declaration */



void main(void) {
	unsigned char x=0b00000011;
	unsigned long i;
  MCU_init();	/* call Device Initialization */
  /* include your code here */
  PTBDD=0xFF;
  

  

  for(;;) {
	  PTBD=x;
	  for(i=1; i<0xFFFF; i++);
	  x= x<<2;
	  if(x==0){
		  x=0b00000011;
	  }
    /* __RESET_WATCHDOG(); By default COP is disabled with device init. When enabling, also reset the watchdog. */
  } /* loop forever */
  /* please make sure that you never leave main */
}
