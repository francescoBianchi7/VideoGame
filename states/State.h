#ifndef VIDEOGAME_STATE_H
#define VIDEOGAME_STATE_H

#include "../entities/GameCharacter.h"
#include "../headers/GSettings.h"
#include "../headers/PreCompHeaders.h"
class State;

class StateData{//class used to make it simplier to pass data between various states
public:
    StateData(){}
    //Vars

    GSettings* gxSettings;
    float tileSize;
    sf::RenderWindow* window;
    std::stack<State *> *states;
    std::map<std::string,int>* supportedKeys;
};
//Base class to create various state of the game e.g starting menu,game state
class State {
protected:
    StateData& stateData;
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
    sf::Vector2i mousePosGrid;
    float tileSize;
    virtual void initKeybinds()=0;//each state is gonna have it's own keybinding

public:

    State(StateData& stateData);
    virtual ~State();

    const bool& getQuit() const;
    bool getKeyTime();


    virtual void endState()=0;
    void pauseState();
    void unpauseState();
    virtual void updateKeyTime(const float &dt);
    virtual void updateMousePosition(sf::View* view=nullptr);
    virtual void updateInput(const float& dt)=0;
    virtual void update(const float& dt)=0;// pure virtual make sure you can instantiate only through inheritance
    virtual void render(sf::RenderTarget* target)=0;//same here
};


#endif //VIDEOGAME_STATE_H
