/*
code file created by ilyass SABIR
*/

#include "Texture.h"

#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include<tuple>

using namespace std;


Texture::Texture(string path)
{
	ifstream myfile;
	myfile.open(path, ios::in);

	string content;
	int count = 0;
	myfile >> content;

	myfile >> content;
	width_ = std::stoi(content);

	myfile >> content;
	height_ = std::stoi(content);

	myfile >> content;

	for (int i = 0; i < height_; i++)
	{
		vector<tuple<double, double, double>> matrixi;
		for (int j = 0; j < 3 * width_; j++)
		{
			double pixR, pixG, pixB;

			myfile >> content;
			pixR = std::stoi(content);

			myfile >> content;
			pixG = std::stoi(content);

			myfile >> content;
			pixB = std::stoi(content);

			matrixi.push_back(make_tuple(pixR / 255.999, pixG / 255.999, pixB / 255.999));

		}
		texture_.push_back(matrixi);
	}

}

Texture::~Texture()
{
	this->texture_.clear();
}