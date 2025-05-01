import numpy as np
import cv2

# Constants and other variables
colors = {
    "Red": ([0, 129, 40], [17, 255, 255]),
    "Blue": ([99, 114, 141], [112, 255, 249]),
    "Orange": ([2, 142, 200], [19, 250, 255]),
    "Yellow": ([23, 76, 123], [33, 216, 197]),
    "Black": ([107, 11, 30], [180, 54, 174]),
}

color_bgr_values = {
    "Red": (0, 0, 255),
    "Blue": (255, 0, 0),
    "Orange": (0, 165, 255),
    "Yellow": (0, 255, 255),
    "Black": (0, 0, 0)
}

global center_frame

def getFrameInfo():
    webcam = cv2.VideoCapture(0)

    if not webcam.isOpened():
        print("❌ Could not open webcam.")
        exit()

    # Main loop
    while True:
        ret, imageFrame = webcam.read()

        if not ret:
            print("❌ Failed to read from webcam.")
            break
            
        height, width, _ = imageFrame.shape
        center_frame = (width // 2, height // 2)  # Centro del frame

        hsvFrame = cv2.cvtColor(imageFrame, cv2.COLOR_BGR2HSV)

        kernal = np.ones((5, 5), "uint8")
        largest_contour = None
        object_center = None
        largest_area = 0

        for color_name, (lower, upper) in colors.items():
            lower = np.array(lower, np.uint8)
            upper = np.array(upper, np.uint8)
            mask = cv2.inRange(hsvFrame, lower, upper)
            mask = cv2.dilate(mask, kernal)

            contours, _ = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
            if contours:
                max_contour = max(contours, key=cv2.contourArea)
                area = cv2.contourArea(max_contour)
                if area > 750 and area > largest_area:
                    largest_area = area
                    largest_contour = max_contour
                    largest_color = color_name

        if largest_contour is not None:
            return (largest_contour, largest_color, largest_area)

# Detect a color and return its name
def getColor():
    return getFrameInfo()[1]

# Detect a color and return the horizontal offset from the center of the frame
def getCenterOffsetX():
    largest_contour = getFrameInfo()[0]
    hull = cv2.convexHull(largest_contour)

    M = cv2.moments(hull)
    if M["m00"] != 0:
        object_center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))
    else:
        object_center = (0, 0)
    
    # Calculamos la diferencia horizontal con respecto al centro del frame
    horizontal_offset = object_center[0] - center_frame[0]

    # Retornar offset
    return horizontal_offset

# Detect a color and return the vertical offset from the center of the frame
def getCenterOffsetY():
    largest_contour = getFrameInfo()[0]
    hull = cv2.convexHull(largest_contour)

    M = cv2.moments(hull)
    object_center = None
    if M["m00"] != 0:
        object_center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))
    else:
        object_center = (0, 0)
    
    # Calculamos la diferencia horizontal con respecto al centro del frame
    vertical_offset = object_center[0] - center_frame[1]

    # Retornar offset
    return vertical_offset

# Detect the largest object in the frame and return its area
def getObjectArea():
    return getFrameInfo()[2]