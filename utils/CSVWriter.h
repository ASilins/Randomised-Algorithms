#ifndef CSVWRITTER_H
#define CSVWRITTER_H
#include <string>


class CSVWriter {
public:
    explicit CSVWriter(const std::string &file, const std::string &header);
    void appendResult(const std::string &text) const;
private:
    std::string filename;
};

#endif //CSVWRITTER_H
