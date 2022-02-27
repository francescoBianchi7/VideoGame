//
// Created by bianc on 22/02/2022.
//
#include "../headers/PreCompHeaders.h"
#include "GSettings.h"

GSettings::GSettings(){
    title="Default";
    resolution=sf::VideoMode::getDesktopMode();
    fullscreen=false;
    verticalSync=false;
    fpsLimit=120;
    contextSettings.antialiasingLevel=0;
    videoModes=sf::VideoMode::getFullscreenModes();
}
//not used yet
void GSettings::saveToFile(const std::string path){
    std::ofstream ofs(path);
    if(ofs.is_open()){
        ofs<<title;
        ofs<<resolution.width<<"  "<<resolution.height;
        ofs<<fullscreen;
        ofs<<fpsLimit;
        ofs<<verticalSync;
        ofs<<contextSettings.antialiasingLevel;
    }
    ofs.close();
}
//not used yet
void GSettings::loadFromFile(const std::string path){
    std::ifstream ifs(path);
    if(ifs.is_open()){
        std::getline(ifs,this->title);
        ifs>>resolution.width>>resolution.height;
        ifs>>fullscreen;
        ifs>>fpsLimit;
        ifs>>verticalSync;
        ifs>>contextSettings.antialiasingLevel;
    }
    ifs.close();
}