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

SBoard::SBoard(Sensor pd0, Sensor pd1, Sensor tmp, Sensor mxm, Sensor mxd, Sensor mym, Sensor myd)
{
    dat.pd0 = pd0;
    dat.pd1 = pd1;
    dat.tmp = tmp;
    dat.mxm = mxm;
    dat.mxd = mxd;
    dat.mym = mym;
    dat.myd = myd;
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
