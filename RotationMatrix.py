import cv2
import numpy as np

def rotationMatrix(size,image_points):
    
    ## This should be obtained while configuring the gun They are mostly 2D plane
    model_points = np.loadtxt("modelPoints.xyz",delimiter=",")

    if len(model_points)!=4:
        print(model_points)
        raise Exception("Config the the model points")

    ## Approximations
    focal_length = size[1]
    center = (size[1]/2, size[0]/2)
    camera_matrix = np.array(
                         [[focal_length, 0, center[0]],
                         [0, focal_length, center[1]],
                         [0, 0, 1]], dtype = "double"
                         )
    image_points = np.array(image_points,dtype="double")
    #print(model_points)
    mod_=[]
    for i in range(len(model_points)):
        mod_.append((model_points[i][0],model_points[i][1],0)) ## this is as its a plane hence we can consider it to be on the focal length
        ## THis assumption would only give a wrong value of translational matrix
        ## Which is not important for us
    model_points = np.array(mod_,dtype="double")## This has to be mapped to 3d coordinates
    #print(model_points)
    dist_coeffs = np.zeros((4,1)) # Assuming no lens distortion
    (success, rotation_vector, translation_vector) = cv2.solvePnP(model_points, image_points, camera_matrix, dist_coeffs, flags=cv2.SOLVEPNP_ITERATIVE)

    return rotation_vector,translation_vector


if __name__=="__main__":
    exit()
