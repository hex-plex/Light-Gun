# Light-Gun

## This is to create a light gun using Opencv and camera module
Bored in the quarantined period revisiting my old video games with light gun inspired an idea of light gun in LCD monitors , I went on building it mainly as a android package as it would be accessable to anyone. Then ended up using a Raspberry Pi as a standalone device to enable its use accross many platforms and devices.<br/>
**Raspi-c is the main working directory for now.**<br/><br/>
**The Explanation for the working can be found in EXPLANATION.md**

## Contribution
Any kind of Contribution is always welcomed. The rules for any Contribution for now is vague as I have not really structurized the project so well as mostly in its developmental period, So its prone to some nasty errors(Anyways feel free to report it :smile: ), Any Idea for a better implementation is also welcome.

## Glimpse:
This is the glimpse of the prototype made with Raspberry pi and a toy gun with all the proccessing done on the Raspberry and only transmites messages to the local server. The previous method of running the proccessing and the actions is documented in **Win-Py** directory.<br/>
This is the basic parts of the hardware prototype.
![Hardware-Setup](https://raw.githubusercontent.com/hex-plex/Light-Gun/master/images/Complete_setup.jpg)

This is the setup with IR-LEDs attached to the 4 ends which makes it very easy for detection in a wide range of lighting conditions.
![Display-Setup](https://raw.githubusercontent.com/hex-plex/Light-Gun/master/images/display_setup.jpg)

And after Installation ( [Raspi](https://github.com/hex-plex/Light-Gun/tree/master/Raspi-c) version or [Local](https://github.com/hex-plex/Light-Gun/tree/master/Win-py) version) the guide lines for using the same is also available in there respective folders.

The Modules should then create a virtual mouse and start following the edge of your camera module.
The following is a demonstration of its working.... (:sweat_smile: in a while i am fixing the deviation erros.)

## Reference:
- This is for getting R and t matrix  https://www.learnopencv.com/head-pose-estimation-using-opencv-and-dlib/
- This is for adjusting focal length (approximation) https://www.learnopencv.com/approximate-focal-length-for-webcams-and-cell-phone-cameras/
- The best solution is to create some software to make some kind of points on to the screen all along the run
- Basic structure completed with multithreading to split the work and decrease latency
