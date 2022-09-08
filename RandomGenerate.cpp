#include <set>
#include "RandomGenerate.hpp"
#include "Vector.hpp"

static float width;
static float height;

void Random::GenerateSectors(std::vector<Unit>& units, std::vector<std::vector<size_t>>& sectors, Vector& min, Vector& max)
{
    sectors.clear();
    sectors.resize(SIZE * SIZE);

    max.x = units[0].getPos().x;
    max.y = units[0].getPos().y;
    
    for (const auto& unit : units)
    {
        min.x = std::fminf(min.x, unit.getPos().x);
        min.y = std::fminf(min.y, unit.getPos().y);

        max.x = std::fmaxf(max.x, unit.getPos().x);
        max.y = std::fmaxf(max.y, unit.getPos().y);
    }

    width = (max.x - min.x) / SIZE;
    height = (max.y - min.y) / SIZE;

    for (size_t i = 0; i < units.size(); ++i)
    {
        Vector shifted_pos = units[i].getPos() - min;

        size_t section_y = std::min(size_t(shifted_pos.y / height), size_t(SIZE - 1));
        size_t section_x = std::min(size_t(shifted_pos.x / width), size_t(SIZE - 1));

        sectors[section_y * SIZE + section_x].push_back(i);
    }
}

void Random::GenerateUnits(std::vector<Unit>& units, size_t count)
{
    units.clear();
    units.reserve(count);

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<float> dist (MIN_RANDOM, MAX_RANDOM);
    
    auto cmp = [](const Vector& left_v, const Vector& right_v) {
        return  left_v.x < right_v.x || left_v.y < right_v.y;
    };
    
    std::set<Vector, decltype(cmp)> unique_pos(cmp);

    while (unique_pos.size() != count)
    {
        unique_pos.emplace(dist(generator), dist(generator));
    }

    for (const auto& position : unique_pos)
    {
        Vector direction { dist(generator), dist(generator) };
        direction.Normalize();

        units.push_back({ position, direction });
    }
}
