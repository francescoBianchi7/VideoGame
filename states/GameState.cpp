//
// Created by bianc on 05/12/2021.
//
#include "PreCompHeaders.h"
#include "GameState.h"

void GameState::initDelayedRender() {
    renderTexture.create(stateData.gxSettings->resolution.width,
                         stateData.gxSettings->resolution.height);//empty texture size of window
    renderSprite.setTexture(renderTexture.getTexture());
    this->renderSprite.setTextureRect(sf::IntRect(0,0,
                                                  static_cast<int>(stateData.gxSettings->resolution.width),
                                                  static_cast<int>(stateData.gxSettings->resolution.height)));
}
void GameState::initView() {
    this->view.setSize(sf::Vector2f(static_cast<float>(stateData.gxSettings->resolution.width),
                                    static_cast<float>(stateData.gxSettings->resolution.height)));
    this->view.setCenter(sf::Vector2f(static_cast<float>(stateData.gxSettings->resolution.width)/2.f,
                                      static_cast<float>(stateData.gxSettings->resolution.height)/2.f));

}
void GameState::initKeybinds() {
    /*this function permits to assign the keybinds for a state based on
     * the available supportedkeys,by reading them from a file
     * e.g. the main menu(or whatever it's going to be called) state can have different
     * keybinds */
    std::ifstream ifs("./config/gamestate_keybinds.ini");
    if(ifs.is_open()){
        std::string key=" ";
        std::string key2=" ";
        while(ifs >> key >> key2){
            keybinds[key]=this->supportedKeys->at(key2);
        }
    }
    ifs.close();
}
//
//INIT FUNCTIONS
void GameState::initFonts() {
    if(!this->font.loadFromFile("assets/fonts/Amarante.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
    }
}
void GameState::initTextures() {
    if(!this->textures["PLAYER_SHEET"].loadFromFile("./assets/Sprites/GC/GC_Sheet.png"))
        throw "ERROR::GAME_STATE::COULDNOTLOADIDLETEXTURE";
}
void GameState::initPlayer() {
    player= new GameCharacter(1, 1, this->textures["PLAYER_SHEET"]);
}
void GameState::initPauseMenu() {
    pmenu=new PauseMenu(*window,this->font);
    pmenu->addButton("QUIT",800.f,"Quit");
}
void GameState::initTileMap() {
    tileMap=new TileMap(stateData.tileSize, 100, 100, "./assets/tiles/tilesheet1.png"); /*normal tileshhet*/
    //tileMap= new TileMap(stateData.tileSize, 6, 6, "Google_tests/gtest_assets/GrassTestTile.png"); /*test tile sheet and size for tile collision test*/
    //tileMap= new TileMap(stateData.tileSize, 4, 4, "Google_tests/gtest_assets/GrassTestTile.png"); /*test tile sheet and size for world bounds test*/
    tileMap->loadFromFile("./assets/maps/map1.txt"); /*normal map*/
    //tileMap->loadFromFile("Google_tests/gtest_assets/tileCollisionTestMap.txt"); /*tile collision test*/
    //tileMap->loadFromFile("Google_tests/gtest_assets/worldboundTestMap.txt"); /* world bounds test*/
}
//CON & DES
GameState::GameState(StateData &stateData)
:State(stateData){
    initDelayedRender();
    initView();
    initKeybinds();
    initFonts();
    initTextures();
    initPauseMenu();
    initTileMap();
    initPlayer();
}

GameState::~GameState() {
    delete this->player;
    delete this->pmenu;
    delete tileMap;
}
//
//RENDER FUNCTIONS
void GameState::render(sf::RenderTarget* target) {
    if(!target)
        target= this->window;

    this->renderTexture.clear();
    this->renderTexture.setView(this->view);
    tileMap->render(renderTexture, this->player);
    player->render(renderTexture);
    if(paused)
    {
        renderTexture.setView(renderTexture.getDefaultView());
        this->pmenu->render(renderTexture);
    }
    //FINAL RENDER
    this->renderTexture.display();
    renderSprite.setTexture(this->renderTexture.getTexture());
    target->draw(this->renderSprite);
}
//
//UPDATE FUNCTIONS
void GameState::updatePlayerInput(const float &dt) {
    player->update(dt);
}
void GameState::updateView(const float &dt) {
    this->view.setCenter(std::floor(player->getPosition().x),std::floor(player->getPosition().y));
}
void GameState::updateTileMap(const float &dt) {
    tileMap->update();
    tileMap->updateCollision(player,dt);
}
void GameState::update(const float& dt) {
    updateMousePosition(&view);
    updateKeyTime(dt);
    updateInput(dt);
    if(!this->paused){
        this->updateView(dt);
        this->updatePlayerInput(dt);
        player->update(dt);
        this->updateTileMap(dt);
    }else{//paused state
        pmenu->update(this->mouseposWindow);
        this->updatePMenuButtons();
    }
}
void GameState::updateInput(const float &dt) {
    //pause& unpause
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeyTime()){
        if(!paused)
            this->pauseState();
        else
            this->unpauseState();
    }
}
void GameState::updatePMenuButtons() {
    //quit from state
    if(this->pmenu->isButtonPressed("QUIT"))
        this->endState();
}

void GameState::endState() {
    this->quit=true;
    std::cout<<"ending gamestate"<<"\n";
}



