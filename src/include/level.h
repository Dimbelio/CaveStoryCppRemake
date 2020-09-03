#ifndef _LEVEL_H
#define _LEVEL_H


#include "slope.h"
#include "animatedTile.h"
#include "door.h"
#include <vector>
#include <memory>


struct Tileset;
class Enemy;
struct SDL_Rect;
class IO;
struct SDL_Texture;
class Player;
class Bat;

class Level{
public:
    Level();
    Level(std::string mapname, IO &graph);
    ~Level();
    void update(int elapsedTime, Player& player);
    void draw (IO &graph);

    std::vector<Recteng> checkTileCollision(const Recteng & other);
    std::vector<Slope> checkSlopeCollision(const Recteng & other);

    std::vector<Door> checkDoorCollision(const Recteng& other);

    std::vector<std::shared_ptr<Enemy>> checkEnemyCollision(const Recteng&other);


    const Vector2 getPlayerSpawnPoint()const;

private:
    std::string _mapName;
    Vector2 _spawnPoint;

    Vector2 _size;
    Vector2 _tileSize;

    SDL_Texture* _backGroundTexture;
    
    //all tiles on the map
    std::vector<Tile> _tileList;
    
    std::vector<Tileset> _tilesets;
    
    std::vector<Recteng> _collisionRects;

    std::vector<Slope> _slopes;

    std::vector<AnimatedTile> _animatedTileList;

    std::vector<AnimatedTileInfo> _animatedTileInfos;

    std::vector<Door> _doorList;

    std::vector<std::shared_ptr<Enemy>> _enemies;
    
    //we will call it only from level class itself.

    void loadMap(std::string mapname, IO &graph);

Vector2 getTilesetPosition(Tileset tls, int j , int tileWidth, int tileHeight,std::vector<int> vect);

};

struct Tileset{
    SDL_Texture* texture;

    int FirstGid;
    Tileset(){
        this->FirstGid = -1;
    }

    Tileset(SDL_Texture *text, int firstGid){
        this->texture = text;
        this->FirstGid = firstGid;
    }

    

};


#endif