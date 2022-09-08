#ifndef RandomGenerate_hpp
#define RandomGenerate_hpp

#include <cmath>
#include <random>
#include "Unit.h"

namespace Random {

    void GenerateUnits(std::vector<Unit>& units, size_t count);
    void GenerateSectors(std::vector<Unit>& units, std::vector<std::vector<size_t>>& sectors, Vector& min, Vector& max);
}

#endif /* RandomGenerate_hpp */
