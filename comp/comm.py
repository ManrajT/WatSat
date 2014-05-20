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

    def open_port(self):
        # opens the serial port if it is not already open
        if self.arduino.isOpen():
            return
        else:
            self.arduino.open()

    def close_port(self):
        # closes the serial port if it not already closed
        if self.arduino.isOpen():
            self.arduino.close()
        else:
            return

    def activate(self):
        # starts up the adcs arduino for buisness
        # changes the attitude of the satellite to the desired pos and
        # then returns the attitude when it has finished
        #
        # call this method from the event queue 
        self.open_port()

        data = self.get_sensor_data()
        self.call_control(data)
        sleep(1) 
        self.post_change('placeholder')
        
        self.close_port()
    
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
        # TODO: process serial string (see next line)
        # 0{photodiodes:417.60; mag_x:-3.00; mag_y: -3.00;}1{photodiodes:405.10; mag_x:-2.00; mag_y: -1.00;}\n
        def gen_dict(string):
            dat = string
            return dat

        self._prep_request('get')
        sleep(1)
        data = self.arduino.readline()
        data = gen_dict(data)
        #print "output from serial: %s"%(data)
        return data

    def post_change(self, dat):
        # posts needed change to the arduino
        #   param : dat : tuple, the desired change
        self._prep_request('post')             
        sleep(1)
        #print "output from serial: %s"%(self.arduino.readline())
        #self.arduino.write(str(dat))
