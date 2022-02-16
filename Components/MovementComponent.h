//
// Created by bianc on 27/12/2021.
//

#ifndef VIDEOGAME_MOVEMENTCOMPONENT_H
#define VIDEOGAME_MOVEMENTCOMPONENT_H



enum movement_states {IDLE=0,MOVING,MOVING_LEFT,MOVING_RIGHT,MOVING_UP,MOVING_DOWN};
class MovementComponent {
private:
    sf::Sprite& sprite;
    float acceleration, deceleration;
    float maxSpeed;
    sf::Vector2f velocity;// speed and direction

public:
    MovementComponent(sf::Sprite& sprite,float maxSpeed,float acceleration,float deceleration);
    virtual ~MovementComponent();

    const sf::Vector2f& getVelocity() const;
    const float& getSpeed() const;
    bool getState(short unsigned state) const;
    void stopVelocity();
    void stopVelocityX();
    void stopVelocityY();
    void move(const float &dt,float dir_x,float dir_y);
    void update(const float& dt);
};


#endif //VIDEOGAME_MOVEMENTCOMPONENT_H
