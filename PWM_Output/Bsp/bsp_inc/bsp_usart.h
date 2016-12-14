#ifndef __BSP_USART_H
#define	__BSP_USART_H

#include "stm32f10x.h"
#include <stdio.h>
	
extern void USART1_Config(uint32_t _baud);
extern void Usart_SendString( USART_TypeDef * pUSARTx, char *str);

#endif /* __BSP_USART_H */
