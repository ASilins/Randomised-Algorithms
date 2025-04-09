#include "CSVWriter.h"

#include <fstream>
#include <iostream>

/**
 * CSVWriter constructor that initializes the CSV file with a header.
 *
 * @param file the file name to write to
 * @param header the first row in the CSV file
 */
CSVWriter::CSVWriter(const std::string &file, const std::string &header) : filename(file) {
    std::ofstream fileCheck(filename, std::ios::app);
    if (fileCheck.tellp() == 0) {
        fileCheck << header << std::endl;
    }
}

/**
 * Append a string to the CSV file
 *
 * @param text text to append to CSV file
 */
void CSVWriter::append_result(const std::string &text) const {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << text;
    } else {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
}

