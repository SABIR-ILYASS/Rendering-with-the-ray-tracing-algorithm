/*
code file created by ilyass SABIR
*/

#include "ImagePPM.h"
 

ImagePPM::ImagePPM(int width, int height, string path, int numberOfImage)
{
	// get the width and height of the image
	this->width_ = width;
	this->height_ = height;
	// get the width and height of the image
	this->size_ = 3 * width_ * height_;

	//get the number of data in the image, we multiply by 3 because each pixel has 3 values.
	this->numberOfImage_ = numberOfImage;
	// path for save the .ppm image
	this->pathOutput_ = path + "image" + std::to_string(numberOfImage_) + ".ppm";
}

// set the pixel values of the .ppm image
void ImagePPM::setNextPixel(int R, int G, int B)
{
	imageData_.push_back(R);
	imageData_.push_back(G);
	imageData_.push_back(B);
	this->pixel_++;
}

// set all pixel values of the .ppm image
void ImagePPM::setPixeltoImage()
{

	ofstream MyImage_(pathOutput_);


	MyImage_ << "P3" << std::endl;
	MyImage_ << width_ << " " << height_ << endl;
	MyImage_ << "255" << endl;

	int count = 0;
	for (int p : this->imageData_)
	{
		if (count == 3) {
			MyImage_ << endl;
			count = 0;
		}
		MyImage_ << p << " ";
		count++;

	}

	MyImage_.close();

}