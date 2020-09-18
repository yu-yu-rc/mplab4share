
#include <xc.h>
#include "tmr0.h"
#include "mcc.h"


#define BAR0 0b00100000
#define BAR1 0b00010000
#define BAR2 0b00100000
#define BAR3 0b00000100
#define BAR4 0b00000001
#define BAR5 0b00000010
#define BAR6 0b00000100
#define BAR7 0b00010000
#define BAR8 0b00100000
#define BAR9 0b01000000


/**
  Section: Global Variables Definitions
*/


volatile uint8_t timer0ReloadVal;
void (*TMR0_InterruptHandler)(void);
/**
  Section: TMR0 APIs
*/


void TMR0_Initialize(void)
{
    // Set TMR0 to the options selected in the User Interface
    
    // PSA assigned; PS 1:16; TMRSE Increment_hi_lo; mask the nWPUEN and INTEDG bits
    OPTION_REG = (uint8_t)((OPTION_REG & 0xC0) | (0xD3 & 0x3F)); 
    
    // TMR0 131; 
    TMR0 = 0x83;
    
    // Load the TMR value to reload variable
    timer0ReloadVal= 131;


    // Clear Interrupt flag before enabling the interrupt
    INTCONbits.TMR0IF = 0;


    // Enabling TMR0 interrupt
    INTCONbits.TMR0IE = 1;


    // Set Default Interrupt Handler
    TMR0_SetInterruptHandler(TMR0_DefaultInterruptHandler);
}


uint8_t TMR0_ReadTimer(void)
{
    uint8_t readVal;


    readVal = TMR0;


    return readVal;
}


void TMR0_WriteTimer(uint8_t timerVal)
{
    // Write to the Timer0 register
    TMR0 = timerVal;
}


void TMR0_Reload(void)
{
    // Write to the Timer0 register
    TMR0 = timer0ReloadVal;
}

void RGB(int row, char col, char bar){
    char color;
    char judge_red = 0, judge_green = 0, judge_blue = 0;

            judge_red = red[row][col] & bar;
            judge_green = green[row][col] & bar;
            judge_blue = blue[row][col] & bar;
            if(judge_red && judge_green && judge_blue){
                IO_RC3_SetHigh();
                IO_RC6_SetHigh();
                IO_RC7_SetHigh();
            }else if(judge_red && judge_green){
                IO_RC3_SetHigh();
                IO_RC6_SetHigh();
                IO_RC7_SetLow();
            }else if(judge_red && judge_blue){
                IO_RC3_SetHigh();
                IO_RC6_SetLow();
                IO_RC7_SetHigh();
            }else if(judge_blue && judge_green){
                IO_RC3_SetLow();
                IO_RC6_SetHigh();
                IO_RC7_SetHigh();
            }else if(judge_red){
                IO_RC3_SetHigh();
                IO_RC6_SetLow();
                IO_RC7_SetLow();
            }else if(judge_green){
                IO_RC3_SetLow();
                IO_RC6_SetHigh();
                IO_RC7_SetLow();
            }else if(judge_blue){
                IO_RC3_SetLow();
                IO_RC6_SetLow();
                IO_RC7_SetHigh();
            }else{
                IO_RC3_SetLow();
                IO_RC6_SetLow();
                IO_RC7_SetLow();
            }
    
}

//?????
void TMR0_ISR(void)
{
    static char i = 0;
    static short j = 0;
    
    switch(i){
        case 0:
            RGB(j, 2, BAR0);
            LATC = red[j][2] & BAR0;
            break;
        case 1:
            RGB(j, 0, BAR1);
            LATA = red[j][0] & BAR1;
            break;
        case 2:
            RGB(j, 0, BAR2);
            LATA = red[j][0] & BAR2;
            break;
        case 3:
            RGB(j, 0, BAR3);
            LATA = red[j][0] & BAR3;
            break;
        case 4:
            RGB(j, 2, BAR4);
            LATC = red[j][2] & BAR4;
            break;
        case 5:
            RGB(j, 2, BAR5);
            LATC = red[j][2] & BAR5;
            break;
        case 6:
            RGB(j, 2, BAR6);
            LATC = red[j][2] & BAR6;
            break;
        case 7:
            RGB(j, 1, BAR7);
            LATB = red[j][1] & BAR7;
            break;
        case 8:
            RGB(j, 1, BAR8);
            LATB = red[j][1] & BAR8;
            break;
        case 9:
            RGB(j, 1, BAR9);
            LATB = red[j][1] & BAR9;
            break; 
    }
    
    i++;
    j++;
    if(i > 9)
        i = 0;
    if(j > 180)
        j = 0;
    INTCONbits.TMR0IF = 0; //??????
    


    TMR0 = timer0ReloadVal; //????


    // ticker function call;
    // ticker is 1 -> Callback function gets called every time this ISR executes
    TMR0_CallBack();


    // add your TMR0 interrupt custom code
}


void TMR0_CallBack(void)
{
    // Add your custom callback code here


    if(TMR0_InterruptHandler)
    {
        TMR0_InterruptHandler();
    }
}


void TMR0_SetInterruptHandler(void (* InterruptHandler)(void)){
    TMR0_InterruptHandler = InterruptHandler;
}


void TMR0_DefaultInterruptHandler(void){
    // add your TMR0 interrupt custom code
    // or set custom function using TMR0_SetInterruptHandler()
}


/**
  End of File
**/