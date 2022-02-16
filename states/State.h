//
// Created by bianc on 30/11/2021.
//

#ifndef VIDEOGAME_STATE_H
#define VIDEOGAME_STATE_H



#include "../entities/GameCharacter.h"

//Base class to create various state of the game e.g starting menu,game state
class State {
protected:
    std::stack<State *> *states;
    sf::RenderWindow* window;
    std::map<std::string ,sf::Texture> textures;
    std::map<std::string,int>* supportedKeys;
    std::map<std::string,int> keybinds;
    bool paused;
    bool quit;
    float keyTime,keyTimeMax;
    sf::Vector2i mousePosScreen;
    sf::Vector2i mouseposWindow;
    sf::Vector2f mouseposView;

    virtual void initKeybinds()=0;//each state is gonna have it's own keybinding

public:

    State(sf::RenderWindow* window,std::map<std::string,int>* supportedKeys,std::stack<State*> *states);
    virtual ~State();

    const bool& getQuit() const;
    bool getKeyTime();

    virtual void updateKeyTime(const float &dt);
    virtual void endState()=0;
    void pauseState();
    void unpauseState();
    virtual void updateMousePosition();
    virtual void updateInput(const float& dt)=0;
    virtual void update(const float& dt)=0;// pure virtual make sure you can instantiate only through inheritance
    virtual void render(sf::RenderTarget* target)=0;//same here
};


#endif //VIDEOGAME_STATE_H
