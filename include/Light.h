#pragma once
#include "Component.h"
#include "BasicGeometry.h"
class Light : public Component{
    public:

        virtual float getLuminocity(Triangle const& tri) = 0;
};