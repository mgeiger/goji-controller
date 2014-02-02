import serial
import time

ser = serial.Serial("/dev/ttyUSB0", 9600, timeout=1)

while 1:
	time.sleep(1)
	values = ser.readline()
	items = values.split(',')
	for item in items:
		if item == " ":
			print "Empty"
		else:
			print item

# finally:
# 	ser.close()