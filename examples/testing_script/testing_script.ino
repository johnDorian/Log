//
//  testing_script.ino
//
//
//  Created by Jason Lessels on 27/10/2014.
//
//

#include <Log.h>

Log Log;


void setup(){
    Log.setName("hello");
    Log.setSampleInterval(10);
    Serial.begin(9600);
    Serial.print("Logger name: ");
    Serial.println(Log.getName());
    Serial.print("Sampling every ");
    Serial.print(Log.getSampleInterval());
    Serial.println(" seconds.");
}

void loop(){
}