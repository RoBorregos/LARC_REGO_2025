import gpiod
import time

class LineSensor:
    def __init__(self, left_pin, right_pin, chip="gpiochip4"):
        self.chip = gpiod.Chip(chip)
        self.left_line = self.chip.get_line(left_pin)
        self.right_line = self.chip.get_line(right_pin)
        self.left_line.request(consumer="LineSensor", type=gpiod.LINE_REQ_DIR_IN)
        self.right_line.request(consumer="LineSensor", type=gpiod.LINE_REQ_DIR_IN)

    def left_detected(self):
        return self.left_line.get_value() == 1

    def right_detected(self):
        return self.right_line.get_value() == 1