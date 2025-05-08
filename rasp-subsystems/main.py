from LineSensor import LineSensor
import serial
import time

def main():
    line_sensor = LineSensor(left_pin=4, right_pin=25)
    port = "/dev/ttyACM0"
    baudrate=9600
    timeout=1

    try:
        serial = serial.Serial(port, baudrate=baudrate, timeout=timeout)
        print(f"[SERIAL] Connected to {port} at {baudrate} baud.")
    except serial.SerialException as e:
        print(f"[ERROR] Serial connection failed: {e}")
        serial = None

    if(line_sensor.left_detected):
        msg = "Right: YES"
    else:
        msg = "Right: NO"
    
    if(line_sensor.right_detected):
        msg = "Left: YES"
    else:
        msg = "Left: NO"

    if serial and serial.is_open:
        serial.write((msg + "\n").encode())