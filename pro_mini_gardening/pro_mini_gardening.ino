#include "LowPower.h"
#include "TimeLib.h"

int sleep_counter = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // remove Serials when installing
}

// estimate that 1 powerdown cycle is 8.5124 s
// 12 hours would have sleep_counter reach 5074.9
// Using 5077 to reach 12hrs and 18mins
// Could probably do a full run to get an exact number one day
void loop() {
  // Sleep section
  Serial.println("Begin sleep cycle (500 ms delay).");
  delay(500);
  // Turn off the outlet before starting
  
  bool sleep = false;
  while(sleep){
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
    sleep_counter++;
    if(sleep_counter >= 100){
      sleep = false;
      sleep_counter = 0;
    }
  }
  Serial.println("16 seconds have passed");

  // Wake section
  // hour, minute, seconds etc all have rollover at the normal times (61 seconds cannot exist)
  // for the full wake section
  setTime(12,0,0,9,11,2001); // set time index to 12pm Sept 11 2001
  // Turn on the outlet now
  time_t dawn = now();
  while(second() < 62){
    Serial.println(second());
    delay(999);
  }
  Serial.println("loop exited");
}
