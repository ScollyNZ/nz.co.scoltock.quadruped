Install adafruit pwm library from IDE library manager
hook up pins to ESP D1 = SDA, D2 = SCL

Not sure which pins are the default I2C pins on the ESP8266 so edit the _i2c.begin() line in the driver library to _i2c.begin(D1, D2)

Leg Calibration:
| Leg | Lift | Shoulder |
| --- | ---  | ----     |
|   1 | 130-340 | 130-490 |
|   2 | 340-580 | 170 - 570 |
|   3 | 290-500 | 130 - 490 |
|   4 | 290-500 | 130 - 570 |   
