#include "web_app.h"
#include "filters/stb_image.h"
#include "filters/stb_image_write.h"
#include "filters/blob_detect.h"
#include "filters/color_threshold.h"
#include "filters/canny_on_blob.h"
#include "detect_location.h"
#include <fstream>
#include <iostream>
#include "util/base64.h"
#include "camera_controller.h"


class Camera : public ICameraObserver {
public:
    // Structure the result however you like
    struct CameraResult : public ICameraResult {
        bool found;
        double pos[3];
    };

    // Constructor
    Camera(int cameraId, ICameraController* controller) : id(cameraId), controller(controller) {
        controller->AddObserver(*this);
    }

    // Takes a picture using the specified camera id
    void TakePicture() {
        controller->TakePicture(id);
    }

    // Processes images asynchonously.  The returned camera result will be passed into the ImageProcessingComplete(...) method
    ICameraResult* ProcessImages(int cameraId, double xPos, double yPos, double zPos, const std::vector<RawCameraImage>& images, picojson::object& details) const {
        if (cameraId == id || cameraId < 0) {
            // These will output the image to files.  Ultimately this is just for debugging:
            std::ofstream colorFile ("color.png", std::ios::out | std::ios::binary);
            colorFile.write (reinterpret_cast<const char*>(images[0].data), images[0].length);
            std::ofstream depthFile ("depth.png", std::ios::out | std::ios::binary);
            depthFile.write (reinterpret_cast<const char*>(images[1].data), images[1].length);
            
            //Color image loaded into image class
            Image* colorImage = new Image("color.png");
            //Depth image loaded into image class
            Image* depthImage = new Image("depth.png");

            ColorThreshold* blobImg = new ColorThreshold();
            CannyOnBlob* cannyblob = new CannyOnBlob();

            BlobDetect* blob = new BlobDetect();
            DetectLocation* detect = new DetectLocation();

            //original image
            Image emp;
            std::vector<Image*>original;
            original.push_back(colorImage);
            //blob image
            std::vector<Image*> color; 
            color.push_back(&emp);
            //canny image 
            std::vector<Image*> canny; 
            canny.push_back(&emp);
            //applying canny and color threshold into the original image
            blobImg->Apply(original,color);
            int blobCount =blob->PixelCount(color[0]);
            //original.clear();
            //original.push_back(color[0]);
            cannyblob->Apply(color,canny);
            int edgeCount =blob ->PixelCount(canny[0]);

            //bool of robot presence in image
            bool robFound =false;

            robFound = blob->objPresent(edgeCount,blobCount);
            //PixelPosition or the robot position
            double pixelPosition[3];
            if(robFound){
                //find the xy coordinates of the pixel of robot
                detect->FindxyPxl(color[0]);
                //getting the pixel of robot from depth image
                unsigned char* pxl = depthImage->GetPixel((detect->xyPxl)[0],(detect->xyPxl)[1]);
                //calculating needed variables for the calculation of pixel location
                detect->DirCalc(pxl);
                //direction vector 
                double Dir[3] = {detect->Direction[0],detect->Direction[1],detect->Direction[2]};
                //Distance*Direction
                for (int i=0 ; i<3;i++){
                    Dir[i] *= (detect->Distance);
                }
                //Pixel
                pixelPosition[0]=xPos+Dir[0];
                pixelPosition[1]=yPos+Dir[1];
                pixelPosition[1]=zPos+Dir[2];
            

            // Generate the result of image processing.  This could include images using the Result class.
                CameraResult* result = new CameraResult();
                result->found = true;
                result->pos[0] = trunc(pixelPosition[0]);
                result->pos[1] = trunc(pixelPosition[2]);
                result->pos[2] = trunc(pixelPosition[1]);
                return result;
            }else{
                CameraResult* result = new CameraResult();
                result->found = false;
                result->pos[0] = xPos;
                result->pos[1] = yPos;
                result->pos[2] = zPos;
                return result;
            }
            delete colorImage;
            delete depthImage;
            delete blobImg;
            delete detect;
            delete cannyblob;
            delete blob;
        }
        else {
            return NULL;
        }
    }

    // After the asynchronous image processing, this method will be synchronized with the update loop.
    void ImageProcessingComplete(ICameraResult* result) {
        CameraResult& res = *static_cast<CameraResult*>(result);
        if (res.found) {
            std::cout << "The robot was found here: " << res.pos[0] << ", " << res.pos[1] << ", " << res.pos[2] << std::endl;
        }
        delete result;
    }

private:
    ICameraController* controller;
    int id;
};