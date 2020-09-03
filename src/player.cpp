#include "include/player.h"
#include "include/IO.h"
#include "include/enemy.h"

namespace player_constants{
    const float WALK_SPEED = 0.2f;
    const float JUMP_SPEED = 0.7f;
    const float GRAVITY = 0.002f;
    const float GRAVITY_CAP = 0.8f;
}


Player::Player(){}

Player::Player(IO &graph, Vector2 spawnPoint):
    animatedSprite(graph,"./content/sprites/MyChar.png", 0 , 0 , 16 ,16,spawnPoint.x , spawnPoint.y, 100)
        , _dx(0), _dy(0), _facing(RIGHT),_grounded(false) ,_lookingUp(false), _lookingDown(false),_maxHealth(3),_currentHealth(3)
{
    graph.loadImage("./content/sprites/MyChar.png");
    this->setupAnimation();
    this->playAnimation("RunRight");

}

void Player::setupAnimation(){
    //first how much pictures, then position of the picture on the line//3rd is how many pixels down it is-y,Name of it, 16 pixels height by 16 width,
    this->addAnimation(1,0,0, "IdleLeft",16,16,Vector2(0,0));
    this->addAnimation(1,0,16,"IdleRight",16,16,Vector2(0,0));
    this->addAnimation(3,0,0,"RunLeft",16,16,Vector2(0,0));
    this->addAnimation(3,0,16,"RunRight",16,16,Vector2(0,0));
    this->addAnimation(1,3,0,"IdleLeftUp",16,16,Vector2(0,0));
    this->addAnimation(1,3,16,"IdleRightUp",16,16,Vector2(0,0));
    this->addAnimation(3,3,0,"RunLeftUp",16,16,Vector2(0,0));
    this->addAnimation(3,3,16,"RunRightUp",16,16,Vector2(0,0));
    this->addAnimation(1,6,0,"LookDownLeft",16,16,Vector2(0,0));
    this->addAnimation(1,6,16,"LookDownRight",16,16,Vector2(0,0));
    this->addAnimation(1,7,0,"LookBackwardsLeft",16,16,Vector2(0,0));
    this->addAnimation(1,7,16,"LookBackwardsRight",16,16,Vector2(0,0));

}

void Player::animationDone(std::string currentAnimation){


}

const float Player::getX()const {return this->_x;}

const float Player::getY()const {return this->_y;}

void Player::update(float elapsedTime)
{
    //Apply gravity
    if(this->_dy <= player_constants::GRAVITY_CAP){
        this->_dy+= player_constants::GRAVITY * elapsedTime;
    }

    //move by dx
    this->_x += this->_dx * elapsedTime;

    //move by DY
    this->_y +=this->_dy*elapsedTime;

    animatedSprite::update(elapsedTime);
}

void Player::draw(IO &graph){
    animatedSprite::draw(graph,this->_x,this->_y);
}

void Player::moveLeft(){
    if(this->_lookingDown && this->_grounded){
        return;
    }
    this->_dx = -player_constants::WALK_SPEED;

    if(this->_lookingUp == false){
        this->playAnimation("RunLeft");
        }
    this->_facing = LEFT;
}

void Player::moveRight(){
        if(this->_lookingDown && this->_grounded){
        return;
    }
    this->_dx = +player_constants::WALK_SPEED;
    if(this->_lookingUp == false){
        this->playAnimation("RunRight");
    }
    this->_facing = RIGHT;
}

void Player::stopMoving(){
    this->_dx = 0.0f;
    if(this->_lookingUp == false && this->_lookingDown == false){
    this->playAnimation(this->_facing == RIGHT ? "IdleRight" : "IdleLeft");
    }

}

void Player::jump(){
    if(this->_grounded){
        this->_dy = 0;
        this->_dy -= player_constants::JUMP_SPEED;
        this->_grounded=false;
    }
}
//void handle slopes collisions

void Player::handleSlopeCollisions(std::vector<Slope> &other){
    for(size_t i = 0 ; i < other.size();i++){
        //Calculate where on the slope the plyers bottom center is touching
        //and use y =mx + b to figure out the y position to place him at
        //First calculate "b" which is the sloe intercept using one of the points (b = y -mx)

        int b = (other.at(i).getP1().y - (other.at(i).getSlope()* fabs(other.at(i).getP1().x)));

        //Get players center x
        int centerX = this->_boundingBox.getCenterX();

        int newY = (other.at(i).getSlope()* centerX) + b - 8;
    
        //Re-position the player to the correct 'y';
        if(this->_grounded){
            this->_y = newY - this->_boundingBox.getHeight();
            this->_grounded= true;
        }
    }

}

void Player::handleDoorCollision(std::vector<Door> &other, Level &level, IO& graph){
        for(size_t i = 0; i<other.size();++i){
            if(this->_grounded && this->_lookingDown){
                level = Level(other.at(i).getDestination(), graph);
                this->_x = level.getPlayerSpawnPoint().x;
                this->_y= level.getPlayerSpawnPoint().y;
                
            }
        }
}

void Player::handleEnemyCollision(std::vector<std::shared_ptr<Enemy>> &other){
    for(size_t i = 0; i<other.size();++i){
        other.at(i)->touchPlayer(this);
    }
}
void Player::gainHealth(int amount){
    _currentHealth +=amount;
}

void Player::handleTileCollisions(std::vector<Recteng> &others){{
    for(size_t i = 0; i<others.size();++i){
        sides::Side collisionSide = Sprite::getCollisionSide(others.at(i));
        if(collisionSide != sides::NONE){
            switch (collisionSide){
                case sides::TOP:
                    this->_dy = 0;
                    this->_y = others.at(i).getBottom()+ 1;
                    if(this->_grounded){
                        //this->stopMoving();
                        this->_dx = 0;
                        this->_x -= this->_facing == RIGHT ? 1.0f : -1.0f;
                    }
                    //this->_y = others.at(i).getBottom() + 1;
                    
                    break;
                case sides::BOTTOM:
                    this->_y = others.at(i).getTop() - this->_boundingBox.getHeight()- 1;
                    this->_dy = 0;
                    this->_grounded = true;
                    break;
                case sides::LEFT:
                    this->_x = others.at(i).getRight() + 1;
                    break;
                case sides::RIGHT:
                    this->_x = others.at(i).getLeft() - this->_boundingBox.getWidth() -1 ;
                    break;
                default:
                break;
            }

            
     
            }
        }

    }
}


void Player::lookUp(){
    this->_lookingUp = true;
    if(this->_dx ==0){
        this->playAnimation(this->_facing == RIGHT ? "IdleRightUp" : "IdleLeftUp");
    }
    else{
        this->playAnimation(this->_facing == RIGHT ? "RunRightUp": "RunLeftUp");
    }
}
void Player::stopLookingUp(){
    this->_lookingUp = false;
}
void Player::lookDown(){
    this->_lookingDown = true;
    if(this->_grounded){
        this->playAnimation(this->_facing == RIGHT ? "LookBackwardsRight": "LookBackwardsLeft");
    }
    else{
        this->playAnimation(this->_facing == RIGHT ? "LookDownRight" : "LookDownLeft");
    }
}
void Player::stopLookingDown(){
    this->_lookingDown=false;
}