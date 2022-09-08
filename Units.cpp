#include "Units.hpp"
#include "RandomGenerate.hpp"
#include <thread>

Units::Units(size_t count)
{
    Random::GenerateUnits(units, count);
    Random::GenerateSectors(units, sectors, min, max);
}

std::pair<size_t, size_t> Units::GetSectorCoords(const Vector& point)
{
    Vector shifted = point - min;
    
    float width = (max.x - min.x) / SIZE;
    float height = (max.y - min.y) / SIZE;

    if (shifted.x < 0)
        shifted.x = 0;

    if (shifted.y < 0)
        shifted.y = 0;

    Vector shifted_max = max - min;

    if (shifted.x > shifted_max.x)
        shifted.x = shifted_max.x;

    if (shifted.y > shifted_max.y)
        shifted.y = shifted_max.y;

    return { std::min(size_t(shifted.x / width), size_t(SIZE - 1)),
             std::min(size_t(shifted.y / height), size_t(SIZE - 1)) };
}

void Units::UpdateVisible(size_t unit_index)
{
    if (unit_index >= units.size())
        return;

    auto& unit = units[unit_index];
    unit.visible_count = 0;

    const Vector distance_vector{ VIEW_DISTANCE };

    auto start = GetSectorCoords(unit.getPos() - distance_vector);
    auto end = GetSectorCoords(unit.getPos() + distance_vector);

    for (size_t y = start.second; y <= end.second; ++y)
    {
        for (size_t x = start.first; x <= end.first; ++x)
        {
            const auto& sector = sectors[y * SIZE + x];
            
            for (auto i : sector)
            {
                const Vector& point = units[i].getPos();
                
                if (i == unit_index)
                    continue;

                if (unit.IsVisible(point))
                    ++unit.visible_count;
            }
        }
    }
}

void Units::UpdateAllVisible(size_t threads_count)
{
    size_t step = Count() / threads_count;
    size_t remainder = Count() % threads_count;
        
    std::vector<std::thread> threads;
    threads.reserve(threads_count + remainder ? 1 : 0);

    auto thread_ = [&](size_t start, size_t end)
    {
        for (; start < end; ++start)
        {
            this->UpdateVisible(start);
        }
    };

    if (step != 0)
    {
        for (size_t i = 0; i < Count() - remainder; i += step)
        {
            threads.emplace_back(std::thread{ thread_, i, i + step });
        }
    }

    if (remainder != 0)
    {
        threads.emplace_back(std::thread{ thread_, Count() - remainder, Count() });
    }

    for (auto& t : threads)
    {
        t.join();
    }
}
