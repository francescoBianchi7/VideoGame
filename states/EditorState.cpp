//
// Created by bianc on 09/02/2022.
//

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
    textureRect=sf::IntRect(0,0,static_cast<int>(stateData.tileSize),static_cast<int>(stateData.tileSize));
    this->type=tileTypes::DEFAULT;
    cameraSpeed=500.f;
    layer=0;
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
    tileMap=new TileMap(stateData.tileSize, 50, 50, "./assets/tiles/tilesheet1.png"); //normal game map
    //tileMap=new TileMap(stateData.tileSize, 4, 4, "Google_tests/gtest_assets/GrassTestTile.png"); /*test tile sheet and size for world-bounds test*/
    //tileMap=new TileMap(stateData.tileSize, 6, 6, "Google_tests/gtest_assets/GrassTestTile.png"); /*test tile sheet and size for tile collision test*/
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
    view.setSize(sf::Vector2f(static_cast<float>(stateData.gxSettings->resolution.width),
                                    static_cast<float>(stateData.gxSettings->resolution.height)));
    view.setCenter(static_cast<float>(stateData.gxSettings->resolution.width)/2.f,
                         static_cast<float>(stateData.gxSettings->resolution.height)/2.f);
}
//rendering functions
void EditorState::render(sf::RenderTarget *target) {
    if(!target)
        target=window;
    target->setView(view);
    tileMap->render(*target,mousePosGrid,true);

    target->setView(window->getDefaultView());
    renderButtons(*target);
    renderGui(*target);
    if(paused){
        target->setView(window->getDefaultView());
        pmenu->render(*target);
    }
}
void EditorState::renderButtons(sf::RenderTarget &target) {
    for(auto &it: this->buttons){
        it.second->render(target);
    }
}

void EditorState::renderGui(sf::RenderTarget &target){
    target.setView(view);
    target.draw(selectorRect);
    target.setView(view);
    target.draw(cursorText);
}
//update functions
void EditorState::updatePMenuButtons() {//for pause state
    if(pmenu->isButtonPressed("QUIT"))
        endState();
    if(pmenu->isButtonPressed("SAVE"))
        tileMap->saveToFile("assets/maps/map1.txt"); //normal map
        //tileMap->saveToFile("Google_tests/gtest_assets/worldboundTestMap.txt");
        //tileMap->saveToFile("Google_tests/gtest_assets/tileCollisionTestMap.txt");
    if(pmenu->isButtonPressed("LOAD"))
        tileMap->loadFromFile("assets/maps/map1.txt");
        //tileMap->loadFromFile("Google_tests/gtest_assets/worldboundTestMap.txt");
        //tileMap->loadFromFile("Google_tests/gtest_assets/tileCollisionTestMap.txt");
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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("TOGGLE_COLLISION")))&& getKeyTime()){
        if(this->collision)
            this->collision=false;
        else
            this->collision=true;
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("INCREASE_TYPE")))&& getKeyTime()){
        this->type++;
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("DECREASE_TYPE")))&& getKeyTime()){
        if(this->type>0)
            this->type--;
    }
}
void EditorState::updateGui(){
    //the selector moves on tiles
    selectorRect.setTexture(tileMap->getTileSheet());
    selectorRect.setTextureRect(textureRect);
    selectorRect.setScale(1/2.f,1/2.f);
    selectorRect.setPosition(static_cast<float>(mousePosGrid.x)*stateData.tileSize/2.f,
                             static_cast<float>(mousePosGrid.y)*stateData.tileSize/2.f);
    //showing the text next mouse
    cursorText.setPosition(mouseposView.x,mouseposView.y-50.f);
    std::stringstream ss;
    ss<<mouseposView.x<<" "<<mouseposView.y<<
    "\n"<<mousePosGrid.x<<" "<<mousePosGrid.y<<
    "\n"<<textureRect.left<<" "<<textureRect.top<<
    "Collision:"<<this->collision<<
    "\n"<<"Enemytype"<<this->type<<
    "\n"<<"Tiles"<<tileMap->getLayerSize(mousePosGrid.x,mousePosGrid.y,layer);
    cursorText.setString(ss.str());
}
void EditorState::update(const float &dt) {
    updateMousePosition(&view);
    updateKeyTime(dt);
    updateInput(dt);
    if(!paused){//unpaused
        updateButtons();
        updateGui();
        updateEditorInput(dt);
    }else{//paused state
        pmenu->update(this->mouseposWindow);
        updatePMenuButtons();
    }
}
//other functions
void EditorState::endState() {
    this->quit=true;
    std::cout<<"ending gamestate"<<"\n";
}


