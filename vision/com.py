import serial
import time

# Abrir puerto serial
ser = serial.Serial('/dev/ttyACM0', 9600)
time.sleep(2)  # Esperar a que la Teensy esté lista

# Definir velocidades para cada motor
# Motor1, Motor2, Motor3, Motor4
comando = "255,0,128,255\n"

# Enviar comando
ser.write(comando.encode())

ser.close()

