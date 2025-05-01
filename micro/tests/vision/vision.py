import numpy as np
import cv2

# turn on cam
webcam = cv2.VideoCapture(2) # Adjust based on camera to use

while (1):
    _, imageFrame = webcam.read()

    # Convert BGR to HSV colorspace
    hsvFrame = cv2.cvtColor(imageFrame, cv2.COLOR_BGR2HSV)

    # Define color ranges and masks
    # TODO: Update these values to match the colors of the spheres
    colors = {
        "Red": ([136, 87, 111], [180, 255, 255]),
        # "Green": ([35, 52, 72], [85, 255, 200]), # Ignoring green, for now
        "Blue": ([94, 80, 2], [120, 255, 255]),
        "Orange": ([5, 100, 100], [15, 255, 255]),
        "Yellow": ([20, 100, 100], [30, 255, 255]),
        "Black": ([0, 0, 0], [50, 50, 30])
    }

    kernal = np.ones((5, 5), "uint8")

    for color_name, (lower, upper) in colors.items():
        lower = np.array(lower, np.uint8)
        upper = np.array(upper, np.uint8)
        mask = cv2.inRange(hsvFrame, lower, upper)
        mask = cv2.dilate(mask, kernal)
        res = cv2.bitwise_and(imageFrame, imageFrame, mask=mask)

        # Creating contour to track color
        contours, hierarchy = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        for pic, contour in enumerate(contours):
            # Get area and convex hull of the contour
            area = cv2.contourArea(contour)
            hull = cv2.convexHull(contour)
            center = tuple(hull[0][0])
            minArea = 5000 # TODO: Test for this value
            if (area > minArea):
                color_bgr = {
                    "Red": (0, 0, 255), 
                    # "Green": (0, 255, 0), 
                    "Blue": (255, 0, 0),
                    "Orange": (0, 165, 255), 
                    "Yellow": (0, 255, 255), 
                    "Black": (0, 0, 0)
                }.get(color_name, (255, 255, 255))

                cv2.drawContours(imageFrame, [hull], 0, (0, 255, 0), 2)
                cv2.putText(imageFrame, f"{color_name} Colour", center, cv2.FONT_HERSHEY_SIMPLEX, 1.0, color_bgr)

    # final run
    cv2.imshow("Color Detection", imageFrame)
    if cv2.waitKey(10) & 0xFF == ord('q'):
        webcam.release()
        cv2.destroyAllWindows()
        break