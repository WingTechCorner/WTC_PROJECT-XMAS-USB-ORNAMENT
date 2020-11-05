/*
 *  Wing Tang Wong's XMAS USB ORNAMENT Lighting Program
 *
 */

#include <Arduino.h>
#include <Wire.h>

// Charlieplexed LED mappings for single LED on at a time
short LEDPINS[36][8] = {
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
  { 0, 0 , 0 , 0 , 1 , 0 , 0 , 0 } };




void setup() {



};



void loop() {

};




void LED_ON( int led) {



};







/*
 * Charlie Plexing Map for LED1 through LED36
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
