#include "TileMap.h"
void TileMap::clear() {
    for(size_t x=0;x<this->mapSizeGrid.x; x++){
        for(size_t y=0;y<this->mapSizeGrid.y; y++){
            for(size_t z=0;z<this->layers;z++){
                for(size_t k=0;k<map[x][y][z].size();k++){
                    delete map[x][y][z][k];
                    map[x][y][z][k]= nullptr;
                }
            }
            map[x][y].clear();
        }
        map[x].clear();
    }
    map.clear();
}

TileMap::TileMap(float tileSize,unsigned width,unsigned height,std::string texture_file) {
    tileSizeF=tileSize/2.f;
    tileSizeI=static_cast<int>(tileSizeF);
    mapSizeGrid.x=width;
    mapSizeGrid.y=height;
    mapSizeF.x= static_cast<float>(width) * tileSizeF;
    mapSizeF.y= static_cast<float>(height) * tileSizeF;
    layers=2;
    textureFile=texture_file;
    map.resize(mapSizeGrid.x, std::vector<std::vector<std::vector<Tile*>>>());
    //prob going to be changed later really inefficient
    for(size_t x=0;x<mapSizeGrid.x; x++){
        for(size_t y=0;y<mapSizeGrid.y; y++){
            map[x].resize(mapSizeGrid.y, std::vector<std::vector<Tile*>>());
            for(size_t z=0;z<layers;z++){
                map[x][y].resize(layers, std::vector<Tile*>());
            }
        }
    }
    if(!tileTextureSheet.loadFromFile(texture_file))
        std::cout<<"ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET"<<texture_file<<"\n";

    collisionBox.setSize(sf::Vector2f(tileSizeF,tileSizeF));
    collisionBox.setFillColor(sf::Color(255,0,0,50));
    collisionBox.setOutlineColor(sf::Color::Red);
    collisionBox.setOutlineThickness(-1.f);

    spawnerTileBox.setSize(sf::Vector2f(tileSizeF,tileSizeF));
    spawnerTileBox.setFillColor(sf::Color(0,0,255,50));
    spawnerTileBox.setOutlineColor(sf::Color::Blue);
    spawnerTileBox.setOutlineThickness(-1.f);
}

TileMap::~TileMap() {
    for(size_t x=0;x<mapSizeGrid.x; x++){
        for(size_t y=0;y<mapSizeGrid.y; y++){
            for(size_t z=0;z<this->layers;z++){
                for(auto & k : map[x][y][z]){
                    delete k;
                }
            }
        }
    }
}

//getter
const sf::Texture *TileMap::getTileSheet() {
    return &this->tileTextureSheet;
}
sf::Vector2i TileMap::getMapSizeI() const {
    return mapSizeGrid;
}
sf::Vector2f TileMap::getMapSizeF() const {
    return mapSizeF;
}
int TileMap::getLayerSize(int x, int y, int layer) const {
    if(x>=0 && x<map.size()){
        if(y>=0 && y<map[x].size()){
            if(layer>=0 && layer<map[x][y].size()){
                return map[x][y][layer].size();
            }
        }
    }
    return -1;
}
bool TileMap::tileEmpty(int x, int y, int z) {
    if(x>=0 && x<=mapSizeF.x &&
    y>=0 && y<=mapSizeF.y &&
    z>0)
        return map[x][y][z].empty();
    else
        return false;
}

