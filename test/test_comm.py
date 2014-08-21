"""
integration test for arduino
    NOTE: requires the arduino to be plugged in
"""

import unittest
from comp.comm import ADCSArduino

class TestComm(unittest.TestCase):
    
    def setUp(self):
        self.ard = ADCSArduino(pr="/dev/ttyACM0")

    def tearDown(self):
        self.ard.close_arduino_port()

    def test_activate(self):
        self.ard.activate()
        self.assertEqual(self.ard.arduino.isOpen(), False)

    def test_get_sensor_data(self):
        self.ard.open_arduino_port()
        data = self.ard.get_sensor_data()
        print data
        self.assertIsNotNone(data)
        self.ard.close_arduino_port()

    def test_cont_sample(self):
        self.ard.open_arduino_port()
        for i in range (5):
            data = self.ard.get_sensor_data()
            print data
            self.assertIsNotNone(data)
        self.ard.close_arduino_port()

    def test_post_change(self):
        self.ard.post_change(7)

#    def test_workflow(self):
        # TODO: test full workflow
#        pass
    
if __name__ == "__main__":
    unittest.main()
