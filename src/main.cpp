/* ==================== ==================== ==================== ==================== 
 *  Wing Tang Wong's XMAS USB ORNAMENT Lighting Program
 *  ©2020 Wing Tang Wong
 * ==================== ==================== ==================== ==================== 
 *
 *  Code to control the hardware design of STM32F030F4 
 *  attached to 36 LED(s) in a charlieplexed configuration.
 *
 *  Communication with the MCU can be done via:
 *  - 4 pin UART header
 *  - USB serial via onboard CH340G
 *
 *  Power can be supplied via:
 *  - USB 5V
 *  - 5-12V via 2 pin
 *  - 3v3 via UART header
 *
 */

/* ==================== ==================== ==================== ==================== 
 *  Basic Arduino Boilerplate and libraries
 * ==================== ==================== ==================== ==================== 
 *
 * - Arduino.h  For basic Arduino stuff
 * - Wire.h     Mainly for I2C communication with the QMA7981 IMU
 *
 *
 */
#include <Arduino.h>
#include <Wire.h>

/* ==================== ==================== ==================== ==================== 
 * Global States of LED(s)
 * ==================== ==================== ==================== ==================== 
 * All default to zero
 * 0 = OFF
 * 128 = MAX ON
 */
uint8_t LED_STATE[36] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint8_t LED_COUNTER[36] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

/* ==================== ==================== ==================== ==================== 
 * Mapping pins of STM32 to rows
 * ==================== ==================== ==================== ==================== 
 *
 * PA0 - A (CharliePlexed LED Lines)
 * PA1 - B (CharliePlexed LED Lines)
 * PA4 - C (CharliePlexed LED Lines)
 * PA5 - D (CharliePlexed LED Lines)
 * PA6 - E (CharliePlexed LED Lines)
 * PA7 - F (CharliePlexed LED Lines)
 * PA13 - G (CharliePlexed LED Lines)
 * PA14 - H (CharliePlexed LED Lines)
 */
uint8_t ROW_PIN[8] = { PA0, PA1, PA4, PA5, PA6, PA7, PA13, PA14 };


/*
 * ==================== ==================== ==================== ==================== 
 * Charlie Plexing Map for LED1 through LED36
 * ==================== ==================== ==================== ==================== 
 *
 * 0 = LOW
 * 1 = HIGH
 * x = DONT CARE
 *
 * For LED(s) that do not conflict with one
 * another, it should be possible to light up
 * more than one LED at a time.
 *
 * D1  = A1, B0 , Cx , Dx , Ex , Fx , Gx , Hx
 * D2  = A0, B1 , Cx , Dx , Ex , Fx , Gx , Hx
 * D3  = Ax, B0 , C1 , Dx , Ex , Fx , Gx , Hx
 * D4  = Ax, B1 , C0 , Dx , Ex , Fx , Gx , Hx
 * D5  = Ax, Bx , C0 , D1 , Ex , Fx , Gx , Hx
 * D6  = Ax, Bx , C1 , D0 , Ex , Fx , Gx , Hx
 * D7  = Ax, Bx , Cx , D0 , E1 , Fx , Gx , Hx
 * D8  = Ax, Bx , Cx , D1 , E0 , Fx , Gx , Hx
 * D9  = Ax, Bx , Cx , Dx , E0 , F1 , Gx , Hx
 * D10 = Ax, Bx , Cx , Dx , E1 , F0 , Gx , Hx
 * D11 = Ax, Bx , Cx , Dx , Ex , F0 , G1 , Hx
 * D12 = Ax, Bx , Cx , Dx , Ex , F1 , G0 , Hx
 * D13 = Ax, Bx , Cx , Dx , Ex , Fx , G0 , H1
 * D14 = Ax, Bx , Cx , Dx , Ex , Fx , G1 , H0
 *
 * D15 = A0, Bx , C1 , Dx , Ex , Fx , Gx , Hx
 * D16 = A1, Bx , C0 , Dx , Ex , Fx , Gx , Hx
 * D17 = Ax, B0 , Cx , D1 , Ex , Fx , Gx , Hx
 * D18 = Ax, B1 , Cx , D0 , Ex , Fx , Gx , Hx
 * D19 = Ax, Bx , C0 , Dx , E1 , Fx , Gx , Hx
 * D20 = Ax, Bx , C1 , Dx , E0 , Fx , Gx , Hx
 * D21 = Ax, Bx , Cx , D0 , Ex , F1 , Gx , Hx
 * D22 = Ax, Bx , Cx , D1 , Ex , F0 , Gx , Hx
 * D23 = Ax, Bx , Cx , Dx , E0 , Fx , G1 , Hx
 * D24 = Ax, Bx , Cx , Dx , E1 , Fx , G0 , Hx
 * D25 = Ax, Bx , Cx , Dx , Ex , F0 , Gx , H1
 * D26 = Ax, Bx , Cx , Dx , Ex , F1 , Gx , H0
 *
 * D27 = A0, Bx , Cx , D1 , Ex , Fx , Gx , Hx
 * D28 = A1, Bx , Cx , D0 , Ex , Fx , Gx , Hx
 * D29 = Ax, B0 , Cx , Dx , E1 , Fx , Gx , Hx
 * D30 = Ax, B1 , Cx , Dx , E0 , Fx , Gx , Hx
 * D31 = Ax, Bx , C0 , Dx , Ex , F1 , Gx , Hx
 * D32 = Ax, Bx , C1 , Dx , Ex , F0 , Gx , Hx
 * D33 = Ax, Bx , Cx , D0 , Ex , Fx , G1 , Hx
 * D34 = Ax, Bx , Cx , D1 , Ex , Fx , G0 , Hx
 * D35 = Ax, Bx , Cx , Dx , E0 , Fx , Gx , H1
 * D36 = Ax, Bx , Cx , Dx , E1 , Fx , Gx , H0
 *
 */