void TileMap::addTile(unsigned x,unsigned y,unsigned z,sf::IntRect& textureRect,bool& collision,short& type) {
    //adds a tile where the mouse is,if the mouse is inside the array
    if(x < mapSizeGrid.x && x >= 0 && y < mapSizeGrid.y && y >= 0 && z < layers && z >= 0){
            map[x][y][z].push_back(new DefaultTile(type,x,y,tileSizeF,tileTextureSheet,textureRect,collision));
        //std::cout<<"DEBUG::ADDED TILE";
    }
}
void TileMap::addTile(unsigned int x, unsigned int y, unsigned int z, sf::IntRect &textureRect, int enemy_type,
                      int enemy_amount, int enemy_tts) {
    if(x < mapSizeGrid.x && x >= 0 && y < mapSizeGrid.y && y >= 0 && z < layers && z >= 0){
        map[x][y][z].push_back(new EnemySpawner(x,y,tileSizeF,tileTextureSheet,textureRect,enemy_type,enemy_amount,enemy_tts));
        //std::cout<<"DEBUG::ADDED TILE";
    }

}
void TileMap::removeTile(unsigned x,unsigned y,unsigned z) {
    //remove if a tile is present
    if(x < mapSizeGrid.x && x >= 0 && y < mapSizeGrid.y && y >= 0 && z < layers && z >= 0){
        if(!map[x][y][z].empty()){//can remove
            delete map[x][y][z][map[x][y][z].size()-1];
            map[x][y][z].pop_back();
            std::cout<<"DEBUG::REMOVED TILE";
        }
    }
}

void TileMap::render(sf::RenderTarget & target,sf::Vector2i gridPosition,const bool showCollision) {
        layer=0;
        fromX=gridPosition.x - 14;
        if(fromX<0)
            fromX=0;
        else if(fromX>mapSizeGrid.x)
            fromX=static_cast<int>(mapSizeGrid.x);

        toX=gridPosition.x + 18;
        if(toX<0)
            toX=0;
        else if(toX>mapSizeGrid.x)
            toX=static_cast<int>(mapSizeGrid.x);

        this->fromY=gridPosition.y - 15;
        if(this->fromY<0)
            this->fromY=0;
        else if(fromY>mapSizeGrid.y)
            fromY=static_cast<int>(mapSizeGrid.y);

        this->toY=gridPosition.y + 20;
        if(toY<0)
            toY=0;
        else if(toY>mapSizeGrid.y)
            toY=static_cast<int>(mapSizeGrid.y);

        for(size_t x=fromX;x<toX;x++){
            for(size_t y=fromY;y<toY;y++){
                for (auto & k : map[x][y][layer]){
                    //if(z){//if this is not null I render, helps with memory
                    k->render(target);
                    if(showCollision){
                        if(k->getCollision()){
                            collisionBox.setPosition(k->getPosition());
                            target.draw(collisionBox);
                        }
                    }
                    if(k->getType()==tileTypes::ENEMYSPAWNER){
                        spawnerTileBox.setPosition(k->getPosition());
                        target.draw(spawnerTileBox);
                    }
                }
            }
        }
}

void TileMap::updateWorldBoundsCollision(Entity *entity, const float &dt) const {
    //WORlD BOUNDS
    std::cout<<"mapsizes"<<mapSizeF.y<<","<<mapSizeGrid.y<<"\n";
    std::cout<<"mapPosition"<<entity->getPosition().y<<","<<entity->getGridPosition(tileSizeI).y<<"\n";
    if(entity->getPosition().x<0.f)
        entity->setPosition(0.f,entity->getPosition().y);
    else if(entity->getPosition().x + entity->getGlobalBounds().width>mapSizeF.x/2.f)
        entity->setPosition(mapSizeF.x/2.f - entity->getGlobalBounds().width, entity->getPosition().y);
    if(entity->getPosition().y<0.f)
        entity->setPosition(entity->getPosition().x,0.f);
    else if(entity->getPosition().y+entity->getGlobalBounds().height>mapSizeF.y/2.f)
        entity->setPosition(entity->getPosition().x, mapSizeF.y/2.f - entity->getGlobalBounds().height);
}

