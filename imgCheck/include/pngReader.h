#pragma once

#include "imgReader.h"

class pngReader : public imgReader
{
public:
    // constructor
    pngReader(){};
    pngReader(const std::string &imgFileName);
    void init();
    // base class
    eImgClass getImgClass() { return IMG_CLASS_BMP; };
    int getImgHeight();
    int getImgWidth();
    int getImgSize();

    bool checkImgValid();
    int readImg();

    // only
private:
    bool isPNGFile();

private:
    std::string fileName;
};