#include "bmp_processor.h"
#include <iostream>

int main() {
    BMPProcessor processor;
    std::string inputFile, outputFile;

    std::cout << "Enter input BMP file name: ";
    std::cin >> inputFile;

    if (!processor.load(inputFile)) return 1;

    std::cout << "\nOriginal image:\n";
    processor.displayInConsole();

    processor.drawX();
    std::cout << "\nImage with X:\n";
    processor.displayInConsole();

    std::cout << "\nEnter output BMP file name: ";
    std::cin >> outputFile;
    processor.save(outputFile);

    return 0;
}