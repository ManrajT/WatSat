#ifndef SBoard_h
#define SBoard_h

#include <Arduino.h>
#include <Wire.h>

struct Data
{
    float pd0;      // first photodiode
    float pd1;      // second photodiode
    float pda;      // photodiode average
    float tmp;      // temperature
    float ax;       // mangetometer x-axis
    float ay;       // magnetometer y-axis
};

class SBoard
{
    public:
        SBoard();
        SBoard(int acc[]);
        
        void fillDat(float pd0, float pd1, float pda, float tmp, float ax, float ay);
        void sendData();

    private:
        Data dat;
        int access[];
        void correctForTemp();
        int getPhotodiodeAverage();
};

#endif
