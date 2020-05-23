import cv2
import numpy as np

def rotationMatrix(img,image_points):
    size = img.shape
    """
    image_points = np.array([
                            (650,430),     # Nose tip
                            (657,565),     # Chin
                            (575,400),     # Left eye left corner
                            (725,395),     # Right eye right corne
                            (620,495),     # Left Mouth corner
                            (690,495)      # Right mouth corner
                        ], dtype="double")
    ## this is to be given as a input of the image taken by camera
    ## this function should convert it 
        """

    ## This should be obtained while configuring the gun They are mostly 2D plane
    model_points = np.array([
                            (0.0, 0.0, 0.0),             # Nose tip
                            (0.0, -330.0, -65.0),        # Chin
                            (-225.0, 170.0, -135.0),     # Left eye left corner
                            (225.0, 170.0, -135.0),      # Right eye right corne
                            (-150.0, -150.0, -125.0),    # Left Mouth corner
                            (150.0, -150.0, -125.0)      # Right mouth corner
                        
                        ])



    ## Approximations
    focal_length = size[1]
    center = (size[1]/2, size[0]/2)
    camera_matrix = np.array(
                         [[focal_length, 0, center[0]],
                         [0, focal_length, center[1]],
                         [0, 0, 1]], dtype = "double"
                         )

    dist_coeffs = np.zeros((4,1)) # Assuming no lens distortion
    (success, rotation_vector, translation_vector) = cv2.solvePnP(model_points, image_points, camera_matrix, dist_coeffs, flags=cv2.SOLVEPNP_ITERATIVE)

    return rotation_vector,translation_vector


if __name__=="__main__":
    exit()
