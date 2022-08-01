#include "PreCompHeaders.h"
#include "GameState.h"
//
//INIT FUNCTIONS
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
            this->keybinds[key]=this->supportedKeys->at(key2);
        }
    }
    ifs.close();
}
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
    delete player;
    delete this->pmenu;
    delete tileMap;

}
//
//RENDER FUNCTIONS
void GameState::render(sf::RenderTarget* target) {
    if(!target)
        target= window;

    renderTexture.clear();
    renderTexture.setView(view);
    tileMap->render(renderTexture,false, player);
    player->render(renderTexture,false);
    if(paused)
    {
        renderTexture.setView(renderTexture.getDefaultView());
        pmenu->render(renderTexture);
    }
    //FINAL RENDER
    this->renderTexture.display();
    renderSprite.setTexture(this->renderTexture.getTexture());
    target->draw(this->renderSprite);
}
//
//UPDATE FUNCTIONS
void GameState::updatePlayerInput(const float &dt) {
    //Update player input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT"))))
        player->move(dt,-1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT"))))
        player->move(dt,1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP"))))
        player->move(dt,0.f, -1.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN"))))
        player->move(dt,0.f, 1.f);
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT"))) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT")))
    && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP"))) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN")))) {
        player->stopVelocity();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        player->getWeapon().shoot(mouseposView,dt);
        //bullets.emplace_back(4.f,500.f,player->getWeapon().getMuzzlePosition());
    }
}
void GameState::updatePlayer(const float & dt) {
    player->update(dt,mouseposView);
}
void GameState::updateInput(const float &dt) {
    //pause& unpause
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeyTime()){
        if(!paused)
            pauseState();
        else
            unpauseState();
    }
}
void GameState::updateView(const float &dt) {
    view.setCenter(std::floor(player->getPosition().x+(static_cast<float>(this->mouseposWindow.x)-static_cast<float>(stateData.gxSettings->resolution.width/2))/5.f),
                         std::floor(player->getPosition().y+(static_cast<float>(this->mouseposWindow.y)-static_cast<float>(stateData.gxSettings->resolution.height/2))/5.f));

    if(view.getCenter().x - view.getSize().x/2.f<0.f)
        view.setCenter(0.f + view.getSize().x/2.f,view.getCenter().y);
    else if(view.getCenter().x - view.getSize().x/2.f>tileMap->getMapSizeF().x)
        view.setCenter(tileMap->getMapSizeF().x- view.getSize().x/2.f,view.getCenter().y);
    if(view.getCenter().y - view.getSize().y/2.f<0.f)
        view.setCenter(view.getCenter().x,0.f + view.getSize().y/2.f);
    else if(view.getCenter().y - view.getSize().y/2.f>tileMap->getMapSizeF().y)
        view.setCenter(view.getCenter().x,0.f +tileMap->getMapSizeF().y- view.getSize().x);

    viewGridPos.x=static_cast<int>(view.getCenter().x/stateData.tileSize);
    viewGridPos.y=static_cast<int>(view.getCenter().y/stateData.tileSize);
}
void GameState::updateTileMap(const float &dt) {
    tileMap->update();
    tileMap->updateCollision(player,dt);
}
void GameState::update(const float& dt) {
    updateMousePosition(&view);
    updateKeyTime(dt);
    updateInput(dt);
    if(!paused){
        updatePlayerInput(dt);
        updatePlayer(dt);
        updateTileMap(dt);
        updateView(dt);
    }else{//paused state
        pmenu->update(mouseposWindow);
        updatePMenuButtons();
    }
}
void GameState::updatePMenuButtons() {
    //quit from state
    if(this->pmenu->isButtonPressed("QUIT"))
        endState();
}

void GameState::endState() {
    quit=true;
    std::cout<<"ending gamestate"<<"\n";
}




