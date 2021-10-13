#include <xc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void beginUSART(long BAUD)//Si no funciona cambiar por long
{                           //pines/bits
    TRISCbits.RC6 = 0;  //Bit de transmision "Tx" sera salida 
    TRISCbits.RC7 = 1;  //Bit de recepcion "Rx" sera entrada
    //Baudios
    SPBRG = (unsigned char)(((_XTAL_FREQ/BAUD)/64)-1);
                            //Modo
    TXSTAbits.BRGH = 0; //Modo asincrono en baja velocidad
    TXSTAbits.SYNC = 0; //Configuramos como modo asincrono
    RCSTAbits.SPEN = 1; //Habilitamos el puerto serial Tx y Rx  
                            //Transmision
    TXSTAbits.TX9 = 0;  //La transmision sera de 8 bits
    TXSTAbits.TXEN = 1; //Habilitamos la transmision
                            //Recepcion
    RCSTAbits.RC9 = 0;  //La recepcion sera de 8 bits
    RCSTAbits.CREN = 1; //Habilitamos la recepcion continua
}
void txCharUSART(char data)
{
    TXREG = data;
    while(TXSTAbits.TRMT == 0);
}
void txStringUSART(char *string)
{
    while(*string != 0x00)
    {
        txCharUSART(*string);
        string++;
    }
}
void txConstUSART(unsigned long _Variable)//En esta funcion introducimos una variable sin asignar su tipo aun 
{                                        //por si se da el caso de ser una variable entera o flotante
    char buffer[20];                     //Buffer de 16 bits, en el se sobreescribiran las variables enteras o flotantes
    sprintf(buffer,"%i",_Variable);      //Se transforman esas variables enteras a un string
    txStringUSART(buffer);                  //Imprimimos en el LCD el buffer donde ahi esta almacenado como string la variable
}
void txVarUSART(unsigned long _Variable, int digit)//En esta funcion introducimos una variable sin asignar su tipo aun 
{
    char buffer[20];
    switch(digit)
    {
        case 1:
            sprintf(buffer,"%1i",_Variable);      //Se transforman esas variables enteras a un string
            txStringUSART(buffer);                  //Imprimimos en el LCD el buffer donde ahi esta almacenado como string la variable
            break;
        case 2:
            sprintf(buffer,"%02i",_Variable);      //Se transforman esas variables enteras a un string
            txStringUSART(buffer);                  //Imprimimos en el LCD el buffer donde ahi esta almacenado como string la variable
            break;
        case 3:
            sprintf(buffer,"%03i",_Variable);      //Se transforman esas variables enteras a un string
            txStringUSART(buffer);                  //Imprimimos en el LCD el buffer donde ahi esta almacenado como string la variable
            break;
        case 4:
            sprintf(buffer,"%04i",_Variable);      //Se transforman esas variables enteras a un string
            txStringUSART(buffer);                  //Imprimimos en el LCD el buffer donde ahi esta almacenado como string la variable
            break;
        case 5:
            sprintf(buffer,"%05i",_Variable);      //Se transforman esas variables enteras a un string
            txStringUSART(buffer);                  //Imprimimos en el LCD el buffer donde ahi esta almacenado como string la variable
            break;
    }
}
void txFloatUSART(float _Variable)//En esta funcion introducimos una variable sin asignar su tipo aun 
{                                        //por si se da el caso de ser una variable entera o flotante
    char buffer[20];                     //Buffer de 16 bits, en el se sobreescribiran las variables enteras o flotantes
    sprintf(buffer,"%.2f",_Variable);      //Se transforman esas variables enteras a un string
    txStringUSART(buffer);                  //Imprimimos en el LCD el buffer donde ahi esta almacenado como string la variable
}
char rxCharUSART()
{ 
    return RCREG;
}
char rxStringUSART()
{
    char string[] = {RCREG};
        int i;
        for(i = 0;string[i]!='\0';i++)
        {
            return string[i];
        }
}
int serialAvailable()
{
    char c = rxCharUSART();
    __delay_ms(5);
    while(RCREG != c && RCREG != NULL)
    {
        return 1;
    }
    return 0;
}