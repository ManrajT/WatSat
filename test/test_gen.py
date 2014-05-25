from comp.comm import ADCSArduino

a = ADCSArduino()
st = '0{photodiodes:417.60; mag_x:-3.00; mag_y:-3.00;}1{photodiodes:405.10; mag_x:-2.00; mag_y:-1.00;}\n'
thing = a.gen_dict(st, 0)
print thing
