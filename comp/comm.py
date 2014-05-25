#! /usr/bin/env/python2

import serial
from time import sleep
import re

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
        # TODO: get val to change - will probably be put in control alg.
        self.post_change(4)
        
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

    # TODO: process serial string (see next line)
    def gen_dict(self, ard, imu):
        data = {}
        sens = ard.split('}')    # gets all elements
        sens.pop()                  # removes \n
            
        # required regexs
        preg = re.compile('photodiodes:[-0-9][^;]*')
        mxreg = re.compile('mag_x:[-0-9][^;]*')
        myreg = re.compile('mag_x:[-0-9][^;]*')

        for i in sens:
            on = re.search('[0-9]', i).group()
            p = re.search(preg, i).group().split(':')[1]
            mx = re.search(mxreg, i).group().split(':')[1]
            my = re.search(myreg, i).group().split(':')[1]

            data[on] = {}
            data[on]['photodiodes'] = float(p)
            data[on]['mag_x'] = float(mx)
            data[on]['mag_y'] = float(my)

        return data

    def _get_imu_data(self):
        return 0

    def get_sensor_data(self):
        # gets sensor data
        self._prep_request('get')
        sleep(1)
        data = self.arduino.readline()
        imu = self._get_imu_data()
        data = self.gen_dict(data, imu)
        return data

    def post_change(self, dat):
        # posts needed change to the arduino
        #   param : dat : tuple, the desired change
        self._prep_request('post')             
        self.arduino.write(str(dat))
        # next two lines are for testing
        #d = self.arduino.readline()
        #print d
