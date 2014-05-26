"""
integration test for arduino
    NOTE: requires the arduino to be plugged in
"""

import unittest
from comp.comm import ADCSArduino

class TestComm(unittest.TestCase):
    
    def setUp(self):
        self.imu = ADCSArduino(pra="/dev/ttyUSB0")

    def tearDown(self):
        self.imu.close_arduino_port()

#    def test_activate(self):
#        self.ar.activate()
#        self.assertEqual(self.ar.arduino.isOpen(), False)

#    def test_get_sensor_data(self):
#        self.ar.open_arduino_port()
#        data = self.ar.get_sensor_data()
#        print data
#        self.assertIsNotNone(data)
#        self.ar.close_arduino_port()

#    def test_cont_sample(self):
#        self.ar.open_arduino_port()
#        for i in range (5):
#            data = self.ar.get_sensor_data()
#            print data
#            self.assertIsNotNone(data)
#        self.ar.close_arduino_port()

#    def test_post_change(self):
#        self.ar.open_arduino_port()
#        self.ar.post_change(7)
#        self.ar.close_arduino_port()

    def test_open_imu(self):
        self.imu.open_imu_port()
        self.assertEqual(self.imu.imu.isOpen(), True)

    def test_get_data(self):
        d = self.imu._get_imu_data()
        self.assertIsNotNone(d)

if __name__ == "__main__":
    unittest.main()
