//
//  Log.h
//  
//
//  Created by Jason Lessels on 27/10/2014.
//
//


#ifndef LOG_h
#define LOG_h

// include types & constants of Wiring core API
#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#define I2C_READ	Wire.read
#define I2C_WRITE	Wire.write
#else
#include <WProgram.h>
#include <WConstants.h>
#define I2C_READ	Wire.receive
#define I2C_WRITE	Wire.send
#endif

// include types & constants of Wire ic2 lib
#include <DS1337.h>
#include <Wire.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include "Stream.h"

#define SERIAL_BUAD_RATE 9600



class Log: public DS1337{
public:
    Log();
    void setName(char name[10]);
    char* getName();
    void setSampleInterval(unsigned long seconds);
    unsigned long getSampleInterval();
    void setNextAlarm(int sampleInterval);
    void powerDOWN();
    void powerUP();
    void updateCurrentTime();
    void processMSG(char option);
    void sendLoggerInfo();
    void start(Stream *theStream);
    void checkForInput();

    void setTimeOutTime(int time);
    void checkTimeOut();
    void resetTimeOut();
    void receiveTime();
    
private:

    char loggerName[10];
    void setupSDCard();
    unsigned long sampleInterval;
    unsigned long currentTime;
    unsigned long timeOutTime;
    unsigned long newTime;
    Stream *_stream;
    bool stay_awake;
    int TIME_OUT_MINUTES;


};

#endif