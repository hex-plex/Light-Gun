# Light-Gun

## This is to create a light gun using Opencv and camera module
Bored in the quarantined period revisiting my old video games with light gun inspired an idea of light gun in LCD monitors , I went on building it mainly as a android package as it would be accessable to anyone. Then ended up using a Raspberry Pi as a standalone device to enable its use accross many platforms and devices.<br/>
**Raspi-c is the main working directory for now.**<br/><br/>
**The Explanation for the working can be found in EXPLANATION.md**

## Glimpse:
This is the glimpse of the prototype made with Raspberry pi and a toy gun with all the proccessing done on the Raspberry and only transmites messages to the local server. The previous method of running the proccessing and the actions is documented in **Win-Py** directory.<br/>

<img src="https://raw.githubusercontent.com/hex-plex/Light-Gun/master/images/Complete_setup.jpg" width="400" align="right" border="20"></img>
<br/><br/><br/><br/><br/><br/>This is an prototype of the light gun with a camera module attached to a toy-gun and with a Raspberry pi 3 b+ (unneccessary I know) and a 7.4 V li-ion battery with a buck converter to which two switches are connected on the interrupt pins.<hr/>

<br/><br/><br/><br/><br/><br/>
<img src="https://raw.githubusercontent.com/hex-plex/Light-Gun/master/images/display_setup.jpg" width="400" align="left"></img>
<br/><br/><br/><br/><br/><br/>
This is the setup with 4 IR-LEDs attached to the corners of the display which makes it very easy for detection in a wide range of lighting conditions.<hr/><br/><br/><br/><br/><br/>
<br/><br/><br/><br/><br/><br/>

And after Installation ( [Raspi](https://github.com/hex-plex/Light-Gun/tree/master/Raspi-c) version or [Local](https://github.com/hex-plex/Light-Gun/tree/master/Win-py) version) the guide lines for using the same is also available in there respective folders.

The Modules should then create a virtual mouse and start following the edge of your camera module.
The following is a demonstration of its working.... (:sweat_smile: in a while i am fixing the deviation erros.)
[**Demo Link**](https://drive.google.com/file/d/1hIYBv8l2JCylOfQS9Cc5D5Hp50Ui55D-/view?usp=sharing)

## Contribution
Any kind of Contribution is always welcomed. The rules for any Contribution for now is vague as I have not really structurized the project so well as mostly in its developmental period, So its prone to some nasty errors(Anyways feel free to report it :smile: ), Any Idea for a better implementation is also welcome.

## Reference:
- This is for getting R and t matrix  https://www.learnopencv.com/head-pose-estimation-using-opencv-and-dlib/
- This is for adjusting focal length (approximation) https://www.learnopencv.com/approximate-focal-length-for-webcams-and-cell-phone-cameras/
- The best solution is to create some software to make some kind of points on to the screen all along the run
- Basic structure completed with multithreading to split the work and decrease latency
