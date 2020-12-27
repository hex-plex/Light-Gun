# Light-Gun

## This is to create a light gun using Opencv and camera module
Bored in the quarantine period, revisiting my old video games with light gun inspired an idea of light gun with a LCD display , I went on to build it mainly as a android package as it would be more accessable to anyone. Then ended up using a Raspberry Pi as a standalone device to enable it's use accross many platforms and devices.<br/>
**Raspi-c is the main working directory for now.**<br/><br/>
**The Explanation for the working can be found in EXPLANATION.md**

## Glimpse:
This is the glimpse of the prototype made with Raspberry pi on a toy gun with all the number-munching done on the Raspberry and transmites messages to the local server through bluetooth. The previous method of running the proccessing and the actions is documented in **Win-Py** directory.<br/>

<img src="https://raw.githubusercontent.com/hex-plex/Light-Gun/master/images/Complete_setup.jpg" width="400" align="right" border="20"></img>
<br/><br/><br/><br/><br/><br/>This is a prototype of the light gun with a camera module attached onto a toy-gun and with a Raspberry pi 3 b+ (unneccessary I know) and a 7.4 V li-ion battery, regulated with a buck converter to which two switches are connected on the Raspi's interrupt pins.<hr/>

<br/><br/><br/><br/><br/><br/>
<img src="https://raw.githubusercontent.com/hex-plex/Light-Gun/master/images/display_setup.jpg" width="400" align="left"></img>
<br/><br/><br/><br/><br/><br/>
This is the display setup with 4 IR-LEDs attached to the corners of the display which makes it very easy for detection in a wide range of lighting conditions.<hr/><br/><br/><br/><br/><br/>
<br/><br/><br/><br/><br/><br/>

And after Installation the main code using [Raspi](https://github.com/hex-plex/Light-Gun/tree/master/Raspi-c) version or [Local](https://github.com/hex-plex/Light-Gun/tree/master/Win-py) version, continue using it according to the guide lines for the same which is present in their respective folders itself.

The Modules then should create a virtual mouse and start following the edge vector of the camera module.
The following is a demonstration of it in action.... (:sweat_smile: coming up shortly, as I am fixing few deviation errors.)

[**Demo Link**](https://drive.google.com/file/d/1hIYBv8l2JCylOfQS9Cc5D5Hp50Ui55D-/view?usp=sharing)

## Contribution
Any kind of Contribution is always welcomed. The rules for any Contribution for now is Non existent as I am the only one working on it and I have not really structurized the project so well as mostly in its prototyping stage, So its not possible to do a lot(Anyways feel free to report any errors or bugs :smile: ), Any Idea for a better implementation is also welcomed.

## Reference:
- This is for getting R and t matrix  [[link]](https://www.learnopencv.com/head-pose-estimation-using-opencv-and-dlib/)
- This is for adjusting focal length (approximation) [[link]](https://www.learnopencv.com/approximate-focal-length-for-webcams-and-cell-phone-cameras/)
- This is for getting accurate intrensic matrix [[link]](https://www.learnopencv.com/camera-calibration-using-opencv/)
- Cmake
- Bluez
- Raspberry pi interupts
- Asynchronous coding