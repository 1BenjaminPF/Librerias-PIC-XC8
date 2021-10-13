void beginADC()
{
    ADCON1bits.VCFG = 0;        //El voltaje de referencia sera tomado de la alimentacion del PIC "5V"
    
    ADCON0bits.GO_DONE = 0;     //Mantenemos el ADC en reposo (Sin hacer nada)
    ADCON0bits.ADON = 0;        //Aun no habilitamos el modulo ADC (Inhabilitado)
    
    ADCON2bits.ACQT = 0b010;    //Seleccionamos un tiempo de adiquisicion de 4TAD
    ADCON2bits.ADCS = 0b001;    //Un TAD es igual a 8 veces el periodo de oscilacion
    ADCON2bits.ADFM = 1;        //Justificamos a la derecha el resultado de la convercion
    
    ADCON0bits.ADON = 1;        //Habilitamos el modulo ADC
}
int adcReadBin(int ANx)
{
    switch(ANx)
    {
        case 0:
            ADCON1bits.PCFG = 0b1110;   //El bit 0 del puerto A como analogico AN0
            TRISAbits.RA0 = 1;
            ANx = 0b0000;
            break;
        case 1:
            ADCON1bits.PCFG = 0b1101;   //El bit 1 del puerto A como analogico AN1
            TRISAbits.RA1 = 1;
            ANx = 0b0001;
            break;
        case 2:
            ADCON1bits.PCFG = 0b1100;   //El bit 2 del puerto A como analogico AN2
            TRISAbits.RA2 = 1;
            ANx = 0b0010;
            break;
        case 3:
            ADCON1bits.PCFG = 0b1011;   //El bit 3 del puerto A como analogico AN3
            TRISAbits.RA3 = 1;
            ANx = 0b0011;
            break;
        case 4:
            ADCON1bits.PCFG = 0b1010;   //El bit 5 del puerto A como analogico AN4
            TRISAbits.RA5 = 1;
            ANx = 0b0100;
            break;
        case 5:
            ADCON1bits.PCFG = 0b1001;   //El bit 0 del puerto E como analogico AN5
            TRISEbits.RE0 = 1;
            ANx = 0b0101;
            break;
        case 6:
            ADCON1bits.PCFG = 0b1000;   //El bit 1 del puerto E como analogico AN6
            TRISEbits.RE1 = 1;
            ANx = 0b0110;
            break;
        case 7:
            ADCON1bits.PCFG = 0b0111;   //El bit 2 del puerto E como analogico AN7
            TRISEbits.RE2 = 1;
            ANx = 0b0111;
            break;
        case 8:
            ADCON1bits.PCFG = 0b0110;   //El bit 2 del puerto B como analogico AN8
            TRISBbits.RB2 = 1;
            ANx = 0b1000;
            break;
        case 9:
            ADCON1bits.PCFG = 0b0101;   //El bit 3 del puerto B como analogico AN9
            TRISBbits.RB3 = 1;
            ANx = 0b1001;
            break;
        case 10:
            ADCON1bits.PCFG = 0b0100;   //El bit 1 del puerto B como analogico AN10
            TRISBbits.RB1 = 1;
            ANx = 0b1010;
            break;
        case 11:
            ADCON1bits.PCFG = 0b0011;   //El bit 4 del puerto B como analogico AN11
            TRISBbits.RB4 = 1;
            ANx = 0b1011;
            break;
        case 12:
            ADCON1bits.PCFG = 0b0010;   //El bit 0 del puerto B como analogico AN12
            TRISBbits.RB0 = 1;
            ANx = 0b1100;
            break;
    }
    ADCON0bits.CHS = ANx;  
    ADCON0bits.GO_DONE = 1; //Habilitamos el ADC
    while(ADCON0bits.GO_DONE == 1);//Esperamos mientras en ADC este trabajando/convirtiendo
    __delay_ms(1);          //Retardo para procesar la convercion
    return ADRES;
}
float adcRead(int ANx)
{
    int ValBin = adcReadBin(ANx);
    float ValDec = (ValBin*5.0)/1023;
    return ValDec;
}