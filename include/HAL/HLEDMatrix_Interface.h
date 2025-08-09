/*
 * LEDMatrix_Interface.h
 *
 *  Created on: Jul 29, 2025
 *      Author: Ziad
 */

#ifndef LEDMATRIX_INTERFACE_H_
#define LEDMATRIX_INTERFACE_H_


void LEDMatrix_Init();
void LEDMatrix_Display(u8* frame);

// Shape functions
void Display_Triangle();
void Display_Circle();
void Display_SadFace();
void Display_HappyFace();




#endif /* LEDMATRIX_INTERFACE_H_ */
