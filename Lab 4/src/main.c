//#include "arm_math.h"

// System includes
#include <stdio.h>
#include "cmsis_os.h"
#include "stm32f4xx.h"

// Project includes
#include "accelerometer.h"
#include "adc_init.h"
#include "alarm.h"
#include "interrupts_config.h"
#include "motor.h"
#include "temp_processing.h"
#include "LCD_Driver.h"

#define TEMP_INT_SIGNAL 0x01
#define ALARM_INT_SIGNAL 0x02
#define ACC_INT_SIGNAL 0x04

/**
 * Thread to perform menial tasks such as switching LEDs.
 * @param arg unused
 */
void temperature_thread(const void* arg);
void accelerometer_thread(const void* arg);
void signalAlarm(void);

FilterStruct tempFilterBuffer;

/* Thread structure for above threads */
osThreadDef(temperature_thread, osPriorityNormal, 1, 0);
osThreadDef(accelerometer_thread, osPriorityNormal, 1, 0);

osThreadId tid_temperature, tid_accelerometer;
/**
 * Program entry point.
 */
int main() {

  ADC_configure();
  calibrateTempSensor();
  initFilterBuffer(&tempFilterBuffer); 
  
  Alarm_configure();
	Motor_PWM_configure();
	Accelerometer_configure();
  
  LCD_configure();
  printLCDString("Temperature:    C", 17, 1);
  
  tid_temperature = osThreadCreate(osThread(temperature_thread), NULL);
	tid_accelerometer = osThreadCreate(osThread(accelerometer_thread), NULL);
	
  // Configure interrupts last so as to avoid a deadlock situation with
  // the signaling for the temperature
	Interrupts_configure();
  
}


void temperature_thread(const void* arg) {
    while(1) {
        
        osSignalWait(TEMP_INT_SIGNAL, osWaitForever);
        
        // TODO put mutex
        float temperature = getAndAverageTemp(&tempFilterBuffer);
        
        char tempAsString[4];
        sprintf(tempAsString, "%.1f", temperature);
      

        alarmCheckTemp(temperature);
        printLCDToPos(tempAsString, 4, 1, 13);
        
    }
}


void accelerometer_thread(const void* arg) {
	while(1) {
    // Wait forever for accelerometer interrupt
    osSignalWait(ACC_INT_SIGNAL, osWaitForever);
        
		int x, y, z;
		Accelerometer_get_data(&x, &y, &z);
		
    int roll = Accelerometer_get_roll(x, y, z);
    int pitch = Accelerometer_get_pitch(x, y, z);
		motor_move_to_angle(roll);
		
		printf("Pitch: %i, Roll: %i\n", pitch, roll);
	}
}

// External interrupt on line 1 : INT2 on acclerometer
void EXTI1_IRQHandler() {
    
    osSignalSet(tid_accelerometer, ACC_INT_SIGNAL);
    
    EXTI_ClearITPendingBit(EXTI_Line1);
    // Note that the interrupt on the accelerometer is cleared 
    // if, and ONLY if, data is read from it.  The status
    // registers that hold the interrupt line high cannot be modified manually
  
}

// Timer 3 interrupt for temperature)
void TIM3_IRQHandler() {
    
    osSignalSet(tid_temperature, TEMP_INT_SIGNAL);
    
    TIM_ClearITPendingBit( TIM3, TIM_IT_Update);
}