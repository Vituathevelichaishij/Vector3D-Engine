#include "Settings.h"
Settings::Settings(){
    YAML::Node config = YAML::LoadFile("../config.yaml");
    m_windowWidth=config["WindowWidth"].as<int>();
    m_windowHeight=config["WindowHeight"].as<int>();

    m_pointOfViewAngle=config["PointOfView"].as<int>();

    m_maxDistance=config["MaxDistance"].as<float>();
    m_screenDistance=config["ScreenDistance"].as<float>();
}