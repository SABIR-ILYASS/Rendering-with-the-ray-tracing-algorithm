/*
Author: SABIR ILYASS.
*/
#include "ImagePPM.h"

ImagePPM::ImagePPM(int width, int height, string path, int numberOfImage)
{
	this->width_ = width;
	this->height_ = height;
	this->size_ = 3 * width_ * height_;

	this->numberOfImage_ = numberOfImage;
	this->pathOutput_ = path + "image" + std::to_string(numberOfImage_) + ".ppm";


}

void ImagePPM::setNextPixel(int R, int G, int B)
{
	imageData_.push_back(R);
	imageData_.push_back(G);
	imageData_.push_back(B);
	this->pixel_++;
}


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