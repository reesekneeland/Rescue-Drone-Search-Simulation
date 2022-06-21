#ifndef IMAGE_H_
#define IMAGE_H_
#include <iostream>
#include <string>
/**
 * @brief Image class that represents an image as an array of unsigned char* forces the image to have a
 * red, green, blue, and alpha value. 
 * 
 */
class Image{
    private:
        int width;//width of image
        int height;//hieght of image
        int components = 4;//number components of the image hard coded to 4 because we assume we have an alpha value.
        unsigned char* image = NULL;//unsigned char* that represents the image itself as a 2d array each element having a char array of size
        //4 for the red, green, blue, and alpha values.
        
    public:
        //constructors
        /**
         * @brief Construct a new Image object with image pointing to null
         * 
         */
        Image();
        /**
         * @brief Construct a new Image object by taking in an existing image in the file system.
         * 
         * @param filename name of the .png file we want to represent.
         */
        Image(const std::string& filename);
        /**
         * @brief Construct a new Image object based on an already existing instance of an image. Makes a copy of the image.
         * 
         * @param img the image we want to make a copy of
         */
        Image(const Image &img);
        /**
         * @brief allows us to set an image to an instance of another by overloading the assignment operator.
         * 
         * @param img the image we are setting our new image to.
         */
        void operator=(const Image& img);
        /**
         * @brief Construct a new blank Image based on the specified width and height.
         * 
         * @param width width of blank image
         * @param height height of blank image
         */
        Image(int width, int height);

        //destructor
        /**
         * @brief Destroy the Image object
         * 
         */
        ~Image();

        //getters
        /**
         * @brief Get the Height Image
         * 
         * @return int images's height
         */
        int GetHeight() const;
        /**
         * @brief Get the Width Image
         * 
         * @return int image's width
         */
        int GetWidth() const;
        /**
         * @brief Get the number of components in a single pixel of the image
         * 
         * @return int number of pixel components hard coded to 4
         */
        int GetComponentNum() const;

        /**
         * @brief Get the Luminance of a pixel
         * 
         * @param x finds the row the pixel is in
         * @param y indexes into row to get the actual pixel in the image
         * @return double luminance value of the current pixel
         */
        double GetLuminance(int x, int y) const;

        /**
         * @brief Get the Pixel of the image
         * 
         * @param x finds the row the pixel is in
         * @param y indexes into row to get the actual pixel in the image
         * @return unsigned char* represents the current pixel
         */
        unsigned char* GetPixel(int x, int y) const;
        /**
         * @brief Get the Overflow Pixel in the event x and y go out of bounds of the unsigned char* 
         * extends the edge pixels to handle out of bounds
         * 
         * @param x finds the row the pixel is in
         * @param y indexes into row to get the actual pixel in the image
         * @return unsigned* either the pixel we intended to get or an extended edge pixel if x and y exceeed image bounds.
         */
        unsigned char* GetOverflowPixel(int x, int y) const;
        /**
         * @brief Get the Pixel Float object
         * 
         * @param x finds the row the pixel is in
         * @param y indexes into row to get the actual pixel in the image
         * @return float 
         */
        float getPixelFloat(int x, int y) const;

        //setters
        /**
         * @brief Set the Pixel at the x and y values to the passed in pixel
         * 
         * @param x finds the row the pixel is in
         * @param y indexes into row to get the actual pixel in the image
         * @param pixel the new pixel we want to set the old pixel to
         */
        void SetPixel(int x, int y,unsigned char* pixel);


        /**
         * @brief converts unsigned char pixel to float pixel and sets it with an image
         * 
         * @param x width index for calculating postion in image
         * @param y same as x but for height
         * @param value value calculated to be in place of unsigned char
         */

        void setPixelFloat(int x, int y, float value);

        //other
        /**
         * @brief saves the image as .png under the new file name 
         * 
         * @param filename name of the new image it will be saved as
         */
        void SaveAs(const std::string& filename);

        unsigned char* GetImage();

};
#endif