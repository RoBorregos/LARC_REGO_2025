from LineSensor.LineSensor import LineSensor
from vision.CameraLower import CameraLower
from vision.CameraUpper import CameraUpper
from vision.BlueObstacleDetector import BlueObstacleDetector
from vision.StorageDetector import StorageDetector
from vision.TreeDetector import TreeDetector
from Elevator.Elevator import Elevator
import RPi.GPIO as GPIO
import time
import serial

def main():
    # Line Sensor Setup
    line_sensor = LineSensor(left_pin=11, right_pin=16)
    elevator = Elevator()
    
    # Camera Setup
    port = "/dev/ttyACM0"
    baudrate = 9600
    timeout = 1

    """ cam_up = CameraUpper(port=port, camera_index=0)
    cam_low = CameraLower(port=port, camera_index=2) """

    try:
        ser = serial.Serial(port, baudrate=baudrate, timeout=timeout)
        print(f"[SERIAL] Connected to {port} at {baudrate} baud.")
    except serial.SerialException as e:
        print(f"[ERROR] Serial connection failed: {e}")
        ser = None

    try:
        while True:
            # Run vision systems
            """ cam_up.run()
            cam_low.run()
            cam_low.receive_state() """

            if ser and ser.is_open:
                if ser.in_waiting:
                    command = ser.readline().decode().strip()

                    print("RECEIVED:" + command)

                    if command.startswith("SET_SPEED:"):
                        try:
                            speed = int(command.split(":")[1])
                            elevator.move(speed)
                            ser.write(b"OK\n")
                        except ValueError:
                            print(f"[ERROR] Invalid speed value in command: {command}")
                            ser.write(b"ERROR: Invalid speed value\n")
                        except Exception as e:
                            print(f"[ERROR] Failed to move elevator: {e}")
                            ser.write(b"ERROR: Failed to move elevator\n")

            msg = ""
            if line_sensor.left_detected():
                msg += "Left: YES "
            else:
                msg += "Left: NO "

            if line_sensor.right_detected():
                msg += "Right: YES"
            else:
                msg += "Right: NO"

            if ser and ser.is_open:
                #print("MESSAGE SENT: " + msg)
                ser.write((msg + "\n").encode())

            time.sleep(0.05)  # Adjusted to reduce CPU load and allow camera time

    except KeyboardInterrupt:
        print("\n[INFO] Cleaning up...")
        if ser and ser.is_open:
            ser.close()
        elevator.cleanup()
        GPIO.cleanup()

if __name__ == "__main__":
    main()
