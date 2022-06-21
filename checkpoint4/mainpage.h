/*! \mainpage Runtime Terror's Search and Rescue Drone
 *
 * \section intro_sec Introduction
 *
 * Welcome to Runtime Terror's Search and Rescue Drone Documentation.
 * 
 * This project incorporates image filtering and detection in order to find a target and "rescue" them.
 * 
 * In order to build the project, run `make`. To run the project, run `./image_processor <original_image> <filter to apply> <filtered_image>'
 * 
 * The main classes used are Image and Filter. The Image class loops through the image and makes each pixel an unsigned char array so pixels can be changed accordingly. There are also functions to save the imag, get an image's height, width, component number, and luminance. One can also retrieve and set individual pixels.
 * The Filter class in comparison is simple -- it allows implementation of filters on images.
 * 
 * To create a new filter, create a header file that includes "filter.h" and "image.h", and have the class inherit from `public Filter`.
 *
 */
