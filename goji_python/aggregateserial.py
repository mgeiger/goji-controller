from serial import *
from threading import Thread

last_received = ''

def receiving(ser):
	global last_received
	buffer = ''

	while True:
		# last_received = ser.readline()
		buffer += ser.read(ser.inWating())
		if '\n' in buffer:
			last_received, buffer = buffer.split('\n')[-2:]

if __name__ == '__main__'
	ser = Serial(
		port=None,
		baudrate=9600,
		bytesize=EIGHTBITS,
		parity=PARITY_NONE,
		stopbits=STOPBITS_ONE,
		timeout=0.1,
		xonxoff=0,
		rtscts=0,
		interCharTimeout=None
	)

	Thread(target=receiving, args=(ser,)).start()