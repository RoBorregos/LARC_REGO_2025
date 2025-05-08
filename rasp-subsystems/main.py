from LineSensor import LineSensor
from Elevator import Elevator
import serial
import time

def main():
    line_sensor = LineSensor(left_pin=4, right_pin=25)
    elevator = Elevator()
    port = "/dev/ttyACM0"
    baudrate=9600
    timeout=1

    try:
        serial = serial.Serial(port, baudrate=baudrate, timeout=timeout)
        print(f"[SERIAL] Connected to {port} at {baudrate} baud.")
    except serial.SerialException as e:
        print(f"[ERROR] Serial connection failed: {e}")
        serial = None

    while True:
        if serial and serial.is_open:
            if serial.in_waiting:
                command = serial.readline().decode().strip()
                
                # Handle elevator commands
                if command.startswith("SET_TARGET:"):
                    try:
                        position = int(command.split(":")[1])
                        elevator.set_target_position(position)
                        serial.write(b"OK\n")
                    except:
                        serial.write(b"ERROR\n")
                
                elif command.startswith("SET_POSITION:"):
                    try:
                        position = int(command.split(":")[1])
                        elevator.encoder_position = position  # Reset current position
                        elevator.set_target_position(position)  # Also set as target
                        serial.write(b"OK\n")
                    except:
                        serial.write(b"ERROR\n")
                
                elif command == "GET_POS":
                    pos = elevator.get_position()
                    serial.write(f"{pos}\n".encode())
                
                # Update elevator position control
                elevator.update_position_control()

        # Line sensor status
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
        
        time.sleep(0.01)  # Small delay to prevent CPU overload

if __name__ == "__main__":
    main()