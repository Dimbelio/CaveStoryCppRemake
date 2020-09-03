#ifndef _HUD_H
#define _HUD_H

#include "player.h"

class Hud{
public:
    Hud() =default;
    Hud(IO & graph, Player &player);

    void update (int elapsedTime, Player &player);
    void draw (IO &graph);



private:

    Player _player;
    //Health sprites;
    Sprite _healthBarSprite;
    Sprite _healthNumber1;

    Sprite _currentHealthBar;

    //exp Sprite

    Sprite _lvWord;
    Sprite _lvNumber;
    Sprite _xpBar;

    //Weapons Sprite:

    Sprite _slash;
    Sprite _dash;

};

#endif