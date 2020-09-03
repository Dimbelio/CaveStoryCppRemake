#include "include/animatedSprite.h"
#include "include/IO.h"
#include<iostream>



animatedSprite::animatedSprite(){}

animatedSprite::animatedSprite(IO &graph, const std::string &filePath, int sourceX , int sourceY , 
                                int width , int height ,float posX, float posY, float timeToUpdate)
                                :
                                    Sprite(graph,filePath,sourceX,sourceY,width,height,posX,posY),
                                    _timeToUpdate(timeToUpdate),
                                    _currentAnimationOnce(false),
                                    _currentAnimation(" "),
                                    _frameIndex(0),
                                
                                    _timeElapsed(0),
                                    _visible(true)
                                    {}

void animatedSprite::addAnimation(int frames, int x , int y , std::string name , int width , int height, Vector2 offset)
{
    std::vector<SDL_Rect> rectangles;
    for(int i = 0; i<frames; i++){
        SDL_Rect newRect = {(i + x)* width,y , width, height };
        rectangles.push_back(newRect);
    }
    this->_animations.insert(std::pair<std::string, std::vector<SDL_Rect>>(name,rectangles));
    this->_offsets.insert(std::pair<std::string,Vector2>(name,offset));
}

void animatedSprite::resetAnimations(){
    this->_animations.clear();
    this->_offsets.clear();
}

void animatedSprite::playAnimation(std::string animation, bool once){
    this->_currentAnimationOnce = once;
    if(this->_currentAnimation != animation){
        this->_currentAnimation = animation;
        this->_frameIndex = 0;
    }

}

void animatedSprite::setVisible(bool visible){
    this->_visible = visible;
}

void animatedSprite::stopAnimation(){
    this->_frameIndex = 0;
    this->animationDone(this->_currentAnimation);
}

void animatedSprite::update(int elapsedTime){
    Sprite::update();

    this->_timeElapsed += elapsedTime;
    if(this->_timeElapsed > this->_timeToUpdate){
        this->_timeElapsed -= this->_timeToUpdate;
        if(this->_frameIndex < static_cast<signed>(this->_animations[this->_currentAnimation].size() - 1)){
            this->_frameIndex++ ;
        }
        else{
            if(this->_currentAnimationOnce ==true){
                this->setVisible(false);
            }
            this->stopAnimation();
        }
    }
}

void animatedSprite::draw(IO &graph, int x , int y)
{
    
    if(this->_visible){
        SDL_Rect destinationRectangle;
   
        destinationRectangle.x = x + this->_offsets[this->_currentAnimation].x;
        destinationRectangle.y = y + this->_offsets[this->_currentAnimation].y;
        destinationRectangle.w = this->_sourceRect.w * globals::SPRITE_SCALE;
        destinationRectangle.h = this->_sourceRect.h * globals::SPRITE_SCALE;


        SDL_Rect sourceRect = this->_animations[this->_currentAnimation][this->_frameIndex];

        graph.blitSurface(this->_spriteSheet, &sourceRect, &destinationRectangle);

    }
}


void animatedSprite::animationDone(std::string currentAnimation){}
/*
void animatedSprite::setupAnimation(){
    this->addAnimation(3,0,0,"RunLeft",16,16,Vector2(0,0));
    this->addAnimation(3,0,16,"RunRight",16,16,Vector2(0,0));
}
*/