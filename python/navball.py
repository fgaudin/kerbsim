import krpc
import time
import serial
import io

conn = krpc.connect(name='Pitch/Heading/Roll')
vessel = conn.space_center.active_vessel

ser = serial.Serial('COM3', 115200, timeout=10)

while(True):
    time.sleep(0.1)
    heading = vessel.flight().heading
    pitch = vessel.flight().pitch
    roll = vessel.flight().roll

    print('heading: {}'.format(heading))
    print('pitch: {}'.format(pitch))
    print('roll: {}'.format(roll))

    packet = "[{}|{}|{}]".format(
        round(heading, 2),
        round(pitch, 2),
        round(roll, 2),
    )
    ser.write(bytes(packet, 'utf-8'))

