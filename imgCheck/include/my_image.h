#pragma once
#include <string>

#include "imgReader.h"

class my_image
{
public:
    ~my_image(){};

    static imgReader *createImageReader(const std::string& imgFileName);
};