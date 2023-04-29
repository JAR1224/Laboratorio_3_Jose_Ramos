import serial
import time

f = open('medicion_4canales.csv','w')

serialPort = serial.Serial(
    port="COM1", baudrate=9600, bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE
)
serialString = ""  # Used to hold data coming over UART
while 1:
    # Wait until there is data waiting in the serial buffer
    if serialPort.in_waiting > 0:

        # Read data out of the buffer until a carraige return / new line is found
        serialString = serialPort.readline()
        f.write(serialString.decode("Ascii").strip('\n'))
        # Print the contents of the serial data
        try:
            print(serialString.decode("Ascii"))
        except:
            pass
