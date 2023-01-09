/*
code file created by ilyass SABIR
*/


#ifndef TEXTURE_h
#define TEXTURE_h

#include <iostream>
#include <vector>

using namespace std;

class Texture
{
public:
    Texture(string path);
    ~Texture();
    string getPath() { return path_; }
    vector<vector<tuple<double, double, double>>> getTexture() { return texture_; }
    int getTextureWidth() { return width_; }
    int getTextureHeight() { return height_; }


private:
    string path_;
    vector<vector<tuple<double, double, double>>> texture_;
    int width_;
    int height_;
};

#endif