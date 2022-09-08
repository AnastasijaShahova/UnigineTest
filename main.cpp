#include <iostream>
#include "Units.hpp"
#include "Defenition.h"

int main(int argc, const char * argv[]) {

    Units map_units(UNITS_COUNT);

    for (size_t i = 0; i < map_units.Count(); ++i)
    {
        const auto& unit = map_units[i];
        std::cout << "Unit" << i << ",pos" << unit.getPos()<<",dir" << unit.getDir() << std::endl;
    }
    
    map_units.UpdateAllVisible(4);

    for (size_t i = 0; i < map_units.Count(); ++i)
    {
        const auto& unit = map_units[i];
        std::cout << "Unit" << i << ",sees count: " << unit.visible_count << std::endl;
    }
    
    return 0;
}
