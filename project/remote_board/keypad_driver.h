#ifndef _KEYPAD_DRIVER_H_
#define _KEYPAD_DRIVER_H_

#include "stm32f4xx_conf.h"
#include "LCD_driver.h"


/* Keypad pin mapping (GPIO Pins <-> Keypad pins)
 *  Rows (1, 4, 7, *)
 *   PD2  = Pin 5
 *   PD3  = Pin 6
 *   PD6  = Pin 7
 *   PD7  = Pin 8
 *  Columns (1, 2, 3, A)
 *   PD8  = Pin 1
 *   PD9  = Pin 2
 *   PD10 = Pin 3
 *   PD11 = Pin 4
 */
void Keypad_configure(void);
uint16_t Keypad_Handle_Interrupt(void);
char Keypad_Get_Character(uint32_t EXTI_Line_Source, uint16_t rows);

void enable_interrupt(uint32_t EXTI_Line);
void disable_interrupt(uint32_t EXTI_Line);
 
#define KEYPAD_GPIO_BANK GPIOD
// Columns
#define KEYPAD_PIN_1 GPIO_Pin_8
#define KEYPAD_PIN_2 GPIO_Pin_6
#define KEYPAD_PIN_3 GPIO_Pin_10
#define KEYPAD_PIN_4 GPIO_Pin_11
// Rows
#define KEYPAD_PIN_5 GPIO_Pin_2
#define KEYPAD_PIN_6 GPIO_Pin_3
#define KEYPAD_PIN_7 GPIO_Pin_6
#define KEYPAD_PIN_8 GPIO_Pin_7

#define KEYPAD_COL KEYPAD_PIN_1 | KEYPAD_PIN_2 | KEYPAD_PIN_3 | KEYPAD_PIN_4
#define KEYPAD_ROW KEYPAD_PIN_5 | KEYPAD_PIN_6 | KEYPAD_PIN_7 | KEYPAD_PIN_8

#define KEPAD_INT_SRC_5 EXTI_PinSource2
#define KEPAD_INT_SRC_6	EXTI_PinSource3
#define KEPAD_INT_SRC_7	EXTI_PinSource6
#define KEPAD_INT_SRC_8 EXTI_PinSource7

#define KEYPAD_INT_SRC KEPAD_INT_SRC_5 | KEPAD_INT_SRC_6 | KEPAD_INT_SRC_7 | KEPAD_INT_SRC_8

#define KEYPAD_INT_LINE_5 EXTI_Line2
#define KEYPAD_INT_LINE_6 EXTI_Line3
#define KEYPAD_INT_LINE_7 EXTI_Line6
#define KEYPAD_INT_LINE_8 EXTI_Line7

#define KEYPAD_INT_LINE KEYPAD_INT_LINE_5 | KEYPAD_INT_LINE_6 | KEYPAD_INT_LINE_7 | KEYPAD_INT_LINE_8

#define KEYPAD_EXTI_IRQ_5 EXTI2_IRQn
#define KEYPAD_EXTI_IRQ_6 EXTI3_IRQn
#define KEYPAD_EXTI_IRQ_7 EXTI9_5_IRQn
#define KEYPAD_EXTI_IRQ_8 EXTI9_5_IRQn

#define KEYPAD_EXTI_IRQ KEYPAD_EXTI_IRQ_5 | KEYPAD_EXTI_IRQ_6 | KEYPAD_EXTI_IRQ_7 | KEYPAD_EXTI_IRQ_8

#endif
