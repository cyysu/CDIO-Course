#ifndef __BSP_IRQ_PRIORITY
#define __BSP_IRQ_PRIORITY

#include "stm32f10x.h"
#include "bsp_TiMbase.h" 

#define EnableInterrupts  	__set_PRIMASK(0);	
#define DisableInterrupts	__set_PRIMASK(1);	

extern void SetIrqAndPriority(void);
	
#endif
