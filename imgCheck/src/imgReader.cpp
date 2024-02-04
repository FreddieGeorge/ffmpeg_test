#include "imgReader.h"

imgReader::imgReader()
{
    m_imgHeight = 0;
    m_imgWeight = 0;
    m_imgSize = 0;
    b_imgValid = false;
};

std::string imgReader::classToString(eImgClass imgClass)
{
    switch (imgClass)
    {
    case IMG_CLASS_PNG:
        return "PNG";
        break;
    case IMG_CLASS_BMP:
        return "BMP";
        break;

    default:
        return "Unsupport format";
        break;
    }
}

void imgReader::printImgInfo()
{
    if (b_imgValid)
    {
        std::cout << "Format: " << classToString(getImgClass()) << std::endl;
        std::cout << "Height: " << m_imgHeight << std::endl;
        std::cout << "Weight: " << m_imgWeight << std::endl;
        std::cout << "Size: " << static_cast<double>(m_imgSize) / 1024.0 << "KB" << std::endl;
    }
    else
    {
        std::cerr << "Error : invalid image file" << std::endl;
    }
}

std::vector<char> imgReader::readBytes(const std::string &filename, std::streampos start, std::streamsize size)
{
    std::ifstream file(filename, std::ios::binary);
    std::vector<char> result;

    if (file.is_open())
    {
        // 设置读取位置
        file.seekg(start);

        // 读取指定范围的字节
        result.resize(size);
        file.read(result.data(), size);

        // 检查是否读取成功
        if (file)
        {
            // std::cout << "Successfully read " << size << " bytes." << std::endl;
            ;
        }
        else
        {
            std::cerr << "Error reading file." << std::endl;
        }

        // 关闭文件
        file.close();
    }
    else
    {
        std::cerr << "Unable to open the file." << std::endl;
    }

    return result;
}