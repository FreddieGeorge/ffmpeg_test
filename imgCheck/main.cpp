#include <iostream>
#include <string>

#include "my_image.h"


int main(int argc, char* argv[])
{
    std::string filename = "../resource/bootlogo.bmp";
    imgReader *imgReader = my_image::createImageReader(filename);

    imgReader->printImgInfo();
}