// Define to prevent recursive inclusion  --------------------------------------
#ifndef __UART_H
#define __UART_H

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Example_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup EXAMPLE_MOTOR
/// @brief MOTOR example modules
/// @{


////////////////////////////////////////////////////////////////////////////////
/// @defgroup MOTOR_Exported_Variables
/// @{
#ifdef _UART_C_
#define GLOBAL
#else
#define GLOBAL extern
#endif

GLOBAL u8 uartTxBuf[20];
GLOBAL u8 uartRxBuf[20];

#undef GLOBAL
/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup MOTOR_Exported_Functions
/// @{

void uartTick();
void initUART(UART_TypeDef* UARTx);


/// @}


/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
