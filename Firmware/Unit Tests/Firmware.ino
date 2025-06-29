
// Include Libraries
#include "Arduino.h"
#include "Buzzer.h"
#include "Adafruit_NeoPixel.h"
#include "Button.h"
#include "Wire.h"
#include "RTClib.h"
#include "Relay.h"


// Pin Definitions
#define BUZZER1_1_PIN_SIG	2
#define BUZZER2_2_PIN_SIG	3
#define LEDRGB_PIN_DIN	4
#define PUSHBUTTON_PIN_2	5
#define RELAYMODULE_PIN_SIGNAL	6
#define SLIDESWITCH_PIN_2	7



// Global variables and defines
#define LedRGB_NUMOFLEDS 1
// object initialization
Buzzer buzzer1_1(BUZZER1_1_PIN_SIG);
Buzzer buzzer2_2(BUZZER2_2_PIN_SIG);
Adafruit_NeoPixel LedRGB(LEDRGB_PIN_DIN);
Button pushButton(PUSHBUTTON_PIN_2);
RTC_DS3231 rtcDS;
Relay relayModule(RELAYMODULE_PIN_SIGNAL);
Button slideSwitch(SLIDESWITCH_PIN_2);


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    LedRGB.begin(); // This initializes the NeoPixel library.
    LedRGB.show(); // Initialize all leds to 'off'
    pushButton.init();
    if (! rtcDS.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
    }
    if (rtcDS.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtcDS.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtcDS.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    }
    slideSwitch.init();
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // Buzzer #1 - Test Code
    // The buzzer will turn on and off for 500ms (0.5 sec)
    buzzer1_1.on();       // 1. turns on
    delay(500);             // 2. waits 500 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    buzzer1_1.off();      // 3. turns off.
    delay(500);             // 4. waits 500 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    }
    else if(menuOption == '2') {
    // Buzzer #2 - Test Code
    // The buzzer will turn on and off for 500ms (0.5 sec)
    buzzer2_2.on();       // 1. turns on
    delay(500);             // 2. waits 500 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    buzzer2_2.off();      // 3. turns off.
    delay(500);             // 4. waits 500 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    }
    else if(menuOption == '3') {
    // LED - RGB Addressable, PTH, 5mm Diffused (5 Pack) - Test Code
    for(int i=0 ; i <= LedRGB_NUMOFLEDS ; i++){
    for (int k = 0 ; k <= 255 ; k++) {
    // set leds Color to RGB values, from 0,0,0 up to 255,255,255
    LedRGB.setPixelColor(i, LedRGB.Color(255-k,k,100)); // turn on green color on led #i.
    if (i > 0)
    LedRGB.setPixelColor(i-1, LedRGB.Color(0,0,0)); // turn off last led
    LedRGB.show(); //update led color to the hardware.
    delay(1);
    }
    }

    }
    else if(menuOption == '4') {
    // Mini Pushbutton Switch - Test Code
    //Read pushbutton state. 
    //if button is pressed function will return HIGH (1). if not function will return LOW (0). 
    //for debounce funtionality try also pushButton.onPress(), .onRelease() and .onChange().
    //if debounce is not working properly try changing 'debounceDelay' variable in Button.h
    bool pushButtonVal = pushButton.read();
    Serial.print(F("pushButtonVal: ")); Serial.println(pushButtonVal);

    }
    else if(menuOption == '5') {
    // RTC - Real Time Clock - Test Code
    //This will display the time and date of the RTC. see RTC.h for more functions such as rtcDS.hour(), rtcDS.month() etc.
    DateTime now = rtcDS.now();
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print('/');
    Serial.print(now.year(), DEC);
    Serial.print("  ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    delay(1000);
    }
    else if(menuOption == '6') {
    // Relay Module - Test Code
    // The relay will turn on and off for 500ms (0.5 sec)
    relayModule.on();       // 1. turns on
    delay(500);             // 2. waits 500 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    relayModule.off();      // 3. turns off.
    delay(500);             // 4. waits 500 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    }
    else if(menuOption == '7') {
    // SPDT Slide Switch (Breadboard-friendly) - Test Code
    //read Slide Switch state. 
    //if Switch is open function will return LOW (0). 
    //if it is closed function will return HIGH (1).
    bool slideSwitchVal = slideSwitch.read();
    Serial.print(F("Val: ")); Serial.println(slideSwitchVal);
    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) Buzzer #1"));
    Serial.println(F("(2) Buzzer #2"));
    Serial.println(F("(3) LED - RGB Addressable, PTH, 5mm Diffused (5 Pack)"));
    Serial.println(F("(4) Mini Pushbutton Switch"));
    Serial.println(F("(5) RTC - Real Time Clock"));
    Serial.println(F("(6) Relay Module"));
    Serial.println(F("(7) SPDT Slide Switch (Breadboard-friendly)"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
    			Serial.println(F("Now Testing Buzzer #1"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing Buzzer #2"));
    		else if(c == '3') 
    			Serial.println(F("Now Testing LED - RGB Addressable, PTH, 5mm Diffused (5 Pack)"));
    		else if(c == '4') 
    			Serial.println(F("Now Testing Mini Pushbutton Switch"));
    		else if(c == '5') 
    			Serial.println(F("Now Testing RTC - Real Time Clock"));
    		else if(c == '6') 
    			Serial.println(F("Now Testing Relay Module"));
    		else if(c == '7') 
    			Serial.println(F("Now Testing SPDT Slide Switch (Breadboard-friendly)"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}

/*******************************************************

*    Circuito.io is an automatic generator of schematics and code for off
*    the shelf hardware combinations.

*    Copyright (C) 2016 Roboplan Technologies Ltd.

*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.

*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.

*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*    In addition, and without limitation, to the disclaimers of warranties 
*    stated above and in the GNU General Public License version 3 (or any 
*    later version), Roboplan Technologies Ltd. ("Roboplan") offers this 
*    program subject to the following warranty disclaimers and by using 
*    this program you acknowledge and agree to the following:
*    THIS PROGRAM IS PROVIDED ON AN "AS IS" AND "AS AVAILABLE" BASIS, AND 
*    WITHOUT WARRANTIES OF ANY KIND EITHER EXPRESS OR IMPLIED.  ROBOPLAN 
*    HEREBY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT 
*    NOT LIMITED TO IMPLIED WARRANTIES OF MERCHANTABILITY, TITLE, FITNESS 
*    FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT, AND THOSE ARISING BY 
*    STATUTE OR FROM A COURSE OF DEALING OR USAGE OF TRADE. 
*    YOUR RELIANCE ON, OR USE OF THIS PROGRAM IS AT YOUR SOLE RISK.
*    ROBOPLAN DOES NOT GUARANTEE THAT THE PROGRAM WILL BE FREE OF, OR NOT 
*    SUSCEPTIBLE TO, BUGS, SECURITY BREACHES, OR VIRUSES. ROBOPLAN DOES 
*    NOT WARRANT THAT YOUR USE OF THE PROGRAM, INCLUDING PURSUANT TO 
*    SCHEMATICS, INSTRUCTIONS OR RECOMMENDATIONS OF ROBOPLAN, WILL BE SAFE 
*    FOR PERSONAL USE OR FOR PRODUCTION OR COMMERCIAL USE, WILL NOT 
*    VIOLATE ANY THIRD PARTY RIGHTS, WILL PROVIDE THE INTENDED OR DESIRED
*    RESULTS, OR OPERATE AS YOU INTENDED OR AS MAY BE INDICATED BY ROBOPLAN. 
*    YOU HEREBY WAIVE, AGREE NOT TO ASSERT AGAINST, AND RELEASE ROBOPLAN, 
*    ITS LICENSORS AND AFFILIATES FROM, ANY CLAIMS IN CONNECTION WITH ANY OF 
*    THE ABOVE. 
********************************************************/