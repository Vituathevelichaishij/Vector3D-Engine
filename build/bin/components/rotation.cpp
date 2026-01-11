#include "Component.h"
#include "GameObject.h"

class rotation : public Component{
    public:
        void update(Uint32 dT) override{
            owner->m_transform.m_rotation.m_x+=0.3;
            owner->m_transform.m_rotation.m_y+=0.6;
            owner->m_transform.m_rotation.m_z+=1;
        };
        void start() override{};
        ~rotation() override =default;
        
};

void register_rotation() {
    ComponentFactory::init().registerComponent("rotation", []() {
        return std::make_unique<rotation>();
    });
}





