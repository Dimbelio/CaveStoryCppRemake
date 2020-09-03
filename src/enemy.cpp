#include "include/enemy.h"
#include<iostream>

//Base enemy class

Enemy::Enemy(IO &graph, std::string filePath,int sourceX , int sourceY,
            int width, int height, Vector2 spawnPoint, int timeToUpdate)
            : animatedSprite(graph,filePath,sourceX,sourceY,width,height,spawnPoint.x , spawnPoint.y ,timeToUpdate),
            _direction(LEFT),
            _maxHealth(0),
            _currentHeath(0)
            {
                
            }

void Enemy::update(int elapsedTime, Player &player){
    this->animatedSprite::update(elapsedTime);
}

void Enemy::draw(IO &graph){
   this->animatedSprite::draw(graph,this->_x,this->_y);
    
}

Bat::Bat(IO &graph, Vector2 spawnPoint):
    Enemy(graph, "./content/sprites/NpcCemet.png",32,32,16,16,spawnPoint,140),
    _startingX(spawnPoint.x),
    _startingY(spawnPoint.y),
    _shouldMoveUp(false)
    {
        this->setupAnimation();
        this->playAnimation("FlyLeft");
    }

void Bat::update(int elapsedTime,Player &player){
    this->_direction = player.getX()>this->_x ? RIGHT : LEFT;
    this->playAnimation(this->_direction == RIGHT ? "FlyRight": "FlyLeft");

    this->_y += this->_shouldMoveUp ? -.4 : .4;
    if(this->_y > (this->_startingY+30)|| this->_y < (this->_startingY-30)){
        this->_shouldMoveUp= !this->_shouldMoveUp;
    }

    this->Enemy::update(elapsedTime,player);
}

void Bat::draw(IO &graph){
    
    this->Enemy::draw(graph);
}


void Bat::animationDone(std::string currentAnimation){

}

void Bat::setupAnimation(){
    this->addAnimation(3,2,32,"FlyLeft",16,16,Vector2(0,0));
    this->addAnimation(3,2,48,"FlyRight",16,16,Vector2(0,0));

}

void Bat::touchPlayer(Player * player){
    player->gainHealth(-1);
}
