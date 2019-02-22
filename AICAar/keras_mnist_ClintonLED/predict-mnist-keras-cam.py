#!/usr/bin/env python3
from keras import layers
from keras import models
from keras.models import load_model
from keras.utils import to_categorical
from keras import backend as K
from gpiozero import LED
from time import sleep
led1 = LED(4)
led2 = LED(17)
led4 = LED(27)
led8 = LED(22)
import numpy as np
import cv2

from ImageProcessor import ImageProcessor

# name of the opencv window
cv_window_name = "MNIST Camera"
CAMERA_INDEX = 0
REQUEST_CAMERA_WIDTH = 640
REQUEST_CAMERA_HEIGHT = 480

def ClintonLED(pre_no):
    if (pre_no == 0):
        led1.off()
        led2.off()
        led4.off()
        led8.off()
        print('i am',pre_no)
    elif (pre_no == 1):
        led1.on()
        led2.off()
        led4.off()
        led8.off()
        print('i am',pre_no)
    elif (pre_no == 2):
        led1.off()
        led2.on()
        led4.off()
        led8.off()
    elif (pre_no == 3):
        led1.on()
        led2.on()
        led4.off()
        led8.off()
        print('i am',pre_no)
    elif (pre_no == 4):
        led1.off()
        led2.off()
        led4.on()
        led8.off()
        print('i am',pre_no)
    elif (pre_no == 5):
        led1.on()
        led2.off()
        led4.on()
        led8.off()
        print('i am',pre_no)
    elif (pre_no == 6):
        led1.off()
        led2.on()
        led4.on()
        led8.off()
        print('i am',pre_no)
    elif (pre_no == 7):
        led1.on()
        led2.on()
        led4.on()
        led8.off()
        print('i am',pre_no)
    elif (pre_no == 8):
        led1.off()
        led2.off()
        led4.off()
        led8.on() 
        print('i am',pre_no)
    elif (pre_no == 9):
        led1.on()
        led2.off()
        led4.off()
        led8.on() 
        print('i am',pre_no)
        
# handles key presses
# raw_key is the return value from cv2.waitkey
# returns False if program should end, or True if should continue
def handle_keys(raw_key):
    global processor
    ascii_code = raw_key & 0xFF
    if ((ascii_code == ord('q')) or (ascii_code == ord('Q'))):
        return False
    elif (ascii_code == ord('w')):
        processor.p1 +=10
        print('processor.p1:' + str(processor.p1))
    elif (ascii_code == ord('s')):
        processor.p1 -=10
        print('processor.p1:' + str(processor.p1))
    elif (ascii_code == ord('a')):
        processor.p2 +=10
        print('processor.p2:' + str(processor.p2))
    elif (ascii_code == ord('d')):
        processor.p2 -=10
        print('processor.p1:' + str(processor.p2))
    return True
# Test image
processor = ImageProcessor()
# input_image = cv2.imread(test_image)
# cropped_input = processor.preprocess_image(input_image)

model = load_model('model.h5')
# 
cv2.namedWindow(cv_window_name)
cv2.moveWindow(cv_window_name, 10,  10)

cap = cv2.VideoCapture(CAMERA_INDEX)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, REQUEST_CAMERA_WIDTH)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, REQUEST_CAMERA_HEIGHT)

actual_frame_width = cap.get(cv2.CAP_PROP_FRAME_WIDTH)
actual_frame_height = cap.get(cv2.CAP_PROP_FRAME_HEIGHT)
print ('actual video resolution: ' + str(actual_frame_width) + ' x ' + str(actual_frame_height))

if ((cap == None) or (not cap.isOpened())):
    print ('Could not open camera.  Make sure it is plugged in.')
    # print ('file name:' + input_video_file)
    print ('Also, if you installed python opencv via pip or pip3 you')
    print ('need to uninstall it and install from source with -D WITH_V4L=ON')
    print ('Use the provided script: install-opencv-from_source.sh')
    exit_app = True
    exit()
exit_app = False
while(True):
    led1.on()
    led2.on()
    led4.on()
    led8.on()  
    ret, input_image = cap.read()

    if (not ret):
        print("No image from from video device, exiting")
        break

    # check if the window is visible, this means the user hasn't closed
    # the window via the X button
    prop_val = cv2.getWindowProperty(cv_window_name, cv2.WND_PROP_ASPECT_RATIO)
    if (prop_val < 0.0):
        exit_app = True
        break
    cropped_input, cropped = processor.preprocess_image(input_image)
    output = model.predict(cropped_input.reshape(1, 28, 28, 1))[0]
    predict_label = output.argmax()
    pre_no = output.argmax()
    percentage = int(output[predict_label] * 100)
    label_text = str(predict_label) + " (" + str(percentage) + "%)"
    print('Predicted:',label_text)
    processor.postprocess_image(input_image, percentage, label_text)
    cv2.imshow(cv_window_name, input_image)
    if (percentage >=95):
        ClintonLED(pre_no)
        sleep(1)
    elif (percentage <95):
        led1.on()
        led2.on()
        led4.on()
        led8.on()  
    raw_key = cv2.waitKey(1)
    if (raw_key != -1):
        if (handle_keys(raw_key) == False):
            exit_app = True
            break
cap.release()
