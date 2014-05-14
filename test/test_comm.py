"""
integration test for arduino
    NOTE: requires the arduino to be plugged in
"""

import unittest
from comp.comm import ADCSArduino

class TestComm(unittest.TestCase):
    
    def setUp(self):
        self.ar = ADCSArduino()

    def tearDown(self):
        self.ar.close_port()

    def test_activate(self):
        self.ar.activate()
        self.assertEqual(self.ar.arduino.isOpen(), False)

    def test_get_sensor_data(self):
        self.ar.open_port()
        data = self.ar.get_sensor_data()
        # TODO: make this more representative of what the output 
        # should be, fix it in general
        self.assertIsNotNone(data)
        self.ar.close_port()

    def test_post_change(self):
        self.ar.open_port()
        da = "placeholder"
        self.ar.post_change(da)
        self.ar.close_port()

    def test_workflow(self):
        # TODO: test full workflow
        pass

if __name__ == "__main__":
    unittest.main()
