//
// Created by bianc on 09/02/2022.
//
#include "PreCompHeaders.h"
#include "EditorState.h"

EditorState::EditorState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys,
                         std::stack<State *> *states) : State(window, supportedKeys, states) {
    initKeybinds();
    initfonts();
    initVariables();
    initBackground();
    //initButtons();
}

EditorState::~EditorState() {

}

// initialiazer functions
void EditorState::initVariables() {

}
void EditorState::initBackground() {

}

void EditorState::initKeybinds() {
    std::ifstream ifs("./config/editorstate_keybinds.ini");
    if(ifs.is_open()){
        std::string key=" ";
        std::string key2=" ";
        while(ifs >> key >> key2){
            this->keybinds[key]=this->supportedKeys->at(key2);
        }
    }
    ifs.close();
}

void EditorState::initfonts() {
    if(!this->font.loadFromFile("assets/fonts/Amarante.ttf"))
    {
        throw("ERROR::EDITORSTATE::COULD NOT LOAD FONT");
    }
}

//rendering functions
void EditorState::render(sf::RenderTarget *target) {
    if(!target)
        target=this->window;

    renderButtons(*target);
}

void EditorState::renderButtons(sf::RenderTarget &target) {
    for(auto &it: this->buttons){
        it.second->render(target);
    }
}


//update functions
void EditorState::updateButtons() {
    for(auto &it: this->buttons){
        it.second->update(this->mouseposView);
    }
}

void EditorState::updateInput(const float &dt) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
        this->endState();
}

void EditorState::update(const float &dt) {
    this->updateMousePosition();
    this->updateInput(dt);
    this->updateButtons();
}

//other functions
void EditorState::endState() {
    this->quit=true;
    std::cout<<"ending gamestate"<<"\n";
}