void TileMap::updateTiles(Entity *entity, const float &dt,std::vector<Enemy*>& activeEnemies,std::map<std::string, sf::Texture>& textures) {
    this->layer=0;
    this->fromX=entity->getGridPosition(this->tileSizeI).x - 14;
    if(this->fromX<0)
        this->fromX=0;
    else if(fromX>mapSizeGrid.x)
        fromX=static_cast<int>(mapSizeGrid.x);

    this->toX=entity->getGridPosition(this->tileSizeI).x + 18;
    if(toX<0)
        toX=0;
    else if(toX>mapSizeGrid.x)
        toX=static_cast<int>(mapSizeGrid.x);

    this->fromY=entity->getGridPosition(this->tileSizeI).y - 15;
    if(this->fromY<0)
        this->fromY=0;
    else if(fromY>mapSizeGrid.y)
        fromY=static_cast<int>(mapSizeGrid.y);

    this->toY=entity->getGridPosition(this->tileSizeI).y + 20;
    if(toY<0)
        toY=0;
    else if(toY>mapSizeGrid.y)
        toY=static_cast<int>(mapSizeGrid.y);
    sf::FloatRect entityBounds=entity->getGlobalBounds();
    sf::FloatRect nextPosition=entity->getNextPositionBounds(dt);

    for(size_t x=fromX;x<this->toX;x++){
        for(size_t y=fromY;y<this->toY;y++){
            for (auto & k : map[x][y][layer]){
                k->update();
                if(k->getType()==tileTypes::ENEMYSPAWNER){
                    auto* es=dynamic_cast<EnemySpawner*>(k);
                    if(!es->getSpawned()){
                        activeEnemies.push_back(new BaldZombie(x*tileSizeF,y*tileSizeF,textures["ZOMBIE_SHEET"]));
                        es->setSpawned(true);
                    }
                }
            }
        }
    }
}

void TileMap::updateTileCollision(Entity *entity, const float &dt) {
    this->layer=0;
    this->fromX=entity->getGridPosition(this->tileSizeI).x - 1;
    if(this->fromX<0)
        this->fromX=0;
    else if(fromX>mapSizeGrid.x)
        fromX=static_cast<int>(mapSizeGrid.x);

    this->toX=entity->getGridPosition(this->tileSizeI).x + 5;
    if(toX<0)
        toX=0;
    else if(toX>mapSizeGrid.x)
        toX=static_cast<int>(mapSizeGrid.x);

    this->fromY=entity->getGridPosition(this->tileSizeI).y - 2;
    if(this->fromY<0)
        this->fromY=0;
    else if(fromY>mapSizeGrid.y)
        fromY=static_cast<int>(mapSizeGrid.y);

    this->toY=entity->getGridPosition(this->tileSizeI).y + 5;
    if(toY<0)
        toY=0;
    else if(toY>mapSizeGrid.y)
        toY=static_cast<int>(mapSizeGrid.y);
    sf::FloatRect entityBounds=entity->getGlobalBounds();
    sf::FloatRect nextPosition=entity->getNextPositionBounds(dt);

    for(size_t x=fromX;x<this->toX;x++){
        for(size_t y=fromY;y<this->toY;y++){
            for (size_t k=0;k<map[x][y][layer].size();k++){
                map[x][y][layer][k]->update();

                sf::FloatRect wallBounds=this->map[x][y][layer][k]->getGlobalBounds();
                if(this->map[x][y][layer][k]->getCollision()
                && this->map[x][y][layer][k]->intersects(nextPosition)){
                    //Right collision
                    if(entity->getVelocity().x>0){
                        entity->setPosition(wallBounds.left - entityBounds.width, entityBounds.top);
                        std::cout<<" "<<entityBounds.top<<" ,"<<entityBounds.left<<"\n";
                    }
                    //Left collision
                    if (entity->getVelocity().x<0){
                        std::cout<<"left collision"<<entityBounds.top<<" ,"<<entityBounds.left<<"\n";
                        std::cout<<"left collision"<<entityBounds.top<<" ,"<<entityBounds.left<<"\n";
                        entity->setPosition(wallBounds.left + wallBounds.width, entityBounds.top);
                        std::cout<<" "<<entityBounds.top<<" ,"<<entityBounds.left<<"\n";
                    }
                    //Bottom collision
                    if (entity->getVelocity().y>0){
                        std::cout<<"bot collision"<<static_cast<int>(entityBounds.top)<<", "<<static_cast<int>(entityBounds.left);
                        entity->setPosition(static_cast<int>(entityBounds.left), static_cast<int>(wallBounds.top-entityBounds.height));
                        std::cout<<static_cast<int>(entityBounds.top)<<", "<<static_cast<int>(entityBounds.left)<<"\n";
                    }
                    //Top collision
                    if (entity->getVelocity().y<0){
                        std::cout<<"top collision"<<entityBounds.top<<" ,"<<entityBounds.left;
                        entity->setPosition(entityBounds.left, wallBounds.top + wallBounds.height);
                        std::cout<<" "<<entityBounds.top<<", "<<entityBounds.left<<"\n";
                    }
                }
            }
        }
    }
}

void TileMap::update(Entity *entity, const float &dt) {
    updateWorldBoundsCollision(entity,dt);
    //TILE COLLISION
    /*setting up for loop;should find a better way to this*/

}

void TileMap::saveToFile(const std::string &file_name) {
//saves the tile maps to a text file
// Format: Size x,y tileSize
//pos x,y textureRect Enemytype
    std::ofstream out_file;
    out_file.open(file_name);
    if(out_file.is_open()){
        out_file << mapSizeGrid.x << " " << mapSizeGrid.y << "\n"
                 << tileSizeI << "\n"
        <<layers<<"\n"
        <<textureFile<<"\n";
        for(size_t x=0;x<mapSizeGrid.x; x++){
            for(size_t y=0;y<mapSizeGrid.y; y++){
                for(size_t z=0;z<layers;z++){
                    if(!this->map[x][y][z].empty()){
                        for(size_t k=0;k<map[x][y][z].size();k++)
                            out_file<<x<<" "<<y<<" "<<z<<" "<<map[x][y][z][k]->getAsString()<<"\n";//MAKE sure last space isn't saved
                    }
                }
            }
            std::cout<<"saved";
        }
    }else{
        std::cout<<"ERROR::COULD NOT SAVE FILE,"<<file_name;
        out_file.close();
    }
}
void TileMap::loadFromFile(const std::string& file_name) {
    std::ifstream in_file;
    in_file.open(file_name);

    if(in_file.is_open()){
        sf::Vector2i size;
        int tileSize=0;
        layers=0;
        std::string texture_file;
        unsigned x=0,y=0,z=0,trX=0,trY=0;
        bool collision=false;
        short type=0;
        //basics
        in_file>> size.x >> size.y >> tileSize >> layers >> texture_file;
        //tiles data
        tileSizeF=static_cast<float>(tileSize);
        tileSizeI=tileSize;
        mapSizeGrid.x=size.x;
        mapSizeGrid.y=size.y;
        textureFile=texture_file;
        this->clear();

        map.resize(mapSizeGrid.x, std::vector<std::vector<std::vector<Tile*>>>());
        for(size_t i=0;i<this->mapSizeGrid.x; i++){
            for(size_t j=0;j<this->mapSizeGrid.y; j++){
                map[i].resize(mapSizeGrid.y, std::vector<std::vector<Tile*>>());
                for(size_t z=0;z<layers;z++){
                    map[i][j].resize(layers,std::vector<Tile*>());
                }
            }
        }
        if(!tileTextureSheet.loadFromFile(texture_file))
            std::cout<<"Error";
        //load all tiles
        while(in_file>> x>> y>> z>> type){
            if(type == tileTypes::ENEMYSPAWNER){
                //type amount time to spawn
                int enemy_type =0, enemy_am=0,enemy_tts=0;
                in_file>> trX>> trY>> enemy_type >> enemy_am >> enemy_tts;
                sf::IntRect textureRect=sf::IntRect(trX, trY,tileSizeI*2, tileSizeI*2);
                this->map[x][y][z].push_back(new EnemySpawner(x,y,
                                     tileSizeF,tileTextureSheet,textureRect,
                                     enemy_type,enemy_am,enemy_tts));
                }else{
                    in_file>> trX>> trY>>collision;
                    sf::IntRect textureRect=sf::IntRect(trX, trY,
                                                    tileSizeI*2, tileSizeI*2);
                    this->map[x][y][z].push_back(
                            new DefaultTile(type,x,y,tileSizeF,tileTextureSheet,
                                     textureRect,collision));
                }
            }
    }else{
        std::cout<<"ERROR::COULD NOT LOAD FROM FILE,"<<file_name;
    }
    in_file.close();
}

