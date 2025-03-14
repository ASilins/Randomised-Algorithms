#include "CSVWriter.h"

#include <fstream>
#include <iostream>

CSVWriter::CSVWriter(const std::string &file, const std::string &header) : filename(file) {
    std::ofstream fileCheck(filename, std::ios::app);
    if (fileCheck.tellp() == 0) {
        fileCheck << header << std::endl;
    }
}

void CSVWriter::append_result(const std::string &text) const {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << text;
    } else {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
}

