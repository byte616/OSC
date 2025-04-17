import serial
import struct
import time

def send_kernelimg():
	with serial.Serial("/dev/ttyUSB0", baudrate=115200, timeout=10) as ser:
		with open("../kernel8.img", 'rb') as kernel:
			kernel_data = kernel.read()
			kernel_size = len(kernel_data)

			# send kernel.img size (<I means 4-bytes)
			header = struct.pack("<I", kernel_size)
			ser.write(header)

			# wait for bootloader handle header
			time.sleep(5)

			# send kernel.img
			ser.write(kernel_data)
			print("sending kernel completed")

if __name__ == "__main__":
	send_kernelimg()

