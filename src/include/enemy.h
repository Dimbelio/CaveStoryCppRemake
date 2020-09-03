#ifndef _ENEMY_H
#define _ENEYM_H

#include "player.h"


class Enemy: public animatedSprite{
public:
    Enemy() = default;
    Enemy(IO & graph , std::string filepath, int sourceX , int sourceY, 
    int width, int height,Vector2 spawnPoint, int timeToUpdate);

    virtual void update(int elapsedTime, Player &player);
    virtual void draw(IO &graph);

    virtual void touchPlayer(Player* player)= 0;

    const inline int getMaxHealth() const {return this->_maxHealth;}
    const inline int getCurrentHealt() const {return this->_currentHeath;}


protected:
    Direction _direction;
    int _maxHealth;
    int _currentHeath;

};

class Bat: public Enemy{
public:
    Bat() =default;

    Bat(IO &graph,Vector2 spawnPoint);

    void update(int elapsedTime,Player &player) override;

    void draw(IO &graph) override;

    void animationDone(std::string currentAnimation);
    void setupAnimation();

    void touchPlayer(Player* player);

private:
    float _startingX , _startingY;
    bool _shouldMoveUp;

};


#endif