//
//  Log.h
//  
//
//  Created by Jason Lessels on 27/10/2014.
//
//


#ifndef LOG_h
#define LOG_h




class Log
{
public:
    Log();
    void setName(const char* name);
    const char* getName();
    void setSampleInterval(unsigned long seconds);
    unsigned long getSampleInterval();

    
private:
    const char* loggerName;
    const char*  currentFileDir;
    const char*  historyFileDir;
    void setupSDCard();
    unsigned long sampleInterval;
    
    
};

#endif