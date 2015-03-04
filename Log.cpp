//
//  Log.cpp
//  
//
//  Created by Jason Lessels on 27/10/2014.
//
//

//#include <Arduino.h>

extern "C" {
    
#include <avr/power.h>
#include <avr/sleep.h>
    
    // Dummy "interrupt handler" for sleep to wake up to on alarm interrupt
    void log_wakeup(void)
    {
        
    }
    
}

#include "Log.h"
#include <stdio.h>
#include <string.h>
#include <Wire.h>
#include <DS1337.h>
#include <avr/sleep.h>
#include <avr/power.h>


// Constructor function
Log::Log(){
    // Default time out time
    TIME_OUT_MINUTES = 2;
    // This stuff is for the sleeping - has to be left in.
}

void Log::start(Stream *theStream){
    PORTD |= 0x04;
    DDRD &=~ 0x04;
    begin();
    _stream = theStream;
    resetTimeOut();


}

//A function to set the logger name

void Log::setName(char name[10]){
    strncpy(loggerName, name, 11);
    
}
//Returns the name of the logger.
char* Log::getName(){
   return loggerName;
    
}

void Log::setTimeOutTime(int time){
    TIME_OUT_MINUTES = time;
    //re-set timeout.
    resetTimeOut();
    
}


void Log::setSampleInterval(unsigned long seconds){
    sampleInterval = seconds;
}
unsigned long Log::getSampleInterval(){
    return sampleInterval;
}

void Log::updateCurrentTime() {
    readTime();
    currentTime = date_to_epoch_seconds();
}

void Log::setNextAlarm(int sampleInterval){
    updateCurrentTime();
    unsigned long nextAlarm = currentTime - (currentTime%sampleInterval)+sampleInterval;
    writeAlarm(nextAlarm);
    enable_interrupt();
    delay(100);
}



void Log::powerDOWN(){
    checkTimeOut();
    if(!stay_awake){
        setNextAlarm(sampleInterval);
        set_sleep_mode(SLEEP_MODE_PWR_DOWN);
        sleep_enable();
    
        power_all_disable();
        power_twi_disable();
        power_spi_disable();
        power_adc_disable();
    
        attachInterrupt(RTC_INT_NUMBER, log_wakeup, FALLING);

        sleep_mode();
    }
  
}

void Log::powerUP(){
    checkTimeOut();
    if(!stay_awake){
        sleep_disable();
        power_all_enable();
        power_twi_enable();
        power_spi_enable();
        power_adc_enable();
        detachInterrupt(RTC_INT_NUMBER);
        clear_interrupt();
    }
}



void Log::processMSG(char option){
    switch (option) {
        case 'I':
            //Send the information about the logger to the computer
            sendLoggerInfo();
            break;
        case 'T':
            //The computer wants to send an update of the time.
            receiveTime();
        default:
            break;
    }
    if (option == 'I') { // This is the the call to receive general info about the logger.

    }
    
}


void Log::sendLoggerInfo(){
    // Update the time in the library
    updateCurrentTime();
    // Now print it all to the serial line.
    Serial.print(getName());
    Serial.print(',');
    Serial.print(sampleInterval);
    Serial.print(',');
    Serial.println(currentTime);
}


void Log::checkForInput() {
    checkTimeOut();
    if(stay_awake) { // If the program is still within the first 2 minutes than look for msg's otherwise exit.
    
    char inChar;
        if(Serial.available()>0){
            inChar = (char)Serial.read();
            processMSG(inChar);
            
            // UPdate the current time.
    
        }
    }
 
}


void Log::checkTimeOut(){
    updateCurrentTime();
    stay_awake = currentTime<timeOutTime;

}

void Log::resetTimeOut(){
    updateCurrentTime();
    timeOutTime = currentTime + 60*TIME_OUT_MINUTES; // Time out 2 minutes after connection.
    stay_awake = currentTime<timeOutTime;
}


void Log::receiveTime(){
    delay(500);
    char c;
    bool msg_fin = false;
    char char_array[10];
    int i = 0;
    for(int i = 0; i<10;i++){
        c = (char)Serial.read();
        if(c == '#'){
            msg_fin = true;
        }
        if(!msg_fin){
            char_array[i] = c;
        }
    }
    // Now try and convert the char array to a time.
//    msg.toCharArray(char_array, sizeof(char_array));
    newTime = atol(char_array);
    if(newTime > 0){
        writeTime(newTime);
        updateCurrentTime();
        resetTimeOut();

    }
}



