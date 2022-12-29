/*
Author: SABIR ILYASS.
*/

#ifndef IMAGEPPM_H
#define IMAGEPPM_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class ImagePPM
{
public:
	ImagePPM(int width, int height, string path, int numberOfImage);

	void setNextPixel(int ColorR, int colorG, int colorB);

	void setPixeltoImage();


private:
	int width_;
	int height_;
	int size_;
	vector<int> imageData_;
	string pathOutput_;
	int numberOfImage_;
	ofstream MyImage_;
	int pixel_ = 0;


};

#endif

