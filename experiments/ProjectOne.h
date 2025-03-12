#ifndef PROJECTONE_H
#define PROJECTONE_H
#include <cstdint>
#include <vector>
#include "../utils/CSVWriter.h"


class ProjectOne {
public:
    static void runExperiments();
private:
    static void runChainingExperiment(const CSVWriter &writer, const CSVWriter &listWriter, const std::vector<uint32_t> &list,
        const std::uint8_t &w, const std::uint32_t &m);

    static void runRedBlackExperiment(const CSVWriter &writer, const std::vector<uint32_t> &list,  const uint32_t &m);

    static void runPerfectHashingExperiment(const CSVWriter &writer, const CSVWriter &rehashesWriter, std::vector<uint32_t> &list,
        const uint8_t &w, const uint32_t &m);
};



#endif //PROJECTONE_H
