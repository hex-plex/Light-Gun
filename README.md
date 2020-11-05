# Light-Gun

## This is to create a light gun using Opencv and camera module
Bored in the quarantined period revisiting my old video games with light gun inspired a idea of light gun in lcd monitors , I went on building it mainly as a android package as it would be accessable for any one. Then ended up using a Raspberry Pi as a standalone device to able to use it accross platforms and devices.<br/>
**Raspi-c is the main working directory for now.**<br/><br/>
**The Explanation for the working can be found in EXPLANATION.md**
## Contribution
Any kind of Contribution is always welcomed. The rules for any Contribution for now is vague as I have not really structurized the project so well as mostly its in the development period, So its prone to some nasty errors(Anyways feel free to report it :smile: ), Any Idea for a better implementation is also welcome.
## ToDo:
- Put a camera module in a toy gun to get the feed from there. (for now i used my phones camera module in demo)
- Devise a method to convert the HSV color space into a grayscale which measures how close is it to the color of the leds in ideal condition. This is very useful in adaptive thresholding.
- Work out the problems with **Hardware Interrupts** and make a communication protocol between the Pi and the Computer.
- ><del>Convert the code into java based android package for any one to use.</del><br/>
This is not the main motive now

## Glimpse:
This is the glimpse of the prototype made with Raspberry pi and a toy gun with all the proccessing done on the Raspberry and only transmites messages to the local server. The previous method of running the proccessing and the actions is documented in **Win-Py** directory.<br/>
This is the basic parts of the hardware prototype.
![Setup](https://raw.githubusercontent.com/hex-plex/Light-Gun/master/images/gun_setup.jpg)

## Reference:
- This is for getting R and t matrix  https://www.learnopencv.com/head-pose-estimation-using-opencv-and-dlib/
- This is for adjusting focal length (approximation) https://www.learnopencv.com/approximate-focal-length-for-webcams-and-cell-phone-cameras/
- The best solution is to create some software to make some kind of points on to the screen all along the run
- Basic structure completed with multithreading to split the work and decrease latency
