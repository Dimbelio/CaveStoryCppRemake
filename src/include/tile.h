#ifndef _TILE_H
#define _TILE_H

#include "globals.h"

class IO;
struct SDL_Texture;

class Tile{
public:
    Tile();
    Tile(SDL_Texture* tileset, Vector2 size, Vector2 tileSetPosition, Vector2 position);

    void update(int elapsedTime);
    void draw(IO &graph);

protected:

SDL_Texture* _tileset;
Vector2 _size;
Vector2 _tileSetPosition;
Vector2 _position;


};


#endif