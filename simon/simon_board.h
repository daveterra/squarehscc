#include "hardware.h"

void boardSetup() {
  //Enable pull ups on inputs
  pinMode(BUTTON_RED, INPUT_PULLUP);
  pinMode(BUTTON_GREEN, INPUT_PULLUP);
  pinMode(BUTTON_BLUE, INPUT_PULLUP);
  pinMode(BUTTON_YELLOW, INPUT_PULLUP);

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);

  pinMode(BUZZER1, OUTPUT);
  pinMode(BUZZER2, OUTPUT);
}

// Lights a given LEDs
// Pass in a byte that is made up from CHOICE_RED, CHOICE_YELLOW, etc
void setLEDs(byte leds) {
  if ((leds & CHOICE_RED) != 0)
    digitalWrite(LED_RED, HIGH);
  else
    digitalWrite(LED_RED, LOW);

  if ((leds & CHOICE_GREEN) != 0)
    digitalWrite(LED_GREEN, HIGH);
  else
    digitalWrite(LED_GREEN, LOW);

  if ((leds & CHOICE_BLUE) != 0)
    digitalWrite(LED_BLUE, HIGH);
  else
    digitalWrite(LED_BLUE, LOW);

  if ((leds & CHOICE_YELLOW) != 0)
    digitalWrite(LED_YELLOW, HIGH);
  else
    digitalWrite(LED_YELLOW, LOW);
}

// Returns a '1' bit in the position corresponding to CHOICE_RED, CHOICE_GREEN, etc.
byte checkButtons() {
  if (digitalRead(BUTTON_RED) == 0) return CHOICE_RED; 
  else if (digitalRead(BUTTON_GREEN) == 0) return CHOICE_GREEN; 
  else if (digitalRead(BUTTON_BLUE) == 0) return CHOICE_BLUE; 
  else if (digitalRead(BUTTON_YELLOW) == 0) return CHOICE_YELLOW;
  
  return CHOICE_NONE; // If no button is pressed, return none
}

byte randomChoice() {
  byte choices[4] = {CHOICE_RED, CHOICE_GREEN, CHOICE_BLUE, CHOICE_YELLOW};
  byte r = random(0, 4);
  return choices[r];
}

// Toggle buzzer every buzz_delay_us, for a duration of buzz_length_ms.
void buzzSound(int buzz_length_ms, int buzz_delay_us) {
  // Convert total play time from milliseconds to microseconds
  long buzz_length_us = buzz_length_ms * (long)1000;

  // Loop until the remaining play time is less than a single buzz_delay_us
  while (buzz_length_us > (buzz_delay_us * 2)) {
    buzz_length_us -= buzz_delay_us * 2; //Decrease the remaining play time
    // Toggle the buzzer at various speeds
    digitalWrite(BUZZER1, LOW);
    digitalWrite(BUZZER2, HIGH);
    delayMicroseconds(buzz_delay_us);

    digitalWrite(BUZZER1, HIGH);
    digitalWrite(BUZZER2, LOW);
    delayMicroseconds(buzz_delay_us);
  }
}

// Light an LED and play tone
// Red, upper left:     440Hz - 2.272ms - 1.136ms pulse
// Green, upper right:  880Hz - 1.136ms - 0.568ms pulse
// Blue, lower left:    587.33Hz - 1.702ms - 0.851ms pulse
// Yellow, lower right: 784Hz - 1.276ms - 0.638ms pulse
void toner(byte which, int buzz_length_ms) {
  setLEDs(which); //Turn on a given LED

  //Play the sound associated with the given LED
  switch(which)  {
  case CHOICE_RED:
    buzzSound(buzz_length_ms, 1136); 
    break;
  case CHOICE_GREEN:
    buzzSound(buzz_length_ms, 568); 
    break;
  case CHOICE_BLUE:
    buzzSound(buzz_length_ms, 851); 
    break;
  case CHOICE_YELLOW:
    buzzSound(buzz_length_ms, 638); 
    break;
  }
  setLEDs(CHOICE_NONE); // Turn off all LEDs
}

// Wait for a button to be pressed. 
// Returns one of LED colors (LED_RED, etc.) if successful, 0 if timed out
byte waitForButton(int wait_time) {
  long startTime = millis(); // Remember the time we started the this loop
  // Loop until too much time has passed
  while ( (millis() - startTime) < (wait_time*1000)) {
    byte button = checkButtons();

    if (button != CHOICE_NONE) {
      toner(button, 150); // Play the button the user just pressed
      while(checkButtons() != CHOICE_NONE) ;  // Now let's wait for user to release button
      delay(10); // This helps with debouncing and accidental double taps
      return button;
    }

  }

  return CHOICE_NONE; // If we get here, we've timed out!
}

