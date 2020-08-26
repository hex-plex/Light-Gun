## Light-Gun
This Folder contains the code for testing out the basic concepts of my project. It is been implemented in python. The code is not optimized and calibrated correctly and only works in a specific ligting condition. The code is been ported and revised to C++, which is done to help in a being computationally lighter for a single board computer.<br/>

## **The code may not work as expected hence I suggest using the Raspi-c folder.**

### Flaws
- The rotation matrix is not used instead rvec was used in code. Later changed it by using cv2.Rodrigues.
- The Point 2 Point mapping of the pointers and the display corners are not done. This is been updated in C++ side of the code taking a difference of the pointer vector and the pointer2corner vector.
- The Scale is not set. Updated in c++ code so that the display could be of any resolution and the code would  make actions based on it
- The Thresholding of coloured objects are challenging and light dependent. This replaced by IR Leds in the C++ code so as to make thresholding easier as they are sources of light themselves.
- Action Registration was done by listenning to all the key strokes on a seperate thread which is runs on the CPU all the time. Its been replaced with **Hardware Interrupt** to save a lot of CPU time.
- No Adaptive Thresholding , updated on the c++ side.
