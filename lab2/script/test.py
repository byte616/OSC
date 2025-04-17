import serial
import struct
import time

ser = serial.Serial("/dev/ttyUSB0", baudrate=115200, timeout=10)
ser.write(b'h')
