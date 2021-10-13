#define E_PIN LATDbits.LD3
#define RW_PIN LATDbits.LD2
#define RS_PIN LATDbits.LD1
#include <stdio.h>
#include <string.h>
void lcdComando(unsigned int comando)
{                   //(D7:RD7, D6:RD6, D5:RD5, D4:RD4) del LCD al PIC
    LATD = comando; //Escribimos en el puerto D el comando que se mandara al LCD
    RS_PIN = 0;     //Indicamos que se enviara un comando 
    E_PIN = 1;    
    __delay_ms(2);
    E_PIN = 0; 
}
void lcdBegin()
{
    for(int i=0;i<3;i++)       //
    {                          //Realizamos los 3 colsos con el
        lcdComando(0b00110000);//comando inicial necesario
    }                          //
    ////////////////////////////////////////////////////////////////////////////    
                           //A partir de este momento configuramos
    lcdComando(0b00100000);//que los datos los enviaremos de
                           //4 en 4 trabajaremos con 4 bits 
    ////////////////////////////////////////////////////////////////////////////
    lcdComando(0b00100000);//Configiramos que usaremos las 2 lineasdel LCD y que
    lcdComando(0b11000000);//trabajaremos con la fuente grande de las letras
    ////////////////////////////////////////////////////////////////////////////
    lcdComando(0b00000000);//Se apaga el LCD y se 
    lcdComando(0b10000000);//reinicia su configuracion
    ////////////////////////////////////////////////////////////////////////////
    lcdComando(0b00000000);//Se apaga el display y regresa
    lcdComando(0b00010000);//a la posicion de inicio
    ////////////////////////////////////////////////////////////////////////////
    lcdComando(0b00000000);//Con esto procedemos a encender el LCD y
    lcdComando(0b01100000);//tambien indicamos que visualizaremos
    lcdComando(0b00000000);//el cursor y este tendra un blink y que
    lcdComando(0b11110000); //este se desplazara a la derecha
}
void lcdWriteChar(char caracter)
{
    char caracterH, caracterL;
    caracterH = caracter&0b11110000;
    caracterL = caracter&0b00001111;
    caracterL = caracterL<<4;   
    ////////////////////////////////////////////////////////////////////////////
    LATD = caracterH; //Se envia la parte alta 
    RS_PIN = 1;       //El dato ingresado es tomado para escrivirse en el LCD
    E_PIN = 1;    
    __delay_ms(1);
    E_PIN = 0; 
     __delay_ms(1);
    ////////////////////////////////////////////////////////////////////////////
    LATD = caracterL; //Se envia la parte baja 
    RS_PIN = 1;       //El dato ingresado es tomado para escrivirse en el LCD
    E_PIN = 1;    
    __delay_ms(1);
    E_PIN = 0; 
    __delay_ms(1);
}
void lcdWriteString(char *string)
{
   int i;
   for(i=0;string[i]!='\0';i++)
      lcdWriteChar(string[i]);
}
void lcdWriteConst(unsigned long _Variable)//En esta funcion introducimos una variable sin asignar su tipo aun 
{
    char buffer[20];
    sprintf(buffer,"%i",_Variable);      //Se transforman esas variables enteras a un string
    lcdWriteString(buffer);                  //Imprimimos en el LCD el buffer donde ahi esta almacenado como string la variable
}
void lcdWriteVar(unsigned long _Variable, int digit)//En esta funcion introducimos una variable sin asignar su tipo aun 
{
    char buffer[20];
    switch(digit)
    {
        case 1:
            sprintf(buffer,"%1i",_Variable);      //Se transforman esas variables enteras a un string
            lcdWriteString(buffer);                  //Imprimimos en el LCD el buffer donde ahi esta almacenado como string la variable
            break;
        case 2:
            sprintf(buffer,"%02i",_Variable);      //Se transforman esas variables enteras a un string
            lcdWriteString(buffer);                  //Imprimimos en el LCD el buffer donde ahi esta almacenado como string la variable
            break;
        case 3:
            sprintf(buffer,"%03i",_Variable);      //Se transforman esas variables enteras a un string
            lcdWriteString(buffer);                  //Imprimimos en el LCD el buffer donde ahi esta almacenado como string la variable
            break;
        case 4:
            sprintf(buffer,"%04i",_Variable);      //Se transforman esas variables enteras a un string
            lcdWriteString(buffer);                  //Imprimimos en el LCD el buffer donde ahi esta almacenado como string la variable
            break;
        case 5:
            sprintf(buffer,"%05i",_Variable);      //Se transforman esas variables enteras a un string
            lcdWriteString(buffer);                  //Imprimimos en el LCD el buffer donde ahi esta almacenado como string la variable
            break;
    }
}
void lcdWriteFloat(float _Variable)//En esta funcion introducimos una variable sin asignar su tipo aun 
{
    char buffer[20];                     //Buffer de 16 bits, en el se sobreescribiran las variables enteras o flotantes
    sprintf(buffer,"%.2f",_Variable);      //Se transforman esas variables enteras a un string
    lcdWriteString(buffer);                  //Imprimimos en el LCD el buffer donde ahi esta almacenado como string la variable
}
void lcdClear()//Se limpia la pantalla del LCD
{
    lcdComando(0b00000000);
    lcdComando(0b00010000);   
}
void cursorHome()//Regresa el cursor a la posicion de inicio
{
    lcdComando(0b00000000);
    lcdComando(0b00100000);
}
void cursorLeft()//Se desplaza el cursor a la izquierda una unidad
{
    lcdComando(0b00010000);
    lcdComando(0b00000000);
}
void cursorRight()//Se desplaza el cursor a la derecha una unidad
{
    lcdComando(0b00010000);
    lcdComando(0b01000000);
}
void displayLeft()//Se desplaza el texto del LCD a la izquierda una unidad
{
    lcdComando(0b00010000);
    lcdComando(0b10000000);
}
void displayRight()//Se desplaza el texto del LCD a la derecha una unidad
{
    lcdComando(0b00010000);
    lcdComando(0b11000000);
}
void cursorLineH()//Se coloca el cursor en la linea de abajo
{
    lcdComando(0b10000000);
    lcdComando(0b00000000);
}
void cursorLineL()//Se coloca el cursor en la linea de arriba
{
    lcdComando(0b11000000);
    lcdComando(0b00000000);
}
void cursorXY(int x,int y)
{
    if(x<1||y<1)
    {
        cursorHome();
        lcdWriteString("cursorXY(x,y);");
        cursorLineL();
        lcdWriteString("X min=1,Y min=1");
        __delay_ms(1000);
        cursorHome();
        lcdClear();
        exit(1);
    }
    else if(x>16||y>2)
    {
        cursorHome();
        lcdWriteString("cursorXY(x,y);");
        cursorLineL();
        lcdWriteString("X max=16,Y max=2");
        __delay_ms(1000);
        cursorHome();
        lcdClear();
        exit(1);
    }
    if(y==2&&x<16)
    {
        cursorLineL();
        for(int i=1;i<x;i++)
        {
            cursorRight();
        }
    }else if(y==1&&x<16)
    {
        cursorHome();
        for(int i=1;i<x;i++)
        {
            cursorRight();
        }
    }   
}
void lineClear(int y)
{
    cursorXY(1,y);
    lcdWriteString("                ");
}
