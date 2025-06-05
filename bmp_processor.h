#ifndef BMP_CONVERTER_BMP_PROCESSOR_H
#define BMP_CONVERTER_BMP_PROCESSOR_H
#pragma once
#include <fstream>
#include <vector>
#include <string>

#pragma pack(push, 1)
struct BMPHeader {
    uint16_t signature;
    uint32_t fileSize;
    uint32_t reserved;
    uint32_t dataOffset;
};

struct BMPInfoHeader {
    uint32_t headerSize;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t imageSize;
};
#pragma pack(pop)

class BMPProcessor {
public:
    bool load(const std::string& filename);
    bool save(const std::string& filename);
    void drawX();
    void displayInConsole() const;

private:
    void drawLine(int x1, int y1, int x2, int y2, uint8_t r, uint8_t g, uint8_t b);

    BMPHeader header{};
    BMPInfoHeader infoHeader{};
    std::vector<uint8_t> pixels;
    int rowStride = 0;
};
#endif //BMP_CONVERTER_BMP_PROCESSOR_H
