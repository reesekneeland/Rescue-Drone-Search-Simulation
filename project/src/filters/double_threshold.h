#ifndef DOUBLE_THRESHOLD_HEADER
#define DOUBLE_THRESHOLD_HEADER

#include "filter.h"

/** @class DoubleThresholdFilter
 * @brief Performs the double threshold filter
 * 
 * Initialized with ratios that determine the thresholds for strong and weak
 * pixels; the default ratios set the low threshold to 0.15 of the high 
 * threshold, and the high threshold to 0.3 of the brightest pixel in the image.
 * Function is based off the explanation of the double threshold filter by
 * Sofiane Sahir at https://towardsdatascience.com/canny-edge-detection-step-by-step-in-python-computer-vision-b49c3a2d8123
 */
class DoubleThresholdFilter : public Filter {
public:
	//constructors
	/** @brief Default constructor; uses low ratio 0.15 and high ratio 0.3 */
	DoubleThresholdFilter();
	/** @brief Constuctor with custom low and high ratios. */
	DoubleThresholdFilter(float lowRatio, float highRatio);

	//getters
	/** @brief Gets the ratio used to calculate the low threshold.
	 * @return low ratio
	 */
	float GetLowRatio() const;
	/** @brief Gets the ratio used to calculate the high threshold
	 * @return high ratio
	 */
	float GetHighRatio() const;

	/** @brief Performs double threshold on an image.
	 * @param original: a vector of input images
	 * @param filtered: a vector of output images
	 */
	void Apply(std::vector<Image*> original, std::vector<Image*> filtered) override;

protected:
	float lowRatio;
	float highRatio;

	/** @brief Gets maximum red value in an image
	 * @return maximum value in the red channel of the image
	 */
	unsigned char GetMaxRed(Image* image) const;

};

#endif