#! /usr/bin/env/python2

import serial
from time import sleep

class RequestError(Exception): pass

class ADCSArduino():

    def __init__(self, pr='/dev/ttyACM0', br=9600):
        self.arduino = serial.Serial()
        self.arduino.port = pr
        self.arduino.baudrate = br
        # calibration algorithm

    def call_control(self, data):
        # call control algorithm
        pass

    def activate(self):
        # starts up the adcs arduino for buisness
        # changes the attitude of the satellite to the desired pos and
        # then returns the attitude when it has finished
        #
        # call this method from the event queue 
        self.arduino.open()
        
        data = self.get_sensor_data()
        self.call_control(data)
        sleep(1) 
        self.post_change('placeholder')
        
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
        # TODO: processing
        #   return : dict, the sensor data
        self._prep_request('get')
        sleep(1)
        data = self.arduino.readline()           
        print "output from serial: %s"%(data)
        return data

    def post_change(self, dat):
        # posts needed change to the arduino
        #   param : dat : tuple, the desired change
        self._prep_request('post')             
        sleep(1)
        print "output from serial: %s"%(self.arduino.readline())
        #self.arduino.write(str(dat))
