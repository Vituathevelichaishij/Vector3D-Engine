#pragma once
#include "Light.h"
class FlatLight : public Light{
    public:
        virtual void start() override;
        virtual void update(Uint32 dT) override;
        virtual void init(YAML::Node const& data) override;
        virtual float getLuminocity(Triangle const& tri);
        ~FlatLight() override =default;
    private:
        Vector3D m_lightDir;
};
