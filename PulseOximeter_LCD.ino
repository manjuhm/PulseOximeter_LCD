#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "MAX30100_PulseOximeter.h"
LiquidCrystal_I2C lcd(0x27,16,2);  //0x27 is the i2c address, while 16 = columns, and 2 = rows. 

#define REPORTING_PERIOD_MS     1000
 
PulseOximeter pox;
uint32_t tsLastReport = 0;
 
void onBeatDetected()
{
    Serial.println("Beat!");
}
 
void setup()
{

  lcd.init();                 //Initialize the LCD
  lcd.backlight();            //Activate the backlight     
  lcd.home(); 
     

    // Initialize the PulseOximeter instance
    // Failures are generally due to an improper I2C wiring, missing power supply
    // or wrong target chip
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }
     pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
 
    // Register a callback for the beat detection
    pox.setOnBeatDetectedCallback(onBeatDetected);

  
}
 
void loop()
{

    pox.update();
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {

     
// Display on LCD

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("BPM: ");
        lcd.print(pox.getHeartRate());
        
        lcd.setCursor(0,1);
        lcd.print("SpO2: ");
        lcd.print(pox.getSpO2());
        lcd.print("%");

        tsLastReport = millis();
        
    }


}
