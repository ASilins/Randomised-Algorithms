#include "CSVWriter.h"

#include <fstream>
#include <iostream>

CSVWriter::CSVWriter(const std::string &file) : filename(file) {
    std::ofstream fileCheck(filename, std::ios::app);
    if (fileCheck.tellp() == 0) {
        fileCheck << "algorithm,n,build,query" << std::endl;
    }
}

void CSVWriter::appendResult(const std::string& algorithm, uint32_t n, u_int64_t buildTime, u_int64_t queryTime) const {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << algorithm << "," << n << "," << buildTime << "," << queryTime << "\n";
    } else {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
}

