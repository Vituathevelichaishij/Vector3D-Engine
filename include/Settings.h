#ifndef SETTINGS_H
#define SETTINGS_H
#include <yaml-cpp/yaml.h>

    class Settings{
        public:
            Settings();
            int m_windowWidth;
            int m_windowHeight;
            int m_pointOfViewAngle;
            float m_maxDistance;
            float m_screenDistance;
    };    
#endif