#! /usr/bin/env/python2
# NOTE: didn't actually test the code... :(

import serial

port = None             # the port the arduino is located 
baud_rate =  None       # the baud rate of the arduino

class RequestError(Exception): pass

def main():
    arduino = serial.Serial(port, baud_rate)
    while True:
        dat = get_sensor_data(arduino)          # Get data
        pos = determine_attitude(dat)           # Process data
        chng = determine_adjustment(pos)        # Math...
        post_change(arduino, chng)              # Tells arduino the change

def _prep_request(typ):
    # tells the arduino when we want to send/recieve data so that the 
    # arduino does not have to take continous sensor readings
    #   param: typ : String, the type of request, 
    #       'get' for arduino -> python
    #       'post' for python -> arduino
    if (typ == 'get'):
        con.write(1111)
    elif (typ == 'post'):
        con.write(0000)
    else:
        raise RequestError('invalid request type')

def get_sensor_data(con):
    # gets sensor data
    #   param : con : Serial instance, the connection to the arduino
    #   return : dict, the sensor data
    # TODO: get sensor data
    #   since we are using a mux, I imagine we can't get all the data at
    #   the same instane.  This method will have to build a dict (subject
    #   to change) with the sensor data and return it
    #   should the ardino return all the sensor data in one request?
    _prep_request('get')
    data = con.readline()
    return data

def determine_attitude(dat):
    # determines satellite attitude
    #   param : dat : dict, the positional information from sensors
    #   return : tuple, the position of the satellite relative to? 
    # TODO: modified b-dot algorithm?
    att = (None, None, None)
    return att

def determine_adjustment(pos):
    # determines how much the satellite needs to move to get to desired pos
    #   param : pos : tuple for the x, y, z pos
    #   return : tuple, the change needed to get to the desired postition
    # TODO: math to determine position -> vector projection?
    chng = (None, None, None)
    return chng

def post_change(con, dat):
    # posts needed change to the arduino
    #   param : con : Serial instance, the connection to the arduino
    #   param : dat : tuple, the desired change
    _prep_request('post')
    con.write(str(dat))
 
if __name__ == '__main__':
    main()