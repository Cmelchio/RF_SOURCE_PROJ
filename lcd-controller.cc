#include "lcd-controller.h"
#include <msp430g2553.h>
#include <stdint.h>



//-------------------------------------ENCODER-----------------------------------------------------------
void LCDController::EncoderSetup() {

    P1DIR   |= ~(ENC_CW + ENC_CCW + ENC_PB);
    P1REN   |= ENC_CW + ENC_CCW + ENC_PB;                // Enable internal pull-up/down resistors
    P1OUT   |= ENC_CW + ENC_CCW + ENC_PB;                   //Select pull-up mode for P1.3
    P1IE    |= ENC_CW + ENC_CCW + ENC_PB;                       // P1.3 interrupt enabled
    P1IES   |= ENC_CW + ENC_CCW + ENC_PB;                    // P1.3 Hi/lo edge
    P1IFG   &= ~(ENC_CW + ENC_CCW + ENC_PB);               // P1.3 IFG cleared

}

int LCDController::EncoderRead() {
    static int8_t   ENC_STATES[] =  {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
    uint8_t PREV_STATE = 0;
    PREV_STATE <<= 2;
    PREV_STATE = ENC_PINS;

    return (ENC_STATES[PREV_STATE & 0x0f]);
}


//-------------------------------------LCD DISPLAY-----------------------------------------------------------

/*Function for initializing the LCD pins and resetting the display*/
void LCDController::LCDInit()
{
    P2DIR |= 0xE0;
    P2OUT |= 0x00;
    SendCommand(LCDController::FOUR_BITS_TWO_LINES);


}

void LCDController::EnableNybble() {

    ENABLE_HIGH;
    //Delay(2);
    ENABLE_LOW;
}

/*Function used to check the state of the LCD*/
void LCDController::CheckBusy(void)
{
    P2DIR &= ~(BIT7);   // make P2.7 as input
    while((P2IN&BIT7)==1)
        {
        LCDController::EnableNybble();
        }
    P2DIR |= BIT7;  // make P2.7 as output
}

/*Function for giveing specific commands to the LCD*/
void LCDController::SendCommand(unsigned char cmd)
{

    //CheckBusy();
    RW_WRITE;
    RS_CWR;
    P2OUT = (P2OUT & 0x00)|(cmd);
    EnableNybble();   // give enable trigge
}

/*Function for writing a char value to the LCD*/
void LCDController::SendData(unsigned char data)
{
    CheckBusy();
    RW_WRITE;
    RS_DR;
    P2OUT = (P2OUT & 0x00)|(data);
    EnableNybble();

}



//-------------------------------------GENERAL FUNCTIONS-----------------------------------------------------------
void LCDController::UnusedPorts() {
    P3DIR = 0;
    P3OUT = 0;

}

void LCDController::Delay_uS(int n){

    const int ONE_uS = 2;
    COUNT_uS = n * ONE_uS;
    TA0CCR0 = COUNT_uS;

    return;

}

void LCDController::Delay_mS(int n){

    const int ONE_mS = 2000;
    COUNT_mS = n * ONE_mS;
    TA0CCR0 = COUNT_mS;

    return;
}




