//
//  Log.cpp
//  
//
//  Created by Jason Lessels on 27/10/2014.
//
//

#include "Log.h"



// Constructor function
Log::Log(){
    
}

//A function to set the logger name

void Log::setName(const char* name){
    loggerName = name;
    
}
// Returns the name of the logger.
const char* Log::getName(){
    return loggerName;
    
}

void Log::setSampleInterval(unsigned long seconds){
    sampleInterval = seconds;
}
unsigned long Log::getSampleInterval(){
    return sampleInterval;
}


// Creates a new file if needbe. Sets up the SD card.
void Log::setupSDCard(){
    currentFileDir = "cur";
    historyFileDir = "hist";
    
    // Next thing to dois make sure ther

}