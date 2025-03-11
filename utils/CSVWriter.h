#ifndef CSVWRITTER_H
#define CSVWRITTER_H
#include <string>


class CSVWriter {
public:
    explicit CSVWriter(const std::string &file);
    void appendResult(const std::string &algorithm, uint32_t n, u_int64_t buildTime, u_int64_t queryTime) const;
private:
    std::string filename;
};

#endif //CSVWRITTER_H
