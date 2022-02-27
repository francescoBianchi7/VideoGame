//
// Created by bianc on 22/02/2022.
//

#ifndef VIDEOGAME_GSETTINGS_H
#define VIDEOGAME_GSETTINGS_H


class GSettings{
public:

    std::string title;
    sf::VideoMode resolution;
    bool fullscreen;
    bool verticalSync;
    unsigned fpsLimit;
    sf::ContextSettings contextSettings;
    std::vector<sf::VideoMode> videoModes;

    GSettings();

    void saveToFile(const std::string path);
    void loadFromFile(const std::string path);
};

#endif //VIDEOGAME_GSETTINGS_H
