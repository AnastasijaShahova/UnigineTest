#ifndef Unit_h
#define Unit_h

#include "Vector.hpp"
#include "Defenition.h"

class Unit
{
public:
    
    Unit(const Vector& pos, const Vector& dir)
    : pos(pos), dir(dir) {};
    
    const Vector& getPos() const
    {
        return pos;
    }
    
    const Vector& getDir() const
    {
        return dir;
    }
    
    bool IsVisible(const Vector& point) const
    {
        Vector sub_vector {point - pos};
        if (sub_vector.LengthQuad() > std::powf(VIEW_DISTANCE, 2))
            return false;

        sub_vector.Normalize();

        float angle = (180.f / M_PI) * std::fabsf(std::acosf(dir.Scalar(sub_vector)));
        
        if (angle > (FOV / 2))
            return false;

        return true;
    }
    
    size_t visible_count = 0;
private:
    Vector pos;
    Vector dir;
};


#endif /* Unit_h */
