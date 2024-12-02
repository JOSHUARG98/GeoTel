/*
 * SSD1306.h
 *
 *  Created on: Jul 29, 2024
 *      Author: joshu
 */

#ifndef SSD1306_H_
#define SSD1306_H_
#include "I2Cx.h"


#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_SETCONTRAST 0x81         ///< See datasheet
#define SSD1306_CHARGEPUMP 0x8D          ///< See datasheet
#define SSD1306_SEGREMAP 0xA0            ///< See datasheet
#define SSD1306_DISPLAYALLON_RESUME 0xA4 ///< See datasheet
#define SSD1306_NORMALDISPLAY 0xA6       ///< See datasheet
#define SSD1306_SETMULTIPLEX 0xA8        ///< See datasheet
#define SSD1306_DISPLAYOFF 0xAE          ///< See datasheet
#define SSD1306_DISPLAYON 0xAF           ///< See datasheet
#define SSD1306_COMSCANINC 0xC0          ///< Not currently used
#define SSD1306_COMSCANDEC 0xC8          ///< See datasheet
#define SSD1306_SETDISPLAYOFFSET 0xD3    ///< See datasheet
#define SSD1306_SETDISPLAYCLOCKDIV 0xD5  ///< See datasheet
#define SSD1306_SETCOMPINS 0xDA          ///< See datasheet
#define SSD1306_SETSTARTLINE 0x40  ///< See datasheet
#define SSD1306_SETPAGE0 0XB0
#define SSD1306_SETPAGE1 0XB1
#define SSD1306_SETPAGE2 0XB2
#define SSD1306_SETPAGE3 0XB3
#define SSD1306_SETPAGE4 0XB4
#define SSD1306_SETPAGE5 0XB5
#define SSD1306_SETPAGE6 0XB6
#define SSD1306_SETPAGE7 0XB7



#define SSD1306_SCROLLINGL_ 0X27
#define SSD1306_SCROLLINGR_ 0X26
#define SSD1306_SET_COLUMN_ADDRESS_ 0X21


//SSD1306

#define AdreSSD1306 0X3C

#define ControlbC  0x00
#define ControlbD  0x40

int i;

/*********************************************
        DECLARACION DE FUNCIONES
**********************************************/
void SSD1306_Init(void);
void SSD1306_WriteString(char *cadena);
void SSD1306_WriteChar(char C);
void SSD1306_Clear(void);
void SSD1306_PosCom(uint8_t Pos);


/*********************************************
        DECLARACION DE FUNCIONES PARA LAS LETRAS
**********************************************/
void Letra_A(void);
void Letra_B(void);
void Letra_C(void);
void Letra_D(void);
void Letra_E(void);
void Letra_F(void);
void Letra_G(void);
void Letra_H(void);
void Letra_I(void);
void Letra_J(void);
void Letra_K(void);
void Letra_L(void);
void Letra_M(void);
void Letra_N(void);
void Letra_O(void);
void Letra_P(void);
void Letra_Q(void);
void Letra_R(void);
void Letra_S(void);
void Letra_T(void);
void Letra_U(void);
void Letra_V(void);
void Letra_W(void);
void Letra_X(void);
void Letra_Y(void);
void Letra_Z(void);
void Espacio (void);
void Admiracion(void);
void Numero_1(void);
void Numero_2(void);
void Numero_3(void);
void Numero_4(void);
void Numero_5(void);
void Numero_6(void);
void Numero_7(void);
void Numero_8(void);
void Numero_9(void);
void Numero_0(void);
void DosPuntos(void);
void Flecha_Abajo(void);
void Vacear(void);
void Flecha_Arriba(void);
void Flecha_Izquierda (void);
void Flecha_Derecha(void);
void Simbolo_Grados(void);







	//Procesamiento para









void SSD1306_Init(void){

	// Apaga la pantalla
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, 0xAE);  // Display OFF

	// Configura la frecuencia del reloj
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, 0xD5);  // Set display clock divide ratio/oscillator frequency
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, 0x80);  // Recommended oscillator frequency

	// Configura la multiplexación (64 multiplex para 128x64)
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, 0xA8);  // Set multiplex ratio
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, 0x3F);  // Multiplex ratio is 64 (for 128x64 display)

	// Configura el offset de la pantalla
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, 0xD3);  // Set display offset
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, 0x00);  // No offset

	// Línea de inicio de la pantalla en 0
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, 0x40);  // Set display start line at 0

	// Habilita el regulador de la bomba de carga (Charge Pump)
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, 0x8D);  // Enable charge pump regulator
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, 0x14);  // Enable charge pump

	// Establece el modo de direccionamiento de memoria
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, 0x20);  // Set memory addressing mode
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, 0x00);  // Horizontal addressing mode

	// Reconfigura el mapa de segmentos (columna 127 mapeada a SEG0)
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, 0xA1);  // Set segment re-map (A0/A1)

	// Configura la dirección de escaneo de salida COM
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, 0xC8);  // Set COM output scan direction (C0/C8)

	// Configura los pines COM
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, 0xDA);  // Set COM pins hardware configuration
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, 0x12);  // Alternative COM pin config

	// Establece el nivel de contraste de la pantalla
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, 0x81);  // Set contrast control
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, 0x7F);  // Contrast level (0x7F is typical)

	// Deshabilita la inversa de la pantalla
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, 0xA4);  // Disable entire display ON (resume to RAM content)

	// Establece el modo de visualización normal (sin inversión)
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, 0xA6);  // Set normal display mode (A6 = normal, A7 = inverted)

	// Configura el rango de desplazamiento (horizontal)
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, 0xD9);  // Set pre-charge period
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, 0xF1);  // Pre-charge period (recommended value)

	// Configura el voltaje de desactivación del driver
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, 0xDB);  // Set VCOMH deselect level
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, 0x40);  // VCOMH deselect level (0x40 recommended)

	// Enciende la pantalla
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, 0xAF);  // Display ON
}



void SSD1306_WriteString(char *cadena){
    unsigned int i = 0;
    while (cadena[i] != 0) {
        SSD1306_WriteChar(cadena[i]); // Escribir cada carácter
        i++;
    }
}



void SSD1306_WriteChar(char C){

    switch (C){
    case 'A':
Letra_A();
    break;
    case 'B':
Letra_B();
    break;
    case 'C':
Letra_C();
    break;
    case 'D':
Letra_D();
    break;
    case 'E':
Letra_E();
    break;
    case 'F':
Letra_F();
    break;
    case 'G':
Letra_G();
    break;
    case 'H':
Letra_H();
    break;
    case 'I':
Letra_I();
    break;
    case 'J':
Letra_J();
    break;
    case 'K':
Letra_K();
    break;
    case 'L':
Letra_L();
    break;
    case 'M':
Letra_M();
    break;
    case 'N':
Letra_N();
    break;
    case 'O':
Letra_O();
    break;
    case 'P':
Letra_P();
    break;
    case 'Q':
Letra_Q();
    break;
    case 'R':
Letra_R();
    break;
    case 'S':
Letra_S();
    break;
    case 'T':
Letra_T();
    break;
    case 'U':
Letra_U();
    break;
    case 'V':
Letra_U();
    break;
     case 'W':
Letra_W();
    break;
    case 'X':
Letra_X();
    break;
    case 'Y':
Letra_Y();
    break;
        case 'Z':
Letra_Z();
    break;
        case ' ':
Espacio();
    break;
        case '!':
Admiracion();
    break;
        case '1':
Numero_1();
    break;
        case '2':
Numero_2();
    break;
        case '3':
Numero_3();
    break;
        case '4':
Numero_4();
    break;
        case '5':
Numero_5();
    break;
        case '6':
Numero_6();
    break;
        case '7':
Numero_7();
    break;
        case '8':
Numero_8();
    break;
        case '9':
Numero_9();
    break;
        case '0':
Numero_0();
    break;
        case ':':
DosPuntos();
    break;
        case '*':
Simbolo_Grados();
	break;
    }
}




//LETRAS
void Letra_A(void){
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x33);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x33);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
}
void Letra_B(void){

    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x99);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x99);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
}
void Letra_C(void){
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xC3);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xC3);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xC3);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xC3);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);

}
void Letra_D(void){
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xC3);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xC3);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
}

void Letra_E(void){

    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xDB);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xDB);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xDB);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xDB);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);

}
void Letra_F(void){

    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x33);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x33);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x03);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x03);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);

}
void Letra_G(void){
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xDB);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xDB);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xF8);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xF8);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
}
void Letra_H(void){
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x18);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x18);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
}
void Letra_I(void){
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xC3);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xC3);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xC3);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xC3);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);

}
void Letra_J(void){
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xC3);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xC3);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x03);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x03);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
}
void Letra_K(void){
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x18);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x3C);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x66);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xC3);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
}

void Letra_L(void){
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xC0);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xC0);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xC0);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);

}
void Letra_M(void){

    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x0C);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x1C);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x0C);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);

}
void Letra_N(void){

    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x1C);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x38);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);

}
void Letra_O(void){


    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xC3);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xC3);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
}
void Letra_P(void){
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x1B);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x1B);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x1F);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x1F);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);

}
void Letra_Q(void){
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x7F);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x7F);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x63);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0X63);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);

}
void Letra_R(void){

    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x1B);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x7B);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x6F);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xEF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);

}
void Letra_S(void){
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xCF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xCF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xDB);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xDB);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xF3);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xF3);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);

}
void Letra_T(void){
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x03);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x03);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x03);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x03);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
}
void Letra_U(void){
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xC0);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xC0);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);

}


void Letra_V(void){
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x1F);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x7F);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xF0);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xF0);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x7F);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x1F);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);

}
void Letra_W(void){

    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x70);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x38);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x70);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);

}
void Letra_X(void){
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xC3);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xE7);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x3C);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x3C);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xE7);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xC3);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
}
void Letra_Y(void){
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x03);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x0F);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFC);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFC);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x0F);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x03);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);

}

void Letra_Z(void){
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xC3);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xE3);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFB);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xD7);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xC7);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xC3);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
}

void Espacio (void){
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
}

void Admiracion(void){
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFB);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFB);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFB);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
}


/*Declaracion de numeros decimales pantalla oled*/

void Numero_1(void){
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x01);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x01);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
}


void Numero_2(void){
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFB);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFB);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xDB);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xDB);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xDF);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xDF);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
}

void Numero_3(void){
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xDB);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xDB);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xDB);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xDB);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
}

void Numero_4(void){
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x1F);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x1F);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x18);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x18);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
}

void Numero_5(void){
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xDF);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xDF);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xDB);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xDB);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFB);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFB);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
}
void Numero_6(void){
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xDB);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xDB);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFB);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFB);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0X00);
}


void Numero_7(void){
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xC3);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xE3);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x3B);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x1F);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x0F);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x07);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
}

void Numero_8(void){
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xDB);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xDB);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0X00);
}

void Numero_9(void){
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xDF);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xDF);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xDB);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xDB);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
}
void Numero_0(void){
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xC3);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xC3);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
}

void DosPuntos(void){
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xC3);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xC3);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
}

void Simbolo_Grados(void) {
    // Ajustamos los valores para subir el símbolo de grados
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x30); // Parte superior del círculo, subido
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x48); // Lados del círculo, subido
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x30); // Parte inferior del círculo, subido
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00); // Separación
}


void Flecha_Abajo(void){
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x01);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x03);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x07);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x0F);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x1F);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x3F);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x7F);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x7F);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x3F);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x1F);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x0F);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x07);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x03);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x01);
}


void Flecha_Arriba(void){
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x80);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xC0);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xE0);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xF0);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xF8);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFC);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFE);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFE);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFC);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xF8);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xF0);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xE0);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xC0);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x80);
}

void Flecha_Izquierda(void){
	SSD1306_PosCom(0);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x80);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xC0);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, SSD1306_SETPAGE2);
	SSD1306_PosCom(1);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x01);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x03);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, SSD1306_SETPAGE1);
	SSD1306_PosCom(2);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xE0);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xF0);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xF8);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, SSD1306_SETPAGE2);
	SSD1306_PosCom(3);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x07);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x0F);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x1F);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, SSD1306_SETPAGE1);
	SSD1306_PosCom(5);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFC);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFE);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, SSD1306_SETPAGE2);
	SSD1306_PosCom(6);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x3F);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x7F);
}

void Flecha_Derecha(void){
		I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, SSD1306_SETPAGE1);
		SSD1306_PosCom(90);
		I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFF);
		I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFE);
		I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, SSD1306_SETPAGE2);
		SSD1306_PosCom(90);
		I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x7F);
		I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x3F);
		I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, SSD1306_SETPAGE1);
		SSD1306_PosCom(92);
		I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xFC);
		I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xF8);
		I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xF0);
		I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, SSD1306_SETPAGE2);
		SSD1306_PosCom(92);
		I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x1F);
		I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x0F);
		I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x07);
		I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, SSD1306_SETPAGE1);
		SSD1306_PosCom(95);
		I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xE0);
		I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0xC0);
		I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x80);
		I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, SSD1306_SETPAGE2);
		SSD1306_PosCom(95);
		I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x03);
		I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x01);
		I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, SSD1306_SETPAGE1);
}


void Vacear(void){
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
}




void SSD1306_Clear(void){
    int c;
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, SSD1306_SETPAGE0);
    SSD1306_PosCom(0);
for(c=0;c<128;c++){
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
}
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, SSD1306_SETPAGE1);
SSD1306_PosCom(0);
for(c=0;c<128;c++){
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
}
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, SSD1306_SETPAGE2);
SSD1306_PosCom(0);
for(c=0;c<128;c++){
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
}
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, SSD1306_SETPAGE3);
SSD1306_PosCom(0);
for(c=0;c<128;c++){
	I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
}
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, SSD1306_SETPAGE4);
SSD1306_PosCom(0);
for(c=0;c<128;c++){
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
}
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, SSD1306_SETPAGE5);
SSD1306_PosCom(0);
for(c=0;c<128;c++){
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
}
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, SSD1306_SETPAGE6);
SSD1306_PosCom(0);
for(c=0;c<128;c++){
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
}
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, SSD1306_SETPAGE7);
SSD1306_PosCom(0);
for(c=0;c<128;c++){
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbD, 0x00);
}
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, SSD1306_SETPAGE0);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, 0x00);
I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, 0x00);
}


void SSD1306_PosCom(uint8_t Pos){

    uint8_t high = (Pos & 0xF0) >> 4; // Parte alta del número
    uint8_t low = Pos & 0x0F;         // Parte baja del número

    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, 0x10 | high); // Enviar parte alta
    I2C_Tx_2Bytes(I2C3, AdreSSD1306, ControlbC, 0x00 | low);  // Enviar parte baja

}





#endif /* SSD1306_H_ */
