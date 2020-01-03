/*! ----------------------------------------------------------------------------
 * @file    port_platform.h
 * @brief   HW specific definitions and functions for portability
 *
 * @attention
 *
 * Copyright 2015 (c) DecaWave Ltd, Dublin, Ireland.
 *
 * All rights reserved.
 *
 * @author DecaWave
 */


#ifndef PORT_PLATFORM_H_
#define PORT_PLATFORM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "deca_types.h" 
#include "deca_device_api.h"
#include "boards.h"

/*

Note: Antenna Delay Values	
The sum of the values is the TX to RX antenna delay, this should be experimentally determined by a calibration process. Here we use a hard coded
value (expected to be a little low so a positive error will be seen on the resultant distance estimate. For a real production application, each
device should have its own antenna delay properly calibrated to get good precision when performing range measurements.   

*/

/* Default antenna delay values for 64 MHz PRF.*/
#define TX_ANT_DLY 16456
#define RX_ANT_DLY 16456	

	
int readfromspi(uint16 headerLength, const uint8 *headerBuffer, uint32 readlength, uint8 *readBuffer);
int writetospi( uint16 headerLength, const uint8 *headerBuffer, uint32 bodylength, const uint8 *bodyBuffer);
decaIrqStatus_t decamutexon(void);
void decamutexoff(decaIrqStatus_t s);

#if defined(BOARD_DWM1001_DEV)
#define SPI_CS_PIN   17 /**< SPI CS Pin.*/
#else
#error "Example is not supported on that board."
#endif

#if 0

/* DW1000 IRQ (EXTI9_5_IRQ) handler type. */
typedef void (*port_deca_isr_t)(void);

/* DW1000 IRQ handler declaration. */
port_deca_isr_t port_deca_isr;

/*! ------------------------------------------------------------------------------------------------------------------
 * @fn port_set_deca_isr()
 *
 * @brief This function is used to install the handling function for DW1000 IRQ.
 *
 * NOTE:
 *   - As EXTI9_5_IRQHandler does not check that port_deca_isr is not null, the user application must ensure that a
 *     proper handler is set by calling this function before any DW1000 IRQ occurs!
 *   - This function makes sure the DW1000 IRQ line is deactivated while the handler is installed.
 *
 * @param deca_isr function pointer to DW1000 interrupt handler to install
 *
 * @return none
 */
void port_set_deca_isr(port_deca_isr_t deca_isr);

#endif

/*****************************************************************************************************************//*
**/


/****************************************************************************//**
 *
 *                              MACRO function
 *
 *******************************************************************************/
typedef bool (*locker_func_t)();
typedef bool (*unlocker_func_t)();


/****************************************************************************//**
 *
 *                              port function prototypes
 *
 *******************************************************************************/

void port_wakeup_dw1000(void);
void port_wakeup_dw1000_fast(void);

void port_set_dw1000_slowrate(void);
void port_set_dw1000_fastrate(void);

void process_dwRSTn_irq(void);
void process_deca_irq(void);

void port_set_mutexer(locker_func_t locker, unlocker_func_t unlocker);

void setup_DW1000RSTnIRQ(int enable);

void reset_DW1000(void);

#if 0
ITStatus EXTI_GetITEnStatus(uint32_t x);

uint32_t port_GetEXT_IRQStatus(void);
uint32_t port_CheckEXT_IRQ(void);
void port_DisableEXT_IRQ(void);
void port_EnableEXT_IRQ(void);
extern uint32_t     HAL_GetTick(void);

#endif

#ifdef __cplusplus
}
#endif

#endif /* PORT_PLATFORM_H_ */
