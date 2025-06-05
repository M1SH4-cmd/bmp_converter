#include "bmp_processor.h"
#include <iostream>
#include <fstream>

bool BMPProcessor::load(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    file.read(reinterpret_cast<char*>(&header), sizeof(BMPHeader));
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(BMPInfoHeader));

    if (infoHeader.bitsPerPixel != 24 && infoHeader.bitsPerPixel != 32) {
        std::cerr << "Error: Only 24/32-bit BMP supported!" << std::endl;
        return false;
    }

    rowStride = (infoHeader.width * (infoHeader.bitsPerPixel / 8) + 3) & ~3;

    pixels.resize(rowStride * infoHeader.height);
    file.seekg(header.dataOffset);
    file.read(reinterpret_cast<char*>(pixels.data()), pixels.size());

    file.close();
    return true;
}

bool BMPProcessor::save(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) return false;

    file.write(reinterpret_cast<char*>(&header), sizeof(BMPHeader));
    file.write(reinterpret_cast<char*>(&infoHeader), sizeof(BMPInfoHeader));
    file.seekp(header.dataOffset);
    file.write(reinterpret_cast<char*>(pixels.data()), pixels.size());

    file.close();
    return true;
}

void BMPProcessor::drawLine(int x1, int y1, int x2, int y2, uint8_t r, uint8_t g, uint8_t b) {
    int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
    int dy = -abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
    int err = dx + dy, e2;

    while (true) {
        int index = (infoHeader.height - 1 - y1) * rowStride + x1 * (infoHeader.bitsPerPixel / 8);
        pixels[index + 0] = b; // B
        pixels[index + 1] = g; // G
        pixels[index + 2] = r; // R

        if (x1 == x2 && y1 == y2) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x1 += sx; }
        if (e2 <= dx) { err += dx; y1 += sy; }
    }
}

void BMPProcessor::drawX() {
    int w = infoHeader.width, h = infoHeader.height;
    drawLine(0, 0, w - 1, h - 1, 255, 0, 0);   // Красный крест
    drawLine(w - 1, 0, 0, h - 1, 255, 0, 0);
}

void BMPProcessor::displayInConsole() const {
    for (int y = infoHeader.height - 1; y >= 0; --y) {
        for (int x = 0; x < infoHeader.width; ++x) {
            int index = y * rowStride + x * (infoHeader.bitsPerPixel / 8);
            uint8_t r = pixels[index + 2];
            uint8_t g = pixels[index + 1];
            uint8_t b = pixels[index + 0];

            //'#' для чёрного '.' для белого
            std::cout << (r == 0 && g == 0 && b == 0 ? '#' : '.');
        }
        std::cout << std::endl;
    }
}