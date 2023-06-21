//////////////////////////////////////////////////
//  DIY Sim Wheel - For Arduino Leo/ProMicro    //
//                                              //
//  By Brendan Beavis                           //
//  v1.0                                        //
//////////////////////////////////////////////////

#include <RotaryEncoder.h>
#include <Joystick.h>
#include "Switch.h"

RotaryEncoder encoder(8, 9);

RotaryEncoder encoder2(15, A0);

//the delay time between checks
const uint32_t DELAY_TIME_MS = 50;

//a count of the buttons
const uint8_t TOTAL_BUTTONS = 12;   // 5 left, 5 right, 2 shifter, excl 4 for rotary

//declare our digital input pins on the board
const byte BUTTON_PINS[TOTAL_BUTTONS] = {
  2, 3, 4, 5,
  6, 7, 
  10, 14, 16,
   A1, A2, A3
   
};

//this is the value of the input from the switches
bool prevBtnState[TOTAL_BUTTONS];

//whats this for?
Switch buttons[TOTAL_BUTTONS];

void setup(void) {
  
  //Serial.begin(115200);

  //setup pinmodes and populate previous state array with falses;
  for (uint8_t i=0; i < TOTAL_BUTTONS;i++) {
    prevBtnState[i] = false;
    pinMode(BUTTON_PINS[i], INPUT_PULLUP);
  };

  Joystick.begin(false);
};

void loop(void) {

  
  static uint32_t previousTime = millis();
  static uint32_t buttonState = 0;

  static int pos = 0;
  static int pos2 = 0;
  encoder.tick();
  encoder2.tick();
  int newPos = encoder.getPosition();
  int newPos2 = encoder2.getPosition();
  
  if (pos > newPos) {
    Joystick.setButton(12, 1);
    Joystick.setButton(13, 0);
    pos = newPos;
  } // if 
  else if (pos < newPos) {
    Joystick.setButton(13, 1);
    Joystick.setButton(12, 0);
    pos = newPos;
  } // if 
  else{
    if (millis() - previousTime > DELAY_TIME_MS) {
      Joystick.setButton(13, 0);
      Joystick.setButton(12, 0);
    };
  }  
  if (pos2 > newPos2) {
    Joystick.setButton(15, 1);
    Joystick.setButton(14, 0);
    pos2 = newPos2;
  } // if 
  else if (pos2 < newPos2) {
    Joystick.setButton(14, 1);
    Joystick.setButton(15, 0);
    pos2 = newPos2;
  } // if 
  else{
    if (millis() - previousTime > DELAY_TIME_MS) {
      Joystick.setButton(14, 0);
      Joystick.setButton(15, 0);
    };
  }


  //read our values from the switches to the digital input pins, save values to buttons array
  for (uint8_t i=0; i < TOTAL_BUTTONS; i++) {
    
    buttons[i].update(!digitalRead(BUTTON_PINS[i]));
    if (buttons[i].on() != prevBtnState[i]) {
      Joystick.setButton(i, buttons[i].on());
    }
    prevBtnState[i] = buttons[i].on();
    //Serial.print(buttons[i].on());
  };
  //Serial.println();

  // Send new state to the host or wait for the delay limit.
  if (millis() - previousTime > DELAY_TIME_MS) {
    Joystick.sendState();
    previousTime = millis();
  };

};
