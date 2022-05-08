#ifndef VIDEOGAME_HITBOXCOMPONENT_H
#define VIDEOGAME_HITBOXCOMPONENT_H

class HitboxComponent {
private:
    sf::Sprite& sprite;
    sf::RectangleShape hitbox;
    sf::FloatRect nextPosition;
    float offsetX,offsetY;
public:
    HitboxComponent(float offset_x,float offset_y,sf::Sprite &sprite,float width,float height);
    virtual ~HitboxComponent();
    //GETTERS & SETTERS
    const sf::FloatRect & getNextPosition(const sf::Vector2f& velocity);
    const sf::Vector2f& getPosition();
    sf::FloatRect getGlobalBounds() const;
    void setPosition(const sf::Vector2f& position);
    void setPosition(float x,float y);
    //FUNCTIONS
    bool checkIntersect(const sf::FloatRect& rect);
    void update();
    void render(sf::RenderTarget& target);
};


#endif //VIDEOGAME_HITBOXCOMPONENT_H
