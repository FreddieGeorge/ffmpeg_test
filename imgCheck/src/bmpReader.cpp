#include "bmpReader.h"

bmpReader::bmpReader(const std::string &filename) : fileName(filename)
{
    init();
}

void bmpReader::init()
{
    if (checkImgValid())
    {
        getImgHeight();
        getImgWidth();
        getImgSize();
    }
}

bool bmpReader::checkImgValid()
{
    b_imgValid = isBMPFile();

    return b_imgValid;
}

int bmpReader::readImg()
{
    return -1;
}

int bmpReader::getImgHeight()
{
    std::streampos start = 22; // 从第23个字节开始
    std::streamsize size = 4; // 读取4个字节

    std::vector<char> bytes = readBytes(fileName, start, size);

    // 将 vector 中的数据按小端读取为 int
    // int m_imgHeight = 0;
    for (size_t i = 0; i < bytes.size(); ++i)
    {
        m_imgHeight |= (static_cast<unsigned char>(bytes[i]) << (8 * i));
    }

    return m_imgHeight;
}

int bmpReader::getImgWidth()
{
    std::streampos start = 18; // 从第19个字节开始
    std::streamsize size = 4;  // 读取4个字节

    std::vector<char> bytes = readBytes(fileName, start, size);

    // 将 vector 中的数据按小端读取为 int
    for (size_t i = 0; i < bytes.size(); ++i)
    {
        m_imgWeight |= (static_cast<unsigned char>(bytes[i]) << (8 * i));
    }

    return m_imgWeight;
}

int bmpReader::getImgSize()
{
    std::streampos start = 2; // 从第3个字节开始
    std::streamsize size = 4;  // 读取4个字节

    std::vector<char> bytes = readBytes(fileName, start, size);

    // 将 vector 中的数据按小端读取为 int
    // int m_imgSize = 0;
    for (size_t i = 0; i < bytes.size(); ++i)
    {
        m_imgSize |= (static_cast<unsigned char>(bytes[i]) << (8 * i));
    }

    return m_imgSize;
}

bool bmpReader::isBMPFile()
{
    std::streampos start = 0; // 从第2个字节开始
    std::streamsize size = 2; // 读取2个字节

    std::vector<char> bytes = readBytes(fileName, start, size);

    // 将 vector 转换为数值
    unsigned int magicNum = 0;
    for (char byte : bytes)
    {
        magicNum = (magicNum << 8) | (byte & 0xFF);
    }

    if (magicNum == BMP_MAGIC_BM)
    {
        return true;
    }
    else
    {
        std::cerr << "Error: Not a bmp file." << std::endl;
        return false;
    }
}
