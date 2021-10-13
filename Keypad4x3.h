#include <xc.h>
void keypadBegin()
{
#define FILA_3  TRISAbits.RA1   //Definimos que bit del PIC sera la fila 3 sin especificar si es I/O
#define FILA_2  TRISAbits.RA2   //Definimos que bit del PIC sera la fila 2 sin especificar si es I/O
#define FILA_1  TRISAbits.RA3   //Definimos que bit del PIC sera la fila 1 sin especificar si es I/O
    FILA_3 = 0;                 //Configuramos como salida a la fila 3
    FILA_2 = 0;                 //Configuramos como salida a la fila 2
    FILA_1 = 0;                 //Configuramos como salida a la fila 1
#define FILA3   LATAbits.LA1    //Fila 3 como escritura H/L
#define FILA2   LATAbits.LA2    //Fila 2 como escritura H/L
#define FILA1   LATAbits.LA3    //Fila 1 como escritura H/L
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define COLUMNA_4 TRISAbits.RA4 //Definimos que bit del PIC sera la Columna 4 sin especificar si es I/O
#define COLUMNA_3 TRISAbits.RA5 //Definimos que bit del PIC sera la Columna 3 sin especificar si es I/O
#define COLUMNA_2 TRISEbits.RE0 //Definimos que bit del PIC sera la Columna 2 sin especificar si es I/O
#define COLUMNA_1 TRISEbits.RE1 //Definimos que bit del PIC sera la Columna 1 sin especificar si es I/O
    COLUMNA_4 = 1;              //Configuramos como entrada a la columna 4
    COLUMNA_3 = 1;              //Configuramos como entrada a la columna 3
    COLUMNA_2 = 1;              //Configuramos como entrada a la columna 2
    COLUMNA_1 = 1;              //Configuramos como entrada a la columna 1
#define COLUMNA4 PORTAbits.RA4  //Entrada PullDown, detectara un pulso positivo
#define COLUMNA3 PORTAbits.RA5  //Entrada PullDown, detectara un pulso positivo
#define COLUMNA2 PORTEbits.RE0  //Entrada PullDown, detectara un pulso positivo
#define COLUMNA1 PORTEbits.RE1  //Entrada PullDown, detectara un pulso positivo
}
int keyTec()//Se retorna una cantidad repetitiva del numero asignado a cada tecla
{
    int key = 12;               //Condicion de no continuar retornando valores  
    FILA3 = 1;
    if(COLUMNA4 == 1) key = 1;
    if(COLUMNA3 == 1) key = 4;
    if(COLUMNA2 == 1) key = 7;
    if(COLUMNA1 == 1) key = 10;
    FILA3 = 0;
    
    FILA2 = 1;
    if(COLUMNA4 == 1) key = 2;
    if(COLUMNA3 == 1) key = 5;
    if(COLUMNA2 == 1) key = 8;
    if(COLUMNA1 == 1) key = 11;
    FILA2 = 0;
    
    FILA1 = 1;
    if(COLUMNA4 == 1) key = 3;
    if(COLUMNA3 == 1) key = 6;
    if(COLUMNA2 == 1) key = 9;
    if(COLUMNA1 == 1) key = 0;
    FILA1 = 0;
    return key;
}
int keyClic()//Se retorna solo un numero asignado segun la tecla precionada cuando se deja de precionar esta(Antirebote)
{
    int key = 12;               //Condicion de no continuar retornando valores
    FILA3 = 1;
    if(COLUMNA4 == 1) key = 1;
    if(COLUMNA3 == 1) key = 4;
    if(COLUMNA2 == 1) key = 7;
    if(COLUMNA1 == 1) key = 10;
    while(COLUMNA4 == 1 || COLUMNA3 == 1 || COLUMNA2 == 1 || COLUMNA1 == 1);
    FILA3 = 0;
    
    FILA2 = 1;
    if(COLUMNA4 == 1) key = 2;
    if(COLUMNA3 == 1) key = 5;
    if(COLUMNA2 == 1) key = 8;
    if(COLUMNA1 == 1) key = 11;
    while(COLUMNA4 == 1 || COLUMNA3 == 1 || COLUMNA2 == 1 || COLUMNA1 == 1);
    FILA2 = 0;
    
    FILA1 = 1;
    if(COLUMNA4 == 1) key = 3;
    if(COLUMNA3 == 1) key = 6;
    if(COLUMNA2 == 1) key = 9;
    if(COLUMNA1 == 1) key = 0;
    while(COLUMNA4 == 1 || COLUMNA3 == 1 || COLUMNA2 == 1 || COLUMNA1 == 1);
    FILA1 = 0;
    return key;
}
char keyClicChar()//decodifica el valor numerico de la tecla precionada con "keyClic();"a caracteres definidos por el usuario
{
    int c = keyClic();
    switch(c)
    {
        case 12://retorno para tomarlo como condicion de no continuar imprimiendo caracteres
            return '\0';
            break;
        case 1:
            return 'a';
            break;
        case 2:
            return 'b';
            break;
        case 3:
            return 'c';
            break;
        case 4:
            return 'd';
            break;
        case 5:
            return 'e';
            break;
        case 6:
            return 'f';
            break;
        case 7:
            return 'g';
            break;
        case 8:
            return 'h';
            break;
        case 9:
            return 'i';
            break;
        case 10:
            return 'j';
            break;
        case 11:
            return 'k';
            break;
        case 0:
            return 'l';
            break;
    }
}
char keyTecChar()//decodifica el valor numerico de la tecla precionada con "keyTec();"a caracteres definidos por el usuario
{
    int c = keyTec();
    switch(c)
    {
        case 12://retorno para tomarlo como condicion de no continuar imprimiendo caracteres
            return '\0';
            break;
        case 1:
            return 'a';
            break;
        case 2:
            return 'b';
            break;
        case 3:
            return 'c';
            break;
        case 4:
            return 'd';
            break;
        case 5:
            return 'e';
            break;
        case 6:
            return 'f';
            break;
        case 7:
            return 'g';
            break;
        case 8:
            return 'h';
            break;
        case 9:
            return 'i';
            break;
        case 10:
            return 'j';
            break;
        case 11:
            return 'k';
            break;
        case 0:
            return 'l';
            break;
    }
}