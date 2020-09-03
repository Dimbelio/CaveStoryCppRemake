#ifndef _ANIMATEDTILE_H
#define _ANIMATEDTILE_H

#include "tile.h"
#include <vector>

class IO;


class AnimatedTile: public Tile{
public:
    AnimatedTile() = default;

    AnimatedTile(std::vector<Vector2> tilesetPosition, int duration, SDL_Texture * tileset,Vector2 size, Vector2 position);

    void draw(IO &graph);

    void update(int elapsedTime);

protected:
    int _amountOfTime = 0;
    bool _notDone = false;

private:
    std::vector<Vector2> _tilesetPosition;
    
    int _tileToDraw;
    int _duration;

};

struct AnimatedTileInfo{
    int TilesetsFirstGid;
    int StartTileId;

    std::vector<int> TileId;

    int Duration;


};

#endif