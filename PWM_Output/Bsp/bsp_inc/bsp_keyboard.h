#ifndef __BSP_KEYBOARD_H
#define __BSP_KEYBOARD_H

#include "stm32f10x.h"

//#define KEYPORT GPIOE->IDR
//extern void MatrixKey_Clock_Enable(void);
//extern uint8_t scan_MatrixKey(void);

extern uint8_t MatrixKey_value;
extern void MatrixKeyboard_Init(void);
extern void MatrixKeyDealPro(void);
extern char RETURN;

#endif
