#include <Filters.h>
#include <Filters/SMA.hpp>

// Pins for motor control
const byte ENABLE_PIN = 5;   // PWM pin for speed control
const byte DIR_PIN_A = 3;
const byte DIR_PIN_B = 4;

// LED pin
const byte LED_PIN = 6;

// Sound sensor pin
const int sound = A0;

// Sound threshold
const int sound_thres = 50;

// Debounce variables
volatile unsigned long time_interrupt = 0;
volatile bool count_just_increased = false;

// State variable for fan and LED (0,1,2)
int state = 0;

// Cooldown time (milliseconds) to wait between toggles
const unsigned long cooldown = 500; 
unsigned long last_time = 0;

// Filter for sound smoothing
SMA<10, float, float> average = {0};

void setup() {
  pinMode(ENABLE_PIN, OUTPUT);
  pinMode(DIR_PIN_A, OUTPUT);
  pinMode(DIR_PIN_B, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  unsigned long t = millis();

  int sound_val = analogRead(sound);
  int sound_avg = average(sound_val);

  if (sound_avg > sound_thres) {
    debounce();
  }

  if (count_just_increased) {
    // Check cooldown before toggling
    if (t - last_time > cooldown) {
      // Cycle through the states
      state = (state + 1) % 3;
      last_time = t; 
      Serial.print("State: ");
      Serial.println(state);
    } else {
      Serial.println("Cooldown...");
    }
    count_just_increased = false;
  }

  // Set motor and LED based on  state
  switch (state) {
    case 0:
      // turned off
      analogWrite(ENABLE_PIN, 0);
      analogWrite(LED_PIN, 0);
      break;

    case 1:
      // low speed & brightness
      digitalWrite(DIR_PIN_A, HIGH);
      digitalWrite(DIR_PIN_B, LOW);
      analogWrite(ENABLE_PIN, 175);  
      analogWrite(LED_PIN, 100);     
      break;

    case 2:
      // high speed & brightness
      digitalWrite(DIR_PIN_A, HIGH);
      digitalWrite(DIR_PIN_B, LOW);
      analogWrite(ENABLE_PIN, 255);  
      analogWrite(LED_PIN, 255);    
      break;
  }

  //delay(10);
}

// Debouncer funciton
void debounce() {
  unsigned long new_time_interrupt = millis();

  if (new_time_interrupt - time_interrupt > 50) {
    count_just_increased = true;
    time_interrupt = new_time_interrupt;
  } else {
    Serial.println("Bouncing!");
  }
}