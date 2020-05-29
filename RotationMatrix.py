import cv2
import numpy as np

def rotationMatrix(size,image_points):
    
    ## This should be obtained while configuring the gun They are mostly 2D plane
    model_points = np.loadtxt("modelPoints.xyz",delimiter=",")
    if len(model_points)!=4:
        raise NoConfigError("Config the the model points")

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
