from LineSensor.LineSensor import LineSensor
from vision.CameraLower import CameraLower
from vision.CameraUpper import CameraUpper
from vision.BlueObstacleDetector import BlueObstacleDetector
from vision.StorageDetector import StorageDetector
from vision.TreeDetector import TreeDetector

import time
import serial

def main():
    # Line Sensor Setup
    line_sensor = LineSensor(left_pin=4, right_pin=25)

    # Camera Setup
    port = "/dev/ttyACM0"
    baudrate = 9600
    timeout = 1

    cam_up = CameraUpper(port=port, camera_index=0)
    cam_low = CameraLower(port=port, camera_index=2)

    try:
        ser = serial.Serial(port, baudrate=baudrate, timeout=timeout)
        print(f"[SERIAL] Connected to {port} at {baudrate} baud.")
    except serial.SerialException as e:
        print(f"[ERROR] Serial connection failed: {e}")
        ser = None
    while True:
        # Run vision systems
        cam_up.run()
        cam_low.run()
        cam_low.receive_state()

        # Serial commands for elevator
        if ser and ser.is_open:
            if ser.in_waiting:
                command = ser.readline().decode().strip()

                if command.startswith("SET_TARGET:"):
                    try:
                        position = int(command.split(":")[1])
                        elevator.set_target_position(position)
                        ser.write(b"OK\n")
                    except:
                        ser.write(b"ERROR\n")

                elif command.startswith("SET_POSITION:"):
                    try:
                        position = int(command.split(":")[1])
                        elevator.encoder_position = position
                        elevator.set_target_position(position)
                        ser.write(b"OK\n")
                    except:
                        ser.write(b"ERROR\n")

                elif command == "GET_POS":
                    pos = elevator.get_position()
                    ser.write(f"{pos}\n".encode())

                elevator.update_position_control()

        # Line Sensor Messages
        msg = ""
        if line_sensor.left_detected:
            msg += "Left: YES "
        else:
            msg += "Left: NO "

        if line_sensor.right_detected:
            msg += "Right: YES"
        else:
            msg += "Right: NO"

        if ser and ser.is_open:
            ser.write((msg + "\n").encode())

        time.sleep(0.1)  # Adjusted to reduce CPU load and allow camera time

if __name__ == "__main__":
    main()
