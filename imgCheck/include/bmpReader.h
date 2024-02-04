#pragma once

#include "imgReader.h"

// little endian
// there are other magic num such as BA CI, I just write the most common one
#define BMP_MAGIC_BM 0x424D


class bmpReader : public imgReader
{
public:
    // constructor
    bmpReader(){};
    bmpReader(const std::string &imgFileName);
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
    bool isBMPFile();

private:
    std::string fileName;
};