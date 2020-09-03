#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "level.h"
#include "hud.h"
#include "IO.h"



class Game{
public:
    Game();
    ~Game();

private:
    void gameLoop();
    void draw(IO &graphics);
    void update(float elapsedTime);


    Player _player;
    Level _level;
    Hud _hud;

    IO _graph;
};


#endif