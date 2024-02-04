#pragma once
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

typedef enum imgClass
{
    IMG_CLASS_PNG = 0,
    IMG_CLASS_BMP,
    IMG_CLASS_UNKNOWN,
} eImgClass;

class imgReader {
public:
    imgReader();
    virtual ~imgReader(){}
    // virtual func part

    virtual bool checkImgValid() = 0;
    virtual int readImg() = 0;
    virtual void init() = 0;

    virtual eImgClass getImgClass() = 0;
    virtual int getImgHeight() = 0;
    virtual int getImgWidth() = 0;
    virtual int getImgSize() = 0;

    std::string classToString(eImgClass imgClass);

    void printImgInfo();

    std::vector<char> readBytes(const std::string &filename, std::streampos start, std::streamsize size);

    // param
    int m_imgHeight;
    int m_imgWeight;
    int m_imgSize;
    bool b_imgValid;
};