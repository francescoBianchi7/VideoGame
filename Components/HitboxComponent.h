//
// Created by bianc on 10/02/2022.
//

#ifndef VIDEOGAME_HITBOXCOMPONENT_H
#define VIDEOGAME_HITBOXCOMPONENT_H
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class HitboxComponent {
private:
    sf::Sprite& sprite;
    sf::RectangleShape hitbox;
    float offsetX,offsetY;
public:

    HitboxComponent(float offset_x,float offset_y,sf::Sprite &sprite,float width,float height);

    virtual ~HitboxComponent();
    bool checkIntersect(const sf::FloatRect& rect);
    void update();
    void render(sf::RenderTarget& target);
};


#endif //VIDEOGAME_HITBOXCOMPONENT_H
