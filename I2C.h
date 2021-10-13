#include <stdio.h>
#include <string.h>
#define TRIS_SDA TRISBbits.RB0
#define TRIS_SCL TRISBbits.RB1
/////////////////////////protocolo i2c MAESTRO//////////////////////////////////
void i2cBegin()
{
    TRIS_SCL = 1;
    TRIS_SDA = 1;
    SSPSTATbits.CKE = 0;
    SSPSTATbits.SMP = 1;        //Configuramos la velocidad de respuesta estandar que es a 100KHz
    SSPCON1bits.SSPEN = 1;      //Señalamos que utilizaremos el SDA y SCL
    SSPCON1bits.SSPM = 0b1000;  //Configuramos como modo MAESTRO
    SSPCON2 = 0x00;             //Inhabilitamos este registro
    SSPADD = 49;                //100Kbps
}
void i2cStart()
{
    SSPCON2bits.SEN = 1;        //Inicia la transmision
    while(SSPCON2bits.SEN == 1);//Retardo mientras sea igual a 1
}
void i2cStop()
{
    SSPCON2bits.PEN = 1;        //Para la transmision
    while(SSPCON2bits.PEN == 1);//Retardo mientras sea igual a 1
}
void i2cRestart()
{
    SSPCON2bits.RSEN = 1;       //Reenvio de datos
    while(SSPCON2bits.RSEN == 1);//Retardo mientras sea igual a 1
}
void i2cACK()
{
    PIR1bits.SSPIF = 0;
    SSPCON2bits.ACKDT = 0;      //ACK
    SSPCON2bits.ACKEN = 1;      //Habilitar ACK
    while(PIR1bits.SSPIF == 0);
}
void i2cNACK()
{
    PIR1bits.SSPIF = 0;
    SSPCON2bits.ACKDT = 1;      //NACK
    SSPCON2bits.ACKEN = 1;      //Habilitar NACK
    while(PIR1bits.SSPIF == 0); //Retardo mientras sea igual a 0
}
void i2cTraData(char data)
{
    PIR1bits.SSPIF = 0;
    SSPBUF = data;
    while(PIR1bits.SSPIF == 0); //Retardo mientras sea igual a 0
}
char i2cResData()
{
    PIR1bits.SSPIF = 0;
    SSPCON2bits.RCEN = 1;       //Habilitamos la recepcion
    while(PIR1bits.SSPIF == 0); //Retardo mientras sea igual a 0
    return SSPBUF;
}
/////////////////////////protocolo i2c ESCLAVO//////////////////////////////////