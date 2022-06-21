#include "double_threshold.h"

/*int main(){
	//create filters
	DoubleThresholdFilter d = DoubleThresholdFilter();
	DoubleThresholdFilter d2 = DoubleThresholdFilter(0.2, 0.4);

	//load up example of a non-max suppressed image
	//and prep inputs & outputs
    Image input("data/statue_suppressed.png");
    Image output = Image(input.GetWidth(), input.GetHeight());
    std::vector<Image*> inputs;
    std::vector<Image*> outputs;
    inputs.push_back(&input);
    outputs.push_back(&output);

    //apply filters and save
    d.Apply(inputs, outputs);

    output.SaveAs("data/statue_double_thresholded.png");

    d2.Apply(inputs, outputs);

    output.SaveAs("data/statue_double_thresholded_2.png");

    return 0;
}*/

//constructors
DoubleThresholdFilter::DoubleThresholdFilter(){
	this->lowRatio = 0.15;
	this->highRatio = 0.3;
}

DoubleThresholdFilter::DoubleThresholdFilter(float lowRatio, float highRatio){
	this->lowRatio = lowRatio;
	this->highRatio = highRatio;
}

//getters
float DoubleThresholdFilter::GetHighRatio() const{
	return this->highRatio;
}

float DoubleThresholdFilter::GetLowRatio() const{
	return this->lowRatio;
}

//apply
//function is based off the explanation of the double threshold filter by
//Sofiane Sahir at https://towardsdatascience.com/canny-edge-detection-step-by-step-in-python-computer-vision-b49c3a2d8123
void DoubleThresholdFilter::Apply(std::vector<Image*> original, std::vector<Image*> filtered){


	//set up threshold values
	//and strong & weak values
	unsigned char maxValue = this->GetMaxRed(original[0]);
	unsigned char highThresh = 1 * (maxValue * this->GetHighRatio());
	unsigned char lowThresh = 1 * (highThresh * this->GetLowRatio());
	const unsigned char STRONG = 255;
	const unsigned char WEAK = 25;

	//std::cout << "maxValue: " << 1 * maxValue << "\nhighThresh: " << 1 * highThresh << 
	//			"\nlowThresh: " << 1 * lowThresh << std::endl;

	//loop through filtered pixels
	for(int x = 0; x < filtered[0]->GetWidth(); x ++){
		for(int y = 0; y < filtered[0]->GetHeight(); y ++){
			//do stuff.
			unsigned char filtPixel[4];
			unsigned char rgbValue;

			//get pixel from original image
			unsigned char* origPixel = original[0]->GetPixel(x, y);
			//set alpha to be the same
			filtPixel[3] = origPixel[3];

			//threshold based on red channel
			if(origPixel[0] >= highThresh){
				rgbValue = STRONG;
			}
			else if(origPixel[0] >= lowThresh){
				rgbValue = WEAK;
			}
			else{
				rgbValue = 0;
			}

			//fill in values for filtPixel
			for(int i = 0; i < 3; i ++){
				filtPixel[i] = rgbValue;
			}

			//add filtPixel to the filtered image
			filtered[0]->SetPixel(x, y, filtPixel);
		}
	} //end y for loop

}

unsigned char DoubleThresholdFilter::GetMaxRed(Image* image) const{
	//get maximum red value
	//assumes image is grayscale, so using red only is fine

	unsigned char currMax = 0;
	unsigned char currVal = 0;
	//go through all pixels in the image
	for(int y = 0; y < image->GetHeight(); y ++){
		for(int x = 0; x < image->GetWidth(); x ++){
			//get pixel and compare to current max
			currVal = image->GetPixel(x, y)[0];

			if(currVal > currMax){
				currMax = currVal;
			}
		}
	} //end y loop

	return currMax;
}