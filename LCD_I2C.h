#include <stdio.h>
#include <string.h>
#define E   0b00000100
#define LED 0b00001000  //Se suma cuando se envia un comando y un caracter para encender el BackLight del LCD "Luz de fondo"
#define RS  0b00000001
void CMD(char ADRESS,char data)
{
    i2cStart();
    i2cTraData(ADRESS);
    i2cTraData(data+E+LED);
    __delay_ms(2);
    i2cTraData(data);
    i2cStop();
}
void lcdBeginI2C(char ADRESS)
{
    for(int i=0;i<3;i++)       //
    {                          //Realizamos los 3 colsos con el
        CMD(ADRESS,0b00110000);//comando inicial necesario
    }                          //
    ////////////////////////////////////////////////////////////////////////////    
                           //A partir de este momento configuramos
    CMD(ADRESS,0b00100000);//que los datos los enviaremos de
                           //4 en 4 trabajaremos con 4 bits 
    ////////////////////////////////////////////////////////////////////////////
    CMD(ADRESS,0b00100000);//Configiramos que usaremos las 2 lineasdel LCD y que
    CMD(ADRESS,0b11000000);//trabajaremos con la fuente grande de las letras
    ////////////////////////////////////////////////////////////////////////////
    CMD(ADRESS,0b00000000);//Se apaga el LCD y se 
    CMD(ADRESS,0b10000000);//reinicia su configuracion
    ////////////////////////////////////////////////////////////////////////////
    CMD(ADRESS,0b00000000);//Se apaga el display y regresa
    CMD(ADRESS,0b00010000);//a la posicion de inicio
    ////////////////////////////////////////////////////////////////////////////
    CMD(ADRESS,0b00000000);//Con esto procedemos a encender el LCD y
    CMD(ADRESS,0b01100000);//tambien indicamos que visualizaremos
    CMD(ADRESS,0b00000000);//el cursor y este tendra un blink y que
    CMD(ADRESS,0b11110000); //este se desplazara a la derecha
}
void lcdWriteCharI2C(char ADRESS, char caracter)
{
    i2cStart();
    i2cTraData(ADRESS);
    
    char caracterH, caracterL;
    caracterH = caracter&0b11110000;
    caracterL = caracter&0b00001111;
    caracterL = caracterL<<4;   
    ////////////////////////////////////////////////////////////////////////////
    i2cTraData(caracterH+E+RS+LED);//Se envia la parte alta
    __delay_ms(1);
    i2cTraData(caracterH+RS+LED);//Se envia la parte alta
    __delay_ms(1);
    ////////////////////////////////////////////////////////////////////////////
    i2cTraData(caracterL+E+RS+LED);//Se envia la parte alta
    __delay_ms(1);
    i2cTraData(caracterL+RS+LED);//Se envia la parte alta
    __delay_ms(1);
    ////////////////////////////////////////////////////////////////////////////
    i2cStop();
}
void lcdWriteStringI2C(char ADRESS,char *string)
{
   int i;
   for(i=0;string[i]!='\0';i++)
      lcdWriteCharI2C(ADRESS,string[i]);
}
void lcdWriteConstI2C(char ADRESS,unsigned long _Variable)//En esta funcion introducimos una variable sin asignar su tipo aun 
{                                        //por si se da el caso de ser una variable entera o flotante
    char buffer[20];                     //Buffer de 16 bits, en el se sobreescribiran las variables enteras o flotantes
    sprintf(buffer,"%i",_Variable);      //Se transforman esas variables enteras a un string
    lcdWriteStringI2C(ADRESS,buffer);                  //Imprimimos en el LCD el buffer donde ahi esta almacenado como string la variable
}
void lcdWriteVarI2C(char ADRESS, unsigned long _Variable, int digit)//En esta funcion introducimos una variable sin asignar su tipo aun 
{
    char buffer[20];
    switch(digit)
    {
        case 1:
            sprintf(buffer,"%1i",_Variable);      //Se transforman esas variables enteras a un string
            lcdWriteStringI2C(ADRESS,buffer);                  //Imprimimos en el LCD el buffer donde ahi esta almacenado como string la variable
            break;
        case 2:
            sprintf(buffer,"%02i",_Variable);      //Se transforman esas variables enteras a un string
            lcdWriteStringI2C(ADRESS,buffer);                  //Imprimimos en el LCD el buffer donde ahi esta almacenado como string la variable
            break;
        case 3:
            sprintf(buffer,"%03i",_Variable);      //Se transforman esas variables enteras a un string
            lcdWriteStringI2C(ADRESS,buffer);                  //Imprimimos en el LCD el buffer donde ahi esta almacenado como string la variable
            break;
        case 4:
            sprintf(buffer,"%04i",_Variable);      //Se transforman esas variables enteras a un string
            lcdWriteStringI2C(ADRESS,buffer);                  //Imprimimos en el LCD el buffer donde ahi esta almacenado como string la variable
            break;
        case 5:
            sprintf(buffer,"%05i",_Variable);      //Se transforman esas variables enteras a un string
            lcdWriteStringI2C(ADRESS,buffer);                  //Imprimimos en el LCD el buffer donde ahi esta almacenado como string la variable
            break;
    }
}
void lcdWriteFloatI2C(char ADRESS,float _Variable)//En esta funcion introducimos una variable sin asignar su tipo aun 
{                                        //por si se da el caso de ser una variable entera o flotante
    char buffer[20];                     //Buffer de 16 bits, en el se sobreescribiran las variables enteras o flotantes
    sprintf(buffer,"%.2f",_Variable);      //Se transforman esas variables enteras a un string
    lcdWriteStringI2C(ADRESS,buffer);                  //Imprimimos en el LCD el buffer donde ahi esta almacenado como string la variable
}
void lcdClearI2C(char ADRESS)//Se limpia la pantalla del LCD
{
    CMD(ADRESS, 0b00000000);
    CMD(ADRESS, 0b00010000);   
}
void cursorHomeI2C(char ADRESS)//Regresa el cursor a la posicion de inicio
{
    CMD(ADRESS, 0b00000000);
    CMD(ADRESS, 0b00100000);
}
void cursorLeftI2C(char ADRESS)//Se desplaza el cursor a la izquierda una unidad
{
    CMD(ADRESS, 0b00010000);
    CMD(ADRESS, 0b00000000);
}
void cursorRightI2C(char ADRESS)//Se desplaza el cursor a la derecha una unidad
{
    CMD(ADRESS, 0b00010000);
    CMD(ADRESS, 0b01000000);
}
void displayLeftI2C(char ADRESS)//Se desplaza el texto del LCD a la izquierda una unidad
{
    CMD(ADRESS, 0b00010000);
    CMD(ADRESS, 0b10000000);
}
void displayRightI2C(char ADRESS)//Se desplaza el texto del LCD a la derecha una unidad
{
    CMD(ADRESS, 0b00010000);
    CMD(ADRESS, 0b11000000);
}
void cursorLineHI2C(char ADRESS)//Se coloca el cursor en la linea de abajo
{
    CMD(ADRESS, 0b10000000);
    CMD(ADRESS, 0b00000000);
}
void cursorLineLI2C(char ADRESS)//Se coloca el cursor en la linea de arriba
{
    CMD(ADRESS, 0b11000000);
    CMD(ADRESS, 0b00000000);
}
void cursorXYI2C(char ADRESS, int x, int y)
{
    if(x<1||y<1)
    {
        cursorHomeI2C(ADRESS);
        lcdWriteStringI2C(ADRESS, "cursorXY(x,y);");
        cursorLineLI2C(ADRESS);
        lcdWriteStringI2C(ADRESS, "X min=1,Y min=1");
        __delay_ms(1000);
        cursorHomeI2C(ADRESS);
        lcdClearI2C(ADRESS);
        exit(1);
    }
    else if(x>16||y>2)
    {
        cursorHomeI2C(ADRESS);
        lcdWriteStringI2C(ADRESS, "cursorXY(x,y);");
        cursorLineLI2C(ADRESS);
        lcdWriteStringI2C(ADRESS, "X max=16,Y max=2");
        __delay_ms(1000);
        cursorHomeI2C(ADRESS);
        lcdClearI2C(ADRESS);
        exit(1);
    }
    if(y==2&&x<16)
    {
        cursorLineLI2C(ADRESS);
        for(int i=1;i<x;i++)
        {
            cursorRightI2C(ADRESS);
        }
    }else if(y==1&&x<16)
    {
        cursorHomeI2C(ADRESS);
        for(int i=1;i<x;i++)
        {
            cursorRightI2C(ADRESS);
        }
    }   
}
