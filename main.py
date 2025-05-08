import sys
import time
import serial

# Obtener la ruta base del proyecto
BASE_DIR = os.path.dirname(os.path.abspath(__file__))

# Agregar paths a sys.path para importar módulos desde subdirectorios
sys.path.append(os.path.join(BASE_DIR, "rasp-subsystems"))
sys.path.append(os.path.join(BASE_DIR, "rasp-subsystems", "Elevator"))
sys.path.append(os.path.join(BASE_DIR, "vision", "src", "LARC"))

from LineSensor import LineSensor
from Elevator import Elevator
from CameraUpper import CameraUpper
from CameraLower import CameraLower

def main():
    # Inicialización de sensores y cámaras
    line_sensor = LineSensor(left_pin=4, right_pin=25)
    elevator = Elevator()
    cam_up_ = CameraUpper(port='/dev/ttyACM0', camera_index=0)
    cam_low_ = CameraLower(port='/dev/ttyACM0', camera_index=1)

    port = "/dev/ttyACM0"
    baudrate = 9600
    timeout = 1

    try:
        serial_conn = serial.Serial(port, baudrate=baudrate, timeout=timeout)
        print(f"[SERIAL] Connected to {port} at {baudrate} baud.")
    except serial.SerialException as e:
        print(f"[ERROR] Serial connection failed: {e}")
        serial_conn = None

    last_camera_time = time.time()

    while True:
        # Manejo de comandos seriales
        if serial_conn and serial_conn.is_open:
            if serial_conn.in_waiting:
                command = serial_conn.readline().decode().strip()
                
                if command.startswith("SET_TARGET:"):
                    try:
                        position = int(command.split(":")[1])
                        elevator.set_target_position(position)
                        serial_conn.write(b"OK\n")
                    except:
                        serial_conn.write(b"ERROR\n")
                
                elif command.startswith("SET_POSITION:"):
                    try:
                        position = int(command.split(":")[1])
                        elevator.encoder_position = position
                        elevator.set_target_position(position)
                        serial_conn.write(b"OK\n")
                    except:
                        serial_conn.write(b"ERROR\n")
                
                elif command == "GET_POS":
                    pos = elevator.get_position()
                    serial_conn.write(f"{pos}\n".encode())

        # Control del elevador
        elevator.update_position_control()

        # Lectura de sensores de línea
        msg = ""
        msg += "Right: YES\n" if line_sensor.left_detected else "Right: NO\n"
        msg += "Left: YES\n" if line_sensor.right_detected else "Left: NO\n"

        if serial_conn and serial_conn.is_open:
            serial_conn.write(msg.encode())

        # Ejecución de cámaras cada 1 segundo
        current_time = time.time()
        if current_time - last_camera_time >= 1.0:
            cam_up_.run()
            cam_low_.run()
            cam_low_.receive_state()
            last_camera_time = current_time

        time.sleep(0.01)  # Pausa pequeña

if __name__ == "__main__":
    main()
