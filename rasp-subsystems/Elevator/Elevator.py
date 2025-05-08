import RPi.GPIO as GPIO
import time
from simple_pid import PID

class Elevator:
    def __init__(self):
        # Motor control pins
        self.IN1 = 38
        self.IN2 = 36
        self.PWM = 40

        # Encoder pins
        self.ENCODER_A = 13
        self.ENCODER_B = 15

        # Encoder state
        self.encoder_position = 0
        self.last_encoder_state = 0

        # PID controller
        self.pid = PID(Kp=1.0, Ki=0.0, Kd=0.0)
        self.pid.output_limits = (-100, 100)
        self.target_position = 0

        GPIO.setmode(GPIO.BOARD)
        GPIO.setwarnings(False)

        # Setup motor pins
        GPIO.setup(self.IN1, GPIO.OUT)
        GPIO.setup(self.IN2, GPIO.OUT)
        GPIO.setup(self.PWM, GPIO.OUT)

        # Setup encoder pins
        GPIO.setup(self.ENCODER_A, GPIO.IN, pull_up_down=GPIO.PUD_UP)
        GPIO.setup(self.ENCODER_B, GPIO.IN, pull_up_down=GPIO.PUD_UP)

        # Setup PWM
        self.pwm = GPIO.PWM(self.PWM, 1000)
        self.pwm.start(0)

        # Add encoder callback
        GPIO.add_event_detect(self.ENCODER_A, GPIO.BOTH, callback=self._encoder_callback)
        GPIO.add_event_detect(self.ENCODER_B, GPIO.BOTH, callback=self._encoder_callback)

    def _encoder_callback(self, channel):
        current_state = (GPIO.input(self.ENCODER_A) << 1) | GPIO.input(self.ENCODER_B)
        if current_state != self.last_encoder_state:
            if (self.last_encoder_state, current_state) in [(0, 1), (1, 3), (3, 2), (2, 0)]:
                self.encoder_position += 1
            else:
                self.encoder_position -= 1
            self.last_encoder_state = current_state

    def set_target_position(self, position):
        self.target_position = position
        self.pid.setpoint = position

    def update_position_control(self):
        control_output = self.pid(self.encoder_position)
        self.move(control_output)

    def get_position(self):
        return self.encoder_position

    def move(self, angularVelocity: float):
        control = abs(angularVelocity)
        control = max(0, min(control, 100))

        if control == 0:
            self.stop()
        else:
            if self.inverted:
                GPIO.output(self.IN1, GPIO.LOW if angularVelocity < 0 else GPIO.HIGH)
                GPIO.output(self.IN2, GPIO.HIGH if angularVelocity < 0 else GPIO.LOW)
            else:
                GPIO.output(self.IN1, GPIO.HIGH if angularVelocity < 0 else GPIO.LOW)
                GPIO.output(self.IN2, GPIO.LOW if angularVelocity < 0 else GPIO.HIGH)

            self.pwm.ChangeDutyCycle(control)

    def set_position(self, position: int):
        self.target_position = position
        self.pid.setpoint = position

    def stop(self):
        GPIO.output(self.IN1, GPIO.LOW)
        GPIO.output(self.IN2, GPIO.LOW)
        self.pwm.ChangeDutyCycle(0)

    def cleanup(self):
        self.stop()
        self.pwm.stop()
        GPIO.cleanup()

            