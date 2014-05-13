#! /usr/bin/env/python2

import serial
from time import sleep

port = '/dev/ttyACM0'     # the port the arduino is located 
baud_rate =  9600     # the baud rate of the arduino

class RequestError(Exception): pass

def main():
    counter = 32
    arduino = serial.Serial()
    arduino.port = port
    arduino.baudrate = 9600
    arduino.open()

    while True:
        counter += 1
        arduino.write(str(chr('g')))
        print "output from serial for %s: "%(counter)
        print arduino.read()
        sleep(1)
        if counter == 255:
            counter = 32

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

def post_change(con, dat):
    # posts needed change to the arduino
    #   param : con : Serial instance, the connection to the arduino
    #   param : dat : tuple, the desired change
    _prep_request('post')
    con.write(str(dat))
 
if __name__ == '__main__':
    main()
