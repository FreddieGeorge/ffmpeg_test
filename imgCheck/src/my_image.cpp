#include "my_image.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include "bmpReader.h"
#include "pngReader.h"

bool fileExists(const std::string &filename)
{
    std::ifstream file(filename.c_str());
    return file.good();
}

imgReader* my_image::createImageReader(const std::string &imgFileName)
{
    // check file exit
    if(fileExists(imgFileName))
    {
        size_t dotIndex = imgFileName.find_last_of('.');
        if(dotIndex != std::string::npos)
        {
            std::string extension = imgFileName.substr(dotIndex + 1);
            /* if(extension == "png")
            {
                return new pngReader(imgFileName);
            }
            else */if(extension == "bmp")
            {
                return new bmpReader(imgFileName);
            }
            else
            {
                std::cerr << "Unsupported image format: " << extension << std::endl;
            }
        }
        else
        {
            std::cerr << "Invalid filename:" << imgFileName << std::endl;
        }
        return nullptr;
    }
    else
    {
        std::cerr << "Error:Image file not exits!" << std::endl;
    }

    return nullptr;
}


