#Light-Gun.apk 
##This is to create a light gun using Opencv and camera module of a android mobile
Bored in the quarantined period seeing my old video game with light gun inspired a idea of light gun in lcd monitors , I went on building it mainly as a android package as it would be accessable for any one.
>For now I have implemented on python using my phones camera module 
##ToDo:
- Scale the input screen coordinates with respect to the actual coordinates
- Utilize the precCoor to project or clip in the actual plane rather than 
- Use the **relative thresholding** to make a better estimate of the detection contours(This is consider something white on the screen and then threshold the color on basis of **Color-White** rather than the **Color** itself as then it would clear up most of the change in lighting scenario)
- Use the ir leds to be sure to not be thresholding any other contour
- Trying to port this on python for prototyping it well on raspberry pi and then start working on mobile as its not very hand on mobile but a good encloser and trigger should work well with the android app
- Convert the code into java based android package for any one to use.
##Reference: 
- This is for getting R and t matrix  https://www.learnopencv.com/head-pose-estimation-using-opencv-and-dlib/
- This is for adjusting focal length (approximation) https://www.learnopencv.com/approximate-focal-length-for-webcams-and-cell-phone-cameras/
- The best solution is to create some software to make some kind of points on to the screen all along the run 
- Basic structure completed with multithreading to split the work and decrease latency

  
