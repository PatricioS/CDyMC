#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

#ifdef __cplusplus
extern "C"
#endif
void MCU_init(void); /* Device initialization function declaration */



void main(void) {
	unsigned char x= 0b00000001;
	unsigned char izq=0;
	unsigned char i;
  MCU_init();	/* call Device Initialization */
  PTBDD=0xFF;
  
  /* include your code here */

  

  for(;;) {
	  if(izq == 1){
		  if(x == 0b10000000){
			  PTBD=x;
			  x= x>>1;
			  izq=0;
		  }
		  else{
			  PTBD=x;
			  x=x<<2;
		  }
		  //for(i=0; i<0xFFFF; i++);
	  }
	  else{
		  if(x == 0b00000001){
			  PTBD=x;
			  x=x<<1;
			  izq=1;
		  }
		  else{
			  PTBD=x;
			  x= x>>2;
		  }
		  //for(i=0; i<0xFFFF; i++);
	  }
    /* __RESET_WATCHDOG(); By default COP is disabled with device init. When enabling, also reset the watchdog. */
  } /* loop forever */
  /* please make sure that you never leave main */
}
