#ifndef VIDEOGAME_PLAYERGUI_H
#define VIDEOGAME_PLAYERGUI_H

#include "..\headers\PreCompHeaders.h"
#include "..\entities\GameCharacter.h"
class PlayerGui {
private:
    GameCharacter* player;
public:
    PlayerGui( GameCharacter* player);

    virtual ~PlayerGui();

    ///functions
    void update(const float& dt);
    void render(sf::RenderTarget & target);
};


#endif //VIDEOGAME_PLAYERGUI_H