uint8_t LED_PINS[36][8] = {
  { 1, 0 , 0 , 0 , 0 , 0 , 0 , 0 },
  { 0, 1 , 0 , 0 , 0 , 0 , 0 , 0 },
  { 0, 0 , 1 , 0 , 0 , 0 , 0 , 0 },
  { 0, 1 , 0 , 0 , 0 , 0 , 0 , 0 },
  { 0, 0 , 0 , 1 , 0 , 0 , 0 , 0 },
  { 0, 0 , 1 , 0 , 0 , 0 , 0 , 0 },
  { 0, 0 , 0 , 0 , 1 , 0 , 0 , 0 },
  { 0, 0 , 0 , 1 , 0 , 0 , 0 , 0 },
  { 0, 0 , 0 , 0 , 0 , 1 , 0 , 0 },
  { 0, 0 , 0 , 0 , 1 , 0 , 0 , 0 },
  { 0, 0 , 0 , 0 , 0 , 0 , 1 , 0 },
  { 0, 0 , 0 , 0 , 0 , 1 , 0 , 0 },
  { 0, 0 , 0 , 0 , 0 , 0 , 0 , 1 },
  { 0, 0 , 0 , 0 , 0 , 0 , 1 , 0 },
  { 0, 0 , 1 , 0 , 0 , 0 , 0 , 0 },
  { 1, 0 , 0 , 0 , 0 , 0 , 0 , 0 },
  { 0, 0 , 0 , 1 , 0 , 0 , 0 , 0 },
  { 0, 1 , 0 , 0 , 0 , 0 , 0 , 0 },
  { 0, 0 , 0 , 0 , 1 , 0 , 0 , 0 },
  { 0, 0 , 1 , 0 , 0 , 0 , 0 , 0 },
  { 0, 0 , 0 , 0 , 0 , 1 , 0 , 0 },
  { 0, 0 , 0 , 1 , 0 , 0 , 0 , 0 },
  { 0, 0 , 0 , 0 , 0 , 0 , 1 , 0 },
  { 0, 0 , 0 , 0 , 1 , 0 , 0 , 0 },
  { 0, 0 , 0 , 0 , 0 , 0 , 0 , 1 },
  { 0, 0 , 0 , 0 , 0 , 1 , 0 , 0 },
  { 0, 0 , 0 , 1 , 0 , 0 , 0 , 0 },
  { 1, 0 , 0 , 0 , 0 , 0 , 0 , 0 },
  { 0, 0 , 0 , 0 , 1 , 0 , 0 , 0 },
  { 0, 1 , 0 , 0 , 0 , 0 , 0 , 0 },
  { 0, 0 , 0 , 0 , 0 , 1 , 0 , 0 },
  { 0, 0 , 1 , 0 , 0 , 0 , 0 , 0 },
  { 0, 0 , 0 , 0 , 0 , 0 , 1 , 0 },
  { 0, 0 , 0 , 1 , 0 , 0 , 0 , 0 },
  { 0, 0 , 0 , 0 , 0 , 0 , 0 , 1 },
  { 0, 0 , 0 , 0 , 1 , 0 , 0 , 0 } 
};




