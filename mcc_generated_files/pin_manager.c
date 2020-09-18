/*???????????????????????void IOCBF7_ISR(void) ????????????????????*/

#include "pin_manager.h"




void (*IOCBF7_InterruptHandler)(void);


void PIN_MANAGER_Initialize(void)
{
    /**
    LATx registers
    */
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;

    /**
    TRISx registers
    */
    TRISA = 0x03;
    TRISB = 0x80;
    TRISC = 0x10;

    /**
    ANSELx registers
    */
    ANSELC = 0x00;
    ANSELB = 0x00;
    ANSELA = 0x03;

    /**
    WPUx registers
    */
    WPUB = 0x00;
    WPUA = 0x00;
    WPUC = 0x00;
    OPTION_REGbits.nWPUEN = 1;

    /**
    ODx registers
    */
    ODCONA = 0x00;
    ODCONB = 0x00;
    ODCONC = 0x00;

    /**
    SLRCONx registers
    */
    SLRCONA = 0x37;
    SLRCONB = 0xF0;
    SLRCONC = 0xFF;

    /**
    INLVLx registers
    */
    INLVLA = 0x3F;
    INLVLB = 0xF0;
    INLVLC = 0xFF;


    /**
    IOCx registers 
    */
    //interrupt on change for group IOCBF - flag
    IOCBFbits.IOCBF7 = 0;
    //interrupt on change for group IOCBN - negative
    IOCBNbits.IOCBN7 = 0;
    //interrupt on change for group IOCBP - positive
    IOCBPbits.IOCBP7 = 1;



    // register default IOC callback functions at runtime; use these methods to register a custom function
    IOCBF7_SetInterruptHandler(IOCBF7_DefaultInterruptHandler);
   
    // Enable IOCI interrupt 
    INTCONbits.IOCIE = 1; 
    
}
  
void PIN_MANAGER_IOC(void)
{   
	// interrupt on change for pin IOCBF7
    if(IOCBFbits.IOCBF7 == 1)
    {
        IOCBF7_ISR();  
    }	
}

/**
 PB??????????????
*/
void IOCBF7_ISR(void) {

    // ?????

    // Call the interrupt handler for the callback registered at runtime
    if(IOCBF7_InterruptHandler)
    {
        IOCBF7_InterruptHandler();
    }
    IOCBFbits.IOCBF7 = 0;
}

/**
  Allows selecting an interrupt handler for IOCBF7 at application runtime
*/
void IOCBF7_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCBF7_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCBF7
*/
void IOCBF7_DefaultInterruptHandler(void){
    // add your IOCBF7 interrupt custom code
    // or set custom function using IOCBF7_SetInterruptHandler()
}

/**
 End of File
*/