#ifndef RF_GENERATOR_LCD_CONTROLLER_H_
#define RF_GENERATOR_LCD_CONTROLLER_H_

#define TIMER_A0_COUNT  65535;
#define TIMER_ENABLE_COUNT 1000;
#define ENC_CW  BIT3
#define ENC_CCW BIT4
#define ENC_PB  BIT5
#define ENC_PINS P1IN |= (ENC_CW + ENC_CCW + ENC_PB);
#define RS_DR P2OUT = P2OUT | BIT2 // define RS high
#define RS_CWR P2OUT = P2OUT & (~BIT2) // define RS low
#define RW_READ P2OUT = P2OUT | BIT1 // define Read signal R/W = 1 for reading
#define RW_WRITE P2OUT = P2OUT & (~BIT1) // define Write signal R/W = 0 for writing
#define ENABLE_HIGH P2OUT = P2OUT | BIT0 // define Enable high signal
#define ENABLE_LOW P2OUT = P2OUT & (~BIT0) // define Enable Low signal
#define LCD_DB = BIT3 | BIT4 | BIT5 | BIT6




class LCDController {
  public:

    static void EnableNybble();
    static void Delay_mS(int);
    static void Delay_uS(int);
    static void CheckBusy();
    static void SendCommand(unsigned char);
    static void SendData(unsigned char);
    static void SendString(char*);
    static void LCDInit();

    int  EncoderRead();
    static void EncoderSetup();
    static void UnusedPorts();
    void EncoderLoop();


  private:

    static const unsigned char FOUR_BITS_TWO_LINES = 0x28;
    static const unsigned char SET_CURSOR = 0x10;
    static const unsigned char SET_BLINKING_CURSOR = 0x0F;
    static const unsigned char SET_ENTRY_MODE = 0x06;

    static bool ENC_CW_FLAG;
    static bool ENC_CCW_FLAG;
    static bool ENC_PB_FLAG;
    static int  COUNT_uS;
    static int  COUNT_mS;

};


#endif /* RF_GENERATOR_LCD_CONTROLLER_H_ */
