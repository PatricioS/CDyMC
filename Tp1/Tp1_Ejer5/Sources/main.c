#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

#ifdef __cplusplus
extern "C"
#endif

void Izq(char *direIzq, char *a, char i);
void Der(char *direDer, char *b, char i);

void MCU_init(void); /* Device initialization function declaration */



void Der(char *direDer, char *a, char i){//a ingresa con el terminal 0 en 1... Y dire ingresa con el valor 0
	if(*direDer == 1){ //Si dire =1 se mueve entre los terminales IMPARES (1,3,5,7)
		if(*a == 0b10000000){
			PTBD= *a;
			*a= *a>>1;
			*direDer= 0;
		}
		else{
			PTBD= *a;
			*a= *a<<2;
		}
		for(i=0; i<0xFFFF; i++); //retraso para que se vean los leds si direDer es =1
	}
	else{  //Si dire =0 se mueve entre los terminales PARES (6,4,2,0)
		if(*a == 0b00000001){
			PTBD= *a;
			*a= *a<<1;
			*direDer= 1;
		}
		else{
			PTBD= *a;
			*a= *a>>2;
		}
		for(i=0; i<0xFFFF; i++); //retraso para que se vean los leds si direDer=0
	}
}

void Izq (char *direIzq, char *b, char i){ //b ingresa con el terminal 0 en 1... Y dire ingresa con el valor 0
	
	if(*direIzq == 0){ //Si dire es = 0, se mueve entre los terminales PARES (0,2,4,6)
		if(*b == 0b01000000){
			PTBD= *b;
			*b= *b<<1;
			*direIzq= 1;
		}
		else{
			PTBD= *b;
			*b=*b<<2;
		}
		for(i=0; i<0xFFFF; i++); //Retraso para que se vean los leds si direIzq= 1
	}
	else{  //Si dire es =1, se mueve entre los terminales impares (7,5,3,1)//
		if(*b == 0b00000010){
			PTBD= *b;
			*b= *b>>1;
			*direIzq=0;
		}
		else{
			PTBD= *b;
			*b= *b>>2;
		}
		for(i=0; i<0xFFFF; i++); //Retraso para que se vean los leds si direIzq= 0
	}
}


void main(void) {
	unsigned char a= 0b00000001;
	unsigned char b= 0b00000001;
	unsigned char direccionIzq=0;
	unsigned char direccionDer=0;
	unsigned char i;
  MCU_init();	/* call Device Initialization */
  PTBDD=0xFF;
  PTCDD_PTCDD0=0;
 
  /* include your code here */

  

  for(;;) {
	  if(PTCD_PTCD0 == 0){ //el boton se activa en 0
		  for(i=0; i<0xFF; i++); //retraso para el ruido del boton
		  while(PTCD_PTCD0 == 0){
			  Izq(&direccionIzq, &a, i);
		  }
	  }
	  else{
		  Der(&direccionDer, &b, i);
	  }  
    /* __RESET_WATCHDOG(); By default COP is disabled with device init. When enabling, also reset the watchdog. */
  } /* loop forever */
  /* please make sure that you never leave main */
}