/* 
 * ==================== ==================== ==================== ==================== 
 * Interrupt related variables. 
 * - Interrupt line is from the IMU
 * ==================== ==================== ==================== ==================== 
 */

uint8_t imuPIN = PB1;
volatile int imuSTATE = LOW;



/* 
 * ==================== ==================== ==================== ==================== 
 * Function declarations
 *
 * Sane folks probably just put this all into a 'main.h' file.... >_>
 * ==================== ==================== ==================== ==================== 
 */

void LED_ON( uint8_t led );
void LED_OFF( uint8_t led);
void LED_SET( uint8_t led, uint8_t val );
void DISPLAY_LED(uint8_t led);
void LED_DISPLAY();
void LED_TICK();
void IMU_SERVICE_UP();
void IMU_SERVICE_DOWN();


/* 
 * ==================== ==================== ==================== ==================== 
 * Setup
 * ==================== ==================== ==================== ==================== 
 */
void setup() {
  // Setup an interrupt for the IMU (PB1)
  //
  attachInterrupt(digitalPinToInterrupt(imuPIN),IMU_SERVICE_UP,RISING);
  attachInterrupt(digitalPinToInterrupt(imuPIN),IMU_SERVICE_DOWN,FALLING);

};

/* 
 * ==================== ==================== ==================== ==================== 
 * Main Loop
 * ==================== ==================== ==================== ==================== 
 */
void loop() {

};

/* 
 * ==================== ==================== ==================== ==================== 
 * functions to set LED state
 * ==================== ==================== ==================== ==================== 
 *
 * General idea... the value assigned to the state of the LED is the target that needs
 * to be hit to shut the light off.
 *
 * However, only one light should ever be on at one time. 
 */

void LED_ON( uint8_t led) {
  LED_STATE[led]=128;  
};

void LED_OFF( uint8_t led){
  LED_STATE[led]=0;
};

void LED_SET( uint8_t led, uint8_t val = 128) {
  if ( val >= 128 ) {
    LED_STATE[led]=128;
  } else {
    LED_STATE[led]=val;
  };
};

void LED_TICK() {
  for( uint8_t i=0; i<36; i++ ) {
    LED_COUNTER[i] += 1;
    if ( LED_COUNTER[i] > LED_STATE[i] ) { LED_COUNTER[i]=0; };
  };
};

void DISPLAY_LED(uint8_t led = 0) {
  if ( led < 36 ) {
    for( uint8_t row = 0; row < 8; row++ ) {
      digitalWrite( ROW_PIN[row], LED_PINS[led][row] );
    };
  }; 
};


void LED_DISPLAY() {
  for( uint8_t i=0; i<36; i++ ) {
    if ( LED_COUNTER[i] <= LED_STATE[i] ) {
      DISPLAY_LED(i);
    };
  };
};


/* 
 * ==================== ==================== ==================== ==================== 
 * ISR Handling Function from IMU
 * ==================== ==================== ==================== ==================== 
 */
void IMU_SERVICE_UP() {
  imuSTATE = HIGH;
};

void IMU_SERVICE_DOWN() {
  imuSTATE = LOW;
};


