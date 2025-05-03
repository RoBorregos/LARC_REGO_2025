import serial
import time

ser = serial.Serial('/dev/ttyACM0', 9600)
time.sleep(2)  # Espera a que la Teensy inicie

contador = 1
while True:
    mensaje = f"Hola Teensy #{contador}\n"
    ser.write(mensaje.encode('utf-8'))
    print("Enviado:", mensaje.strip())
    contador += 1
    time.sleep(2)
