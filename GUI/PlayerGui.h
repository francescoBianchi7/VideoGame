#ifndef VIDEOGAME_PLAYERGUI_H
#define VIDEOGAME_PLAYERGUI_H

#include "..\headers\PreCompHeaders.h"
#include "..\entities\GameCharacter.h"
class PlayerGui {
private:
    GameCharacter* player;

    sf::Font GUIfont;
    sf::Text levelText;
    std::string levelString;
    //EXP
    sf::Text expText;
    std::string expString;
    //HP BAR
    sf::RectangleShape hpBarBack;
    sf::RectangleShape hpBarInner;
    float hpBarMaxWidth;
    sf::Text hpBarText;
    std::string hpBarString;
    ///initFunction
    void initLevel();
    void initFont();
    void initExpText();
    void initHPbar();
public:
    PlayerGui( GameCharacter* player);

    virtual ~PlayerGui();

    ///update functions
    void updateLevel();
    void updateExpText();
    void updateHpBar();
    void update(const float& dt);
    ///render functions
    void renderLevel(sf::RenderTarget &target);
    void renderExpText(sf::RenderTarget &target);
    void renderHpBar(sf::RenderTarget &target);
    void render(sf::RenderTarget & target);
};


#endif //VIDEOGAME_PLAYERGUI_H
