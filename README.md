# ElectricMotorControl
In this repository you will find a file that controls the positioning of stepper motors (ARDUINO_STEPPER), a file that controls a brushed electric motor (Arduino_SLAVE) and a file that allows for a secondary arduino to recieve data from the controller (Arduino_MASTER) using Arduino. The programming language used is C++.

## Control of brushed electric motor
The brushed electric motors are positioned with the help of an encoder that reads the position of the shaft and a PID calculator.

## Control of stepper motor
Stepper motors are controlled step by step, counting number of steps made, taking into consideration the direction of rotation and also the rate of steps.

## Master/Slave connection
The connection between Arduino Master and Arduino Slave is made using I2C protocol for serial communication. The data transmitted is the position of the electric motors.
