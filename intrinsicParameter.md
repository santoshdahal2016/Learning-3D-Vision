# Intrinsic Parameter


Intrinsic Parameter indicate the property of camera itself .

<img src="images/IntrinsicParameter.png">

The previous perspective projection equation : 

<img src="images/PrespectiveProjectionEqun.png"/>


The ~ above the image co-ordinate depicts this does not completely describe Pinhole Camera Model
 and there are other camera parameter need to be considered :
 
 1. Transformation between Optical Center and Camera Center 
 2. Changing the unit ( meter to pixel )

### Transformation between Optical Center and Camera Center 


<img src="images/cameraCenter.png">

X0 and Y0 are the camera center.

### Changing the unit ( meter to pixel )

<img src="images/scalinrIntrinsic.png">

dx and dy denote the pixel height and width

## Camera Calibration

1. Self Calibration

Self-calibration refers to the process of calculating all the intrinsic parameters of the camera using only the information
available in the images taken by that camera.   

2. Calibration