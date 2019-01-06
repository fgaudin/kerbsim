import krpc
import time
import serial
import io

conn = krpc.connect(name='Pitch/Heading/Roll')
vessel = conn.space_center.active_vessel

ser = serial.Serial('COM3', 9600, timeout=10)
sio = io.TextIOWrapper(io.BufferedRWPair(ser, ser))

previous_heading = None
previous_heading_time = None
rpm = None

while(True):
    line = ser.readline()
    while (line):
        print(line)
        line = ser.readline()

    time.sleep(0.1)
    heading = vessel.flight().heading
    current_time = time.time()
    if previous_heading is not None:    
        delta_heading = (heading - previous_heading + 180) % 360 - 180
        delta_time = current_time - previous_heading_time
        rpm = abs((delta_heading * 60 / delta_time) / 360)
    previous_heading = heading
    previous_heading_time = current_time
        
    print('heading: {}'.format(heading))
    print('rpm: {}'.format(rpm))

    if rpm is not None:
        sio.write(str(round(heading, 2)) + '|' + str(round(rpm, 2)))
        sio.flush() # it is buffering. required to get the data out *now*
