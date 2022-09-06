#include "PlayerGui.h"

#include <cmath>

void PlayerGui::initFont() {
this->GUIfont.loadFromFile("assets/fonts/slant_regular.ttf");

}

void PlayerGui::initLevel() {
    float x=125.f;
    float y=10.f;
    levelText.setFont(GUIfont);
    levelText.setScale(0.7,0.7);
    levelText.setPosition(x,y);
    levelText.setOutlineColor(sf::Color::White);
    levelText.setFillColor(sf::Color::Yellow);
}

void PlayerGui::initExpText() {
    float x=170.f;
    float y=13.f;
    expText.setFont(GUIfont);
    expText.setScale(0.6,0.6);
    expText.setPosition(x,y);
    expText.setOutlineColor(sf::Color::White);
    expText.setFillColor(sf::Color(30,30,200,250));
}

void PlayerGui::initHPbar() {
    float width=100.f;
    float height=10.f;
    float x=20.f;
    float y=20.f;

    hpBarMaxWidth=width;

    hpBarText.setFont(GUIfont);
    hpBarText.setScale(0.75,0.75);

    hpBarBack.setSize(sf::Vector2f(width, height));
    hpBarBack.setFillColor(sf::Color(50,50,50,200));
    hpBarBack.setPosition(x,y);

    hpBarInner.setSize(sf::Vector2f(width,height));
    hpBarInner.setFillColor(sf::Color(250,20,20,200));
    hpBarInner.setPosition(hpBarBack.getPosition());

    hpBarText.setPosition(hpBarBack.getPosition().x,hpBarBack.getPosition().y);

}
PlayerGui::PlayerGui( GameCharacter* player) {
    this->player=player;
    initFont();
    initHPbar();
    initLevel();
    initExpText();
}

PlayerGui::~PlayerGui() {
}
///update functions
void PlayerGui::update(const float &dt) {
    updateHpBar();
    updateExpText();
    updateLevel();
}
void PlayerGui::updateExpText() {
    expString=std::to_string(player->getAttributeComponent()->exp)+"/"+std::to_string(player->getAttributeComponent()->expNext);
    expText.setString(expString);
}
void PlayerGui::updateLevel() {
    levelString="lvl:"+std::to_string(player->getAttributeComponent()->level);
    levelText.setString(levelString);
}
void PlayerGui::updateHpBar() {
    float percent =static_cast<float>(player->getAttributeComponent()->hp)
            /static_cast<float>(player->getAttributeComponent()->hpMax);
    hpBarInner.setSize(sf::Vector2f(static_cast<float>(hpBarMaxWidth*percent),hpBarInner.getSize().y));
    hpBarString= std::to_string(player->getAttributeComponent()->hp)+"/"+std::to_string(player->getAttributeComponent()->hpMax);
    hpBarText.setString(hpBarString);
}
///render functions
void PlayerGui::renderLevel(sf::RenderTarget &target) {
    target.draw(levelText);
}
void PlayerGui::renderExpText(sf::RenderTarget &target) {
    target.draw(expText);
}

void PlayerGui::renderHpBar(sf::RenderTarget &target) {
    target.draw(this->hpBarBack);
    target.draw(this->hpBarInner);
    target.draw(this->hpBarText);
}
void PlayerGui::render(sf::RenderTarget &target) {
    renderHpBar(target);
    renderExpText(target);
    renderLevel(target);
}
