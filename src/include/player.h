#ifndef _PLAYER_H
#define _PLAYER_H
#include "animatedSprite.h"
#include "level.h"

class IO;

class Player : public animatedSprite{
public:
    Player();
    Player(IO &graph, Vector2 spawnPoint);
    void draw(IO &graph);
    void update (float elapsedTime);

    //move right by -dx
    void moveLeft();
    //move right by +dx
    void moveRight();
    //Stops moving the player
    void stopMoving();

    void jump();

    void lookUp();
    void stopLookingUp();
    void lookDown();
    void stopLookingDown();


    virtual void animationDone(std::string currentAnimation);
    virtual void setupAnimation();

    void handleTileCollisions(std::vector<Recteng> &others);
    void handleSlopeCollisions (std::vector<Slope> &other);
    void handleDoorCollision(std::vector<Door> &other, Level &level, IO& graph);
    void handleEnemyCollision(std::vector<std::shared_ptr<Enemy>> &other);

    const float getX() const;
    const float getY() const;


    const inline int getMaxHealth() const {return this->_maxHealth;}
    const inline int getCurrentHealth()const {return this->_currentHealth;}
    
    void gainHealth(int amount);

private:
    float _dx, _dy;

    Direction _facing;
    bool _grounded;//true if we are on the ground

    bool _lookingUp;
    bool _lookingDown;

    int _maxHealth;
    int _currentHealth;

};

#endif