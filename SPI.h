#define SPI_Clook_4     0   //La velocidad de transmicion sera la velocidad del relog entre 4
#define SPI_Clook_16    1   //La velocidad de transmicion sera la velocidad del relog entre 16
#define SPI_Clook_64    2   //La velocidad de transmicion sera la velocidad del relog entre 64
#define SPI_Timer2      3   //La velocidad de transmicion sera la velocidad del Timer2

#define SPI_Slave_R5    4   //Usamos el PIC en modo esclavo y habiliramos el pin RA5 
#define SPI_Slave_IO    5   //Usamos el PIC en modo esclavo

#define Mode_1  '1'         //Modo de reloj 1
#define Mode_2  '2'         //Modo de reloj 2
#define Mode_3  '3'         //Modo de reloj 3
#define Mode_4  '4'         //Modo de reloj 4

#define Data_Mitad  0       //Leemos los datos a la mitar del pulso de reloj
#define Data_Fin    1       //Leemos los datos al final del puslo de reloj

void spiBeginMaster(char clook, char modo, char smp)
{
    ADCON1 = 0xFF;      //Todos los bits AN como digitales 
    TRISBbits.RB0 = 1;  //SDI como entrada
    TRISBbits.RB1 = 0;  //SCK como salida 
    TRISAbits.RA5 = 0;  //SS como salida 
    TRISCbits.RC7 = 0;  //SDO como salida 
    SSPCON1bits.SSPM = clook;
    if(modo == '1')
    {
        SSPCON1bits.CKP = 1;    
        SSPSTATbits.CKE = 1;    
    }
    else if(modo == '2')
    {
        SSPCON1bits.CKP = 0;    
        SSPSTATbits.CKE = 1;
    }
    else if(modo == '3')
    {
        SSPCON1bits.CKP = 1;    
        SSPSTATbits.CKE = 0;
    }
    else if(modo == '4')
    {
        SSPCON1bits.CKP = 1;    
        SSPSTATbits.CKE = 1;
    }
    SSPSTATbits.SMP = smp;
    SSPCON1bits.SSPEN = 1;  //Habilitacion de pines
}
void spiBeginSlave(char pinSlave,char modo)
{
    ADCON1 = 0xFF;      //Todos los bits AN como digitales 
    TRISBbits.RB0 = 1;  //SDI como entrada
    TRISBbits.RB1 = 1;  //SCK como entrada 
    TRISAbits.RA5 = 1;  //SS como entrada 
    TRISCbits.RC7 = 0;  //SDO como salida 
    SSPCON1bits.SSPM = pinSlave;
    if(modo == '1')
    {
        SSPCON1bits.CKP = 1;    
        SSPSTATbits.CKE = 1;    
    }
    else if(modo == '2')
    {
        SSPCON1bits.CKP = 0;    
        SSPSTATbits.CKE = 1;
    }
    else if(modo == '3')
    {
        SSPCON1bits.CKP = 1;    
        SSPSTATbits.CKE = 0;
    }
    else if(modo == '4')
    {
        SSPCON1bits.CKP = 1;    
        SSPSTATbits.CKE = 1;
    }
    SSPCON1bits.SSPEN = 1;  //Habilitacion de pines
}
void spiWrite(char dato)
{
    SSPBUF = dato;
}
char spiRead()
{
    return SSPBUF;
}

