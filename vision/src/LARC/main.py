from CameraLower import CameraLower
from CameraUpper import CameraUpper
import time
import serial

cam_up_ = CameraUpper(port='/dev/ttyACM0', camera_index=0)
cam_low_ = CameraLower(port='/dev/ttyACM0', camera_index=1)

def main():
    while True:
        cam_up_.run()

        cam_low_.run()
        cam_low_.receive_state()
        time.sleep(1)

if __name__ == "__main__":
    main()