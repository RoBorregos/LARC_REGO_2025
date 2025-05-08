import RPi.GPIO as GPIO
import time

class LineSensor:
    def __init__(self, left_pin, right_pin):
        self.left_pin = left_pin
        self.right_pin = right_pin

        # Usamos el modo BCM (por número de GPIO)
        GPIO.setmode(GPIO.BCM)

        # Desactiva advertencias por reutilización de pines
        GPIO.setwarnings(False)

        # Configura los pines como entradas
        GPIO.setup(self.left_pin, GPIO.IN)
        GPIO.setup(self.right_pin, GPIO.IN)

    def left_detected(self):
        value = GPIO.input(self.left_pin)
        #print("Left detected =", value)
        return value == GPIO.HIGH

    def right_detected(self):
        value = GPIO.input(self.right_pin)
        #print("Right detected =", value)
        return value == GPIO.HIGH
