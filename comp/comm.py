#! /usr/bin/env/python2

import serial
from time import sleep

class RequestError(Exception): pass

class ADCSArduino():

    def __init__(self, pr='/dev/ttyACM0', br=9600):
        self.arduino = serial.Serial()
        self.arduino.port = pr
        self.arduino.baudrate = br

    def activate(self):
        # starts up the adcs arduino for buisness
        self.arduino.open()
        while True:
            self._prep_request('post')
            sleep(1)
            print "output from serial: %s"%(self.arduino.readline())
            sleep(1)
    
    def deactivate(self);
        # closes down the adcs arduino
        self.arduino.close()

    def _prep_request(self, typ):
        # tells the arduino when we want to send/recieve data so
        # that the arduino does not have to take continous sensor
        # readings
        #   param: typ : String, the type of request, 
        #       'get' for arduino -> python
        #       'post' for python -> arduino
        self.arduino.flush()
        if (typ == 'get'):
            self.arduino.write('g')
        elif (typ == 'post'):
            self.arduino.write('p')
        else:
            raise RequestError('invalid request type')

    def get_sensor_data(self):
        # gets sensor data
        #   return : dict, the sensor data
        self._prep_request('get')
        data = self.arduino.readline()
        return data

    def post_change(self, dat):
        # posts needed change to the arduino
        #   param : dat : tuple, the desired change
        self._prep_request('post')
        self.arduino.write(str(dat))
