#ifndef _WIRELESS_CC2500_H
#define _WIRELESS_CC2500_H
/*!
 @file wireless_cc2500.h
 @author Nicholas Destounis
 @author Nikolaos Bukas
 @author Michael Smith
 @author Kevin Dam
 @brief Header for TI CC2500 configuration
 */
 
/*! @addtogroup Microp Project Group 1
 *  @{
 */

#include "stdint.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_spi.h"

// Wireless RF configuration - from TA
#ifndef SMARTRF_CC2500_H
#define SMARTRF_CC2500_H
#define SMARTRF_RADIO_CC2500
#define SMARTRF_SETTING_FSCTRL1 0x0C//0x12 //Frequency offset = 457kHz
#define SMARTRF_SETTING_FSCTRL0 0x00
#define SMARTRF_SETTING_FREQ2 0x5D // Carrier Frequency is 2.433GHz
#define SMARTRF_SETTING_FREQ1 0x93
#define SMARTRF_SETTING_FREQ0 0xB1
// Page 65 of datasheet - FREQ 0,1,2 registers
// We set f_carrier, f_XOSC = 26Mhz
// TODO : Fill in the registers

#define SMARTRF_SETTING_MDMCFG4 0x0E //0x2D // BW of channel = 541.666kHz
#define SMARTRF_SETTING_MDMCFG3 0x3B // Baud Rate = 125kb
#define SMARTRF_SETTING_MDMCFG2 0x73 //before demodulator, MSK modulation, 16/16 sync word bits detected
#define SMARTRF_SETTING_MDMCFG1 0x42 //
#define SMARTRF_SETTING_MDMCFG0 0xF8 // Default Channel Spacing of 200kHz
#define SMARTRF_SETTING_CHANNR 0x00 // Channel 0
#define SMARTRF_SETTING_DEVIATN 0x00 //0x01 // 1785kHz
#define SMARTRF_SETTING_FREND1 0xB6
#define SMARTRF_SETTING_FREND0 0x10
#define SMARTRF_SETTING_MCSM0 0x18 // Automatically calibrate When going from IDLE to RX or TX (or FSTXON) check CC2500 datasheet
#define SMARTRF_SETTING_FOCCFG 0x1D // check datasheet
#define SMARTRF_SETTING_BSCFG 0x1C
#define SMARTRF_SETTING_AGCCTRL2 0xC7
#define SMARTRF_SETTING_AGCCTRL1 0x40 //0x00
#define SMARTRF_SETTING_AGCCTRL0 0xB0
#define SMARTRF_SETTING_FSCAL3 0xEA
#define SMARTRF_SETTING_FSCAL2 0x0A
#define SMARTRF_SETTING_FSCAL1 0x00
#define SMARTRF_SETTING_FSCAL0 0x19 //0x11
#define SMARTRF_SETTING_FSTEST 0x59
#define SMARTRF_SETTING_TEST2 0x88
#define SMARTRF_SETTING_TEST1 0x31
#define SMARTRF_SETTING_TEST0 0x0B
#define SMARTRF_SETTING_FIFOTHR 0x07
#define SMARTRF_SETTING_IOCFG2 0x29
#define SMARTRF_SETTING_IOCFG0D 0x06
#define SMARTRF_SETTING_PKTCTRL1 0x04
#define SMARTRF_SETTING_PKTCTRL0 0x05 //0x05 // Fixed Packet Length (0x05)
#define SMARTRF_SETTING_ADDR 0x00 // Global Broadcast Address
#define SMARTRF_SETTING_PKTLEN 0x0A // Packet Length of 10bytes (0xFF)
#endif
//! @} 

typedef struct {
	int test;
}WirelessInitStruct;

void CC2500_Init(WirelessInitStruct* initStruct);

// Wireless data send/receive
void CC2500_SendData(void* data, uint8_t address, int size);
void CC2500_ReceiveData(void* data, uint8_t address, int size);

// SPI Interface Pins
#define CC2500_CONFG_REGS_ADDR_MIN			0x00
#define CC2500_CONFG_REGS_ADDR_MAX			0x2E
#define CC2500_STATUS_REGS_ADDR_MIN			0x30
#define CC2500_STATUS_REGS_ADDR_MAX			0x3F

#define FIFO_WRITE_ADDRESS					 		 0x3F
#define FIFO_READ_ADDRESS								 0xBF
#define FIFO_WRITE_BURST_ADDRESS				 0x7F
#define FIFO_READ_BURST_ADDRESS					 0xFF

#define ERROR												0x00
#define SUCCESS											0x01

#define EXCEPTION_ERROR									 0x00
#define OVERFLOW_ERROR									 0x02
#define NO_ERROR												 0x01

#define CHIP_RDY_MASK										0x80
#define STATE_MASK											0x38
#define FIFO_BYTES_MASK									0xF0

#define CHIP_RDY_ERROR									0x01

#define IDLE_STATE											0x00
#define RX_STATE												0x01
#define TX_STATE												0x02
#define FSTXON_STATE										0x03
#define CALIBRATE_STATE									0x04
#define SETTLING_STATE									0x05
#define RXFIFO_OVERFLOW_STATE						0x06
#define TXFIFO_UNDERFLOW_STATE					0x07

#define CC2500_SPI                       SPI2
#define CC2500_SPI_CLK                   RCC_APB1Periph_SPI2

#define CC2500_SPI_SCK_PIN               GPIO_Pin_13                 
#define CC2500_SPI_SCK_GPIO_PORT         GPIOB                       
#define CC2500_SPI_SCK_GPIO_CLK          RCC_AHB1Periph_GPIOB
#define CC2500_SPI_SCK_SOURCE            GPIO_PinSource13
#define CC2500_SPI_SCK_AF                GPIO_AF_SPI2

#define CC2500_SPI_MISO_PIN              GPIO_Pin_14                 
#define CC2500_SPI_MISO_GPIO_PORT        GPIOB                       
#define CC2500_SPI_MISO_GPIO_CLK         RCC_AHB1Periph_GPIOB
#define CC2500_SPI_MISO_SOURCE           GPIO_PinSource14
#define CC2500_SPI_MISO_AF               GPIO_AF_SPI2

#define CC2500_SPI_MOSI_PIN              GPIO_Pin_15                 
#define CC2500_SPI_MOSI_GPIO_PORT        GPIOB                       
#define CC2500_SPI_MOSI_GPIO_CLK         RCC_AHB1Periph_GPIOB
#define CC2500_SPI_MOSI_SOURCE           GPIO_PinSource15
#define CC2500_SPI_MOSI_AF               GPIO_AF_SPI2

#define CC2500_SPI_NSS_PIN							 GPIO_Pin_12
#define CC2500_SPI_NSS_GPIO_PORT				 GPIOB
#define CC2500_SPI_NSS_GPIO_CLK					 RCC_AHB1Periph_GPIOE
#define CC2500_SPI_NSS_SOURCE            GPIO_PinSource12
#define CC2500_SPI_NSS_AF                GPIO_AF_SPI2

#define CC2500_SPI_INT_PIN              GPIO_Pin_0                  
#define CC2500_SPI_INT_GPIO_PORT        GPIOE                       
#define CC2500_SPI_INT_GPIO_CLK         RCC_AHB1Periph_GPIOE
#define CC2500_SPI_INT_EXTI_LINE        EXTI_Line0
#define CC2500_SPI_INT_EXTI_PORT_SOURCE EXTI_PortSourceGPIOE
#define CC2500_SPI_INT_EXTI_PIN_SOURCE  EXTI_PinSource0
#define CC2500_SPI_INT_EXTI_IRQn        EXTI0_IRQn 

#define CC2500_NSS_LOW()       GPIO_ResetBits(CC2500_SPI_NSS_GPIO_PORT, CC2500_SPI_NSS_PIN)
#define CC2500_NSS_HIGH()      GPIO_SetBits(CC2500_SPI_NSS_GPIO_PORT, CC2500_SPI_NSS_PIN)

#endif
