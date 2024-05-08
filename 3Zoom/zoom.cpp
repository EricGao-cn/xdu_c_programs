#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <windows.h>

// 读取位图文件信息
bool LoadBitmapInfo(const std::string& filename, BITMAPFILEHEADER& fileHeader, BITMAPINFOHEADER& infoHeader, std::vector<unsigned char>& pixelData) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Cannot open the file " << filename << std::endl;
        return false;
    }

    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    // 检查是否为位图文件
    if (fileHeader.bfType != 0x4D42) {
        std::cerr << "Error: The file " << filename << " is not a bitmap file." << std::endl;
        return false;
    }

    // 只处理24位色深的位图
    if (infoHeader.biBitCount != 24) {
        std::cerr << "Error: The bitmap must be 24 bits per pixel." << std::endl;
        return false;
    }

    // 计算行大小并读取像素数据
    long lineSize = (infoHeader.biWidth * infoHeader.biBitCount / 8 + 3) & ~3;   // 四字节对齐 
    pixelData.resize(lineSize * infoHeader.biHeight);
    file.seekg(fileHeader.bfOffBits, std::ios::beg);
    file.read(reinterpret_cast<char*>(pixelData.data()), pixelData.size());

    file.close();
    return true;
}

// 保存位图文件信息
bool SaveBitmapInfo(const std::string& filename, BITMAPFILEHEADER& fileHeader, BITMAPINFOHEADER& infoHeader, const std::vector<unsigned char>& pixelData) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Cannot open the file " << filename << std::endl;
        return false;
    }

    file.write(reinterpret_cast<const char*>(&fileHeader), sizeof(fileHeader));
    file.write(reinterpret_cast<const char*>(&infoHeader), sizeof(infoHeader));
    file.write(reinterpret_cast<const char*>(pixelData.data()), pixelData.size());

    file.close();
    return true;
}

// 双线性插值
unsigned char BilinearInterpolate(const std::vector<unsigned char>& inputPixels, long srcWidth, long srcHeight, double srcX, double srcY, int channel, long lineSize) {
    int x = static_cast<int>(srcX);
    int y = static_cast<int>(srcY);
    double u = srcX - x;
    double v = srcY - y;

    int x1 = std::min((long)x + 1, srcWidth - 1);
    int y1 = std::min((long)y + 1, srcHeight - 1);

    double p1 = inputPixels[(y * lineSize) + (x * 3) + channel];
    double p2 = inputPixels[(y * lineSize) + (x1 * 3) + channel];
    double p3 = inputPixels[(y1 * lineSize) + (x * 3) + channel];
    double p4 = inputPixels[(y1 * lineSize) + (x1 * 3) + channel];

    return static_cast<unsigned char>((p1 * (1 - u) * (1 - v)) + (p2 * u * (1 - v)) + (p3 * (1 - u) * v) + (p4 * u * v));
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <input.bmp> <scale_percentage> <output.bmp>" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    int scalePercentage = std::stoi(argv[2]);
    std::string outputFile = argv[3];

    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    std::vector<unsigned char> inputPixels;

    if (!LoadBitmapInfo(inputFile, fileHeader, infoHeader, inputPixels)) {
        return 1;
    }

    double scale = scalePercentage / 100.0;
    long srcWidth = infoHeader.biWidth;
    long srcHeight = infoHeader.biHeight;
    long srcLineSize = ((srcWidth * infoHeader.biBitCount / 8 + 3) & ~3);

    long dstWidth = static_cast<long>(srcWidth * scale);
    long dstHeight = static_cast<long>(srcHeight * scale);
    long dstLineSize = ((dstWidth * infoHeader.biBitCount / 8 + 3) & ~3);

    std::vector<unsigned char> outputPixels(dstLineSize * dstHeight);

    for (long y = 0; y < dstHeight; ++y) {
        for (long x = 0; x < dstWidth; ++x) {
            double srcX = x / scale;
            double srcY = y / scale;

            for (int channel = 0; channel < 3; ++channel) {
                outputPixels[(y * dstLineSize) + (x * 3) + channel] = BilinearInterpolate(inputPixels, srcWidth, srcHeight, srcX, srcY, channel, srcLineSize);
            }
        }
    }

    // 更新文件头和信息头
    fileHeader.bfSize = sizeof(fileHeader) + sizeof(infoHeader) + dstLineSize * dstHeight;
    fileHeader.bfOffBits = sizeof(fileHeader) + sizeof(infoHeader);

    infoHeader.biWidth = dstWidth;
    infoHeader.biHeight = dstHeight;
    infoHeader.biSizeImage = dstLineSize * dstHeight;

    if (!SaveBitmapInfo(outputFile, fileHeader, infoHeader, outputPixels)) {
        return 1;
    }

    std::cout << "Image scaling completed successfully." << std::endl;
    return 0;
}