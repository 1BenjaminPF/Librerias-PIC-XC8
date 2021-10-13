void beginPWM(int CCPx)
{
    if(CCPx == 1)
        TRISCbits.RC2 = 0;  //Establece el pin RC2 como salida correspondiente al modulo CCP1
    if(CCPx == 2)
        TRISCbits.RC1 = 0;  //Establece el pin RC1 como salida correspondiente al modulo CCP2
}
void writePWM(int CCPx, int DutyCicle)
{
//  PR2 =((1/FrecDeseada)/(1/FreqDeCrystal)*4*16)-1
//  Duty Cycle = ((1/FrecDeseada)/(1/FreqDeCrystal)*16)*DutyCycle
    int freq = 1200;//No cambiar, sea cual sea el valor de freq, la frecuencia siempre sera 1200 aprox
    int periodo = ((1/freq)/(1/_XTAL_FREQ)*4*16)-1;
    int pwm = (1024/100)*DutyCicle;
    PR2 = periodo;
    T2CONbits.T2CKPS = 0b10;    //Establece a 16 al preescaler del temporizador 2
    T2CONbits.TMR2ON = 1;       //Enciende el temporizador 2
    switch(CCPx)
    {
        case 1:
            CCPR1L = pwm>>2;            //Carga el valor de CCPR1L (Ciclo de trabajo) del PPC1
            CCP1CONbits.DC1B = pwm;     //Carga el valor de DC1B (Ciclo de trabajo) del CCP1
            CCP1CONbits.CCP1M = 0b1100; //Configura en modo PWM al modulo CCP1
            break;
        case 2:
            CCPR2L = pwm>>2;            //Carga el valor de CCPR2L (Ciclo de trabajo) del CCP2
            CCP2CONbits.DC2B = pwm;     //Carga el valor de DC2B (Ciclo de trabajo) del CCP2
            CCP2CONbits.CCP2M = 0b1100; //Configura en modo PWM al modulo CCP2
            break;
    }
}