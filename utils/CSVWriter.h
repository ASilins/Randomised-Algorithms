#ifndef CSVWRITTER_H
#define CSVWRITTER_H
#include <fstream>
#include <iostream>
#include <string>


class CSVWriter {
public:

    /**
     * CSVWriter constructor that initializes the CSV file with a header.
     *
     * @param file the file name to write to
     * @param header the first row in the CSV file
     */
    CSVWriter(const std::string &file, const std::string &header) : filename(file) {
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
    void append_result(const std::string &text) const {
        if (std::ofstream file(filename, std::ios::app); file.is_open()) {
            file << text;
        } else {
            std::cerr << "Error opening file: " << filename << std::endl;
        }
    }

    template<typename... Args>
    void append_row(Args... args) const {
        std::ofstream file(filename, std::ios::app);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }
        write_to_file(file, args...);
        file << std::endl;
    }

    // Base case
    template<typename LastArg>
    void write_to_file(std::ofstream &file, LastArg lastArg) const {
        file << lastArg;
    }

    // Recursive case
    template<typename FirstArg, typename... RestOfArgs>
    void write_to_file(std::ofstream &file, FirstArg firstArg, RestOfArgs... rest) const {
        file << firstArg << ",";
        write_to_file(file, rest...);
    }

private:
    std::string filename;
};

#endif //CSVWRITTER_H
