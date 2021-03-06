/*
   May 17, 2014

   A module to model the watsat adcs board that consists of 
    - 2 photodiodes
    - a temperature sensor
    - a double axis magnetometer
*/

#include <Arduino.h>
#include "SBoard.h"

SBoard::SBoard()
{

}

SBoard::SBoard(Sensor pd0, Sensor pd1, Sensor tmp, 
    Sensor mxm, Sensor mxd, Sensor mym, Sensor myd, 
    int ct0, int ct1, int ct2, int ct3)
{
    dat.pd0 = pd0;
    dat.pd1 = pd1;
    dat.tmp = tmp;
    dat.mxm = mxm;
    dat.mxd = mxd;
    dat.mym = mym;
    dat.myd = myd;

    ctrl0 = ct0;
    ctrl1 = ct1;
    ctrl2 = ct2;
    ctrl3 = ct3;

/*
    pinMode(ct0, OUTPUT);
    pinMode(ct1, OUTPUT);
    pinMode(ct2, OUTPUT);
    pinMode(ct3, OUTPUT);
*/
}

SBoard::SBoard(Sensor pd0, Sensor pd1, Sensor tmp, 
    int ct0, int ct1, int ct2, int ct3)
{
    mindat.pd0 = pd0;
    mindat.pd1 = pd1;
    mindat.tmp = tmp;

    ctrl0 = ct0;
    ctrl1 = ct1;
    ctrl2 = ct2;
    ctrl3 = ct3;
}

float SBoard::correctForTemp()
{
    if (!(dat.pd0.val) || !(dat.pd1.val) || !(dat.tmp.val))
    {
        return -1;
    }
    dat.pd0.val = dat.pd0.val - (0.1 * dat.tmp.val);
    dat.pd1.val = dat.pd1.val - (0.1 * dat.tmp.val);
    
    return ( 0.1 * dat.tmp.val);
}

float SBoard::setPhotodiodeAverage()
{
    if (!(dat.pd0.val) || !(dat.pd1.val))
    {
        return -1;
    }

    dat.pda = (dat.pd0.val + dat.pd1.val)/2;
    return dat.pda;
}

float SBoard::setMagVals()
{
    if (!(dat.mxm.val) || !(dat.mxd.val) || 
        !(dat.mym.val) || !(dat.myd.val))
    {
        return -1;
    }

    dat.ax = dat.mxm.val - dat.mxd.val;
    dat.ay = dat.mym.val - dat.myd.val;
}

void SBoard::setPinmodeActive(int cmd)
{
    digitalWrite(ctrl0, cmd/1000);
    digitalWrite(ctrl1, (cmd%1000)/100);
    digitalWrite(ctrl2, ((cmd%1000)%100)/10);
    digitalWrite(ctrl3, (((cmd%1000)%100)%10));
}

Data SBoard::readData()
{
    setPinmodeActive(dat.pd0.loc);
    dat.pd0.val = analogRead(dat.pd0.inp);   
    
    setPinmodeActive(dat.pd1.loc);
    dat.pd1.val = analogRead(dat.pd1.inp);    
    
    setPinmodeActive(dat.tmp.loc);
    dat.tmp.val = analogRead(dat.tmp.inp);    
   
    setPinmodeActive(dat.mxm.loc);
    dat.mxm.val = analogRead(dat.mxm.inp);    
    
    setPinmodeActive(dat.mxd.loc);
    dat.mxd.val = analogRead(dat.mxd.inp);    
    
    setPinmodeActive(dat.mym.loc);
    dat.mym.val = analogRead(dat.mym.inp);    
    
    setPinmodeActive(dat.myd.loc);
    dat.myd.val = analogRead(dat.mym.inp);    
    
    setMagVals();

    correctForTemp();
    setPhotodiodeAverage();

    return dat;
}

Data SBoard::readMinData()
{
    setPinmodeActive(dat.pd0.loc);
    dat.pd0.val = analogRead(dat.pd0.inp);   
    
    setPinmodeActive(dat.pd1.loc);
    dat.pd1.val = analogRead(dat.pd1.inp);    
    
    setPinmodeActive(dat.tmp.loc);
    dat.tmp.val = analogRead(dat.tmp.inp);    
    
    correctForTemp();
    setPhotodiodeAverage();

    return dat;
}

Data SBoard::sendData()
{
    return dat;
}
