//
//  testing_script.ino
//
//
//  Created by Jason Lessels on 27/10/2014.
//
//

#include <Wire.h>
#include <DS1337.h>
#include <Log.h>
#include <avr/sleep.h>
#include <avr/power.h>

Log Log;


void setup(){
// The next two lines are needed - I don't know why.
Wire.begin();

Serial.begin(9600);


analogReference(INTERNAL);


Log.start(&Serial);
Log.setName("hello");
Log.setSampleInterval(15);
Log.setTimeOutTime(2);


}

void loop(){
Log.checkForInput();
//Shut down the microcrontroller, and all routines.
Log.powerDOWN();
//

//Wake everything up.
Log.powerUP();

}


