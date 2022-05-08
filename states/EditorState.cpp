//
// Created by bianc on 09/02/2022.
//
#include "PreCompHeaders.h"
#include "EditorState.h"

EditorState::EditorState(StateData &stateData) : State(stateData) {
    initKeybinds();
    initfonts();
    initText();
    initVariables();
    initBackground();
    initPauseMenu();
    initTileSheet();
    initButtons();
    initGui();
    initView();
}
EditorState::~EditorState() {
    delete this->pmenu;
    delete tileMap;
}
// initialiazer functions
void EditorState::initButtons() {}
void EditorState::initVariables() {
    textureRect=sf::IntRect(0,0,stateData.tileSize,stateData.tileSize);
    this->collision=false;
    this->type=tileTypes::DEFAULT;
    cameraSpeed=500.f;
}
void EditorState::initBackground() {}
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
    if(!font.loadFromFile("assets/fonts/Amarante.ttf"))
    {
        throw("ERROR::EDITORSTATE::COULD NOT LOAD FONT");
    }
}
void EditorState::initText() {
    //used to know positioning of mouse
    cursorText.setPosition(mouseposView.x,mouseposView.y-50.f);
    cursorText.setFillColor(sf::Color::White);
    cursorText.setFont(font);
    cursorText.setCharacterSize(12);

}

void EditorState::initPauseMenu() {
    this->pmenu=new PauseMenu(*window,this->font);
    this->pmenu->addButton("QUIT",800.f,"Quit");
    this->pmenu->addButton("SAVE",300.f,"Save");
    this->pmenu->addButton("LOAD",500.f,"Load");
}
void EditorState::initTileSheet() {
    this->tileMap=new TileMap(stateData.tileSize,100,100,"assets/tiles/tilesheet1.png");
}
void EditorState::initGui() {
    selectorRect.setSize(sf::Vector2f(stateData.tileSize,stateData.tileSize));
    selectorRect.setOutlineColor(sf::Color::Green);
    selectorRect.setOutlineThickness(1.f);
    selectorRect.setFillColor(sf::Color(255,255,255,150));
    selectorRect.setTexture(tileMap->getTileSheet());
    selectorRect.setTextureRect(textureRect);
}
void EditorState::initView() {
    this->view.setSize(sf::Vector2f(stateData.gxSettings->resolution.width,
                                     stateData.gxSettings->resolution.height));
    this->view.setCenter(stateData.gxSettings->resolution.width/2.f,
                          stateData.gxSettings->resolution.height/2.f);
}
//rendering functions
void EditorState::render(sf::RenderTarget *target) {
    if(!target)
        target=this->window;
    target->setView(view);
    tileMap->render(*target);

    target->setView(this->window->getDefaultView());
    renderButtons(*target);
    renderGui(*target);
    if(paused){
        target->setView(this->window->getDefaultView());
        this->pmenu->render(*target);
    }
}
void EditorState::renderButtons(sf::RenderTarget &target) {
    for(auto &it: this->buttons){
        it.second->render(target);
    }
}
void EditorState::renderGui(sf::RenderTarget &target){
    target.setView(this->view);
    target.draw(this->selectorRect);
    target.setView(this->view);
    target.draw(cursorText);
}
//update functions
void EditorState::updatePMenuButtons() {//for pause state
    if(this->pmenu->isButtonPressed("QUIT"))
        this->endState();
    if(this->pmenu->isButtonPressed("SAVE"))
        this->tileMap->saveToFile("assets/maps/map1.txt");
    if(this->pmenu->isButtonPressed("LOAD"))
        this->tileMap->loadFromFile("assets/maps/map1.txt");
}
void EditorState::updateButtons() {//making them clickable
    for(auto &it: this->buttons){
        it.second->update(this->mouseposView);
    }
}
void EditorState::updateInput(const float &dt) {//switching between pause and unpause
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE")))&& this->getKeyTime()){
        if(!paused)
            this->pauseState();
        else
            this->unpauseState();
    }
}
void EditorState::updateEditorInput(const float &dt) {
    //MOVE VIEW (TEMPORARY)
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_CAMERA_RIGHT")))){
        this->view.move(cameraSpeed*dt,0.f);
    }else  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_CAMERA_LEFT")))){
        this->view.move(-cameraSpeed*dt, 0.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_CAMERA_DOWN")))){
        this->view.move(0,cameraSpeed*dt);
    }else  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_CAMERA_UP")))){
        this->view.move(0.f,-cameraSpeed*dt);
    }

    //add a tile
    if(sf::Mouse::isButtonPressed((sf::Mouse::Left))&&getKeyTime()){
        tileMap->addTile(mousePosGrid.x,mousePosGrid.y,0,textureRect,this->collision,this->type);
    }else if(sf::Mouse::isButtonPressed((sf::Mouse::Right))&&getKeyTime()){
        //remove tile
        tileMap->removeTile(mousePosGrid.x,mousePosGrid.y,0);
    }
    //change tile Texture selected
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && getKeyTime()){
        if(textureRect.left<=700){
            textureRect.left+=100;
        }
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && getKeyTime()){
        if(textureRect.left>=100)
            textureRect.left-=100;
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && getKeyTime()){
        if(textureRect.top==0)
            textureRect.top+=100;
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && getKeyTime()){
        if(textureRect.top==100){
            textureRect.top-=100;
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("TOGGLE_COLLISION")))&& this->getKeyTime()){
        if(this->collision)
            this->collision=false;
        else
            this->collision=true;
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("INCREASE_TYPE")))&& this->getKeyTime()){
        this->type++;
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("DECREASE_TYPE")))&& this->getKeyTime()){
        if(this->type>0)
            this->type--;
    }
}
void EditorState::updateGui(){
    //the selector moves on tiles
    selectorRect.setTexture(tileMap->getTileSheet());
    selectorRect.setTextureRect(textureRect);
    selectorRect.setPosition(mousePosGrid.x*stateData.tileSize,mousePosGrid.y*stateData.tileSize);
    //showing the text next mouse
    cursorText.setPosition(mouseposView.x,mouseposView.y-50.f);
    std::stringstream ss;
    ss<<mouseposView.x<<" "<<mouseposView.y<<
    "\n"<<mousePosGrid.x<<" "<<mousePosGrid.y<<
    "\n"<<textureRect.left<<" "<<textureRect.top<<
    "Collision:"<<this->collision<<
    "\n"<<"type"<<this->type;
    cursorText.setString(ss.str());
}
void EditorState::update(const float &dt) {
    this->updateMousePosition(&view);
    this->updateKeyTime(dt);
    this->updateInput(dt);
    if(!this->paused){//unpaused
        updateButtons();
        updateGui();
        updateEditorInput(dt);
    }else{//paused state
        this->pmenu->update(this->mouseposWindow);
        this->updatePMenuButtons();
    }
}
//other functions
void EditorState::endState() {
    this->quit=true;
    std::cout<<"ending gamestate"<<"\n";
}


