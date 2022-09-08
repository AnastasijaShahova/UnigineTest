#ifndef Unit_hpp
#define Unit_hpp

#include <random>
#include <vector>
#include "Unit.h"

class Units
{
public:
    explicit Units(size_t count);

    size_t Count() const
    {
        return units.size();
    }

    Unit& operator[](size_t index)
    {
        return units[index];
    }

    const Unit& operator[](size_t index) const
    {
        return units[index];
    }
    
    void UpdateVisible(size_t unit_index);
    void UpdateAllVisible(size_t threads_count);

private:
    std::pair<size_t, size_t> GetSectorCoords(const Vector& point);

    Vector min;
    Vector max;
    
    std::vector<Unit> units;
    std::vector<std::vector<size_t>> sectors;
};


#endif /* Unit_hpp */
