#ifndef SBoard_h
#define SBoard_h

#include <Arduino.h>
#include <Wire.h>

struct Sensor
{
    float val;
    int loc;
    int inp;
};

struct Data
{
    Sensor pd0;      // first photodiode
    Sensor pd1;      // second photodiode
    float pda;      // photodiode average
    Sensor tmp;      // temperature
    Sensor mxm;
    Sensor mxd;
    Sensor mym;
    Sensor myd;
    float ax;       // mangetometer x-axis
    float ay;       // magnetometer y-axis
};

struct MinDat
{
    Sensor pd0;      // first photodiode
    Sensor pd1;      // second photodiode
    float pda;      // photodiode average
    Sensor tmp;      // temperature
    float ax = 0;
    float ay = 0;
};

class SBoard
{
    public:
        SBoard();
        SBoard(Sensor pd0, Sensor pd1, Sensor tmp, 
                Sensor mx_m, Sensor mx_d, Sensor my_m, 
                Sensor my_d, int ct0, int ct1, int ct2, int ct3);
       SBoard(Sensor pd0, Sensor pd1, Sensor tmp, 
                int ct0, int ct1, int ct2, int ct3);

        Data readData();
        Data readMinData();
        Data sendData();
       
    private:
        int ctrl0;
        int ctrl1;
        int ctrl2;
        int ctrl3;
        Data dat;
        MinDat mindat;
        float correctForTemp();
        float setPhotodiodeAverage();
        float setMagVals();
        void setPinmodeActive(int cmd);
};

#endif
