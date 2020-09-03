#include "include/sprite.h"
#include "include/IO.h"

#include "include/globals.h"
#include <algorithm>

Sprite::Sprite(){
}


 Sprite::Sprite(IO &graph, const std::string &filePath, int sourceX , int sourceY , int width, int height, 
                float posX , float posY)
                    :_x(posX), _y(posY)
{
    this->_sourceRect.x = sourceX;
    this->_sourceRect.y = sourceY;
    this->_sourceRect.w = width;
    this->_sourceRect.h = height;

    this->_spriteSheet = SDL_CreateTextureFromSurface(graph.getRenderer(),graph.loadImage(filePath));
    if(this->_spriteSheet == NULL){
        printf("\nError: Unable to load image\n");
    }
    this->_boundingBox = Recteng(this->_x, this->_y, width * globals::SPRITE_SCALE , height * globals::SPRITE_SCALE);
}

Sprite::~Sprite(){

}

void Sprite::draw(IO &graph, int x , int y){
    SDL_Rect destinationRectangle = { x , y , this->_sourceRect.w * static_cast<int>(globals::SPRITE_SCALE),
                                              this->_sourceRect.h * static_cast<int>(globals::SPRITE_SCALE) };
    graph.blitSurface(this->_spriteSheet, & this->_sourceRect, &destinationRectangle);
}

void Sprite::update(){
    this->_boundingBox = Recteng(this->_x, this->_y, 
                this->_sourceRect.w * globals::SPRITE_SCALE, this->_sourceRect.h *globals::SPRITE_SCALE);
}


const Recteng Sprite::getBoundingBox()const {return this->_boundingBox;}


//Determine which side the collision happened on
const sides::Side Sprite::getCollisionSide(Recteng & other)const{

    int amountRight, amountLeft, amountTop, amountBottom;
    amountRight = this->getBoundingBox().getRight() - other.getLeft();
    amountLeft = other.getRight() - this->getBoundingBox().getLeft();
    amountTop = other.getBottom() - this->getBoundingBox().getTop();
    amountBottom = this->getBoundingBox().getBottom() - other.getTop();

    int vals[4] = {abs(amountRight), abs(amountLeft), abs(amountTop), abs(amountBottom)};
    int* lowest = std::min_element(vals,vals+4);

    return 
    *lowest == abs(amountRight) ? sides::RIGHT :
    *lowest == abs(amountLeft) ? sides::LEFT :
    *lowest == abs(amountTop) ? sides::TOP :
    *lowest == abs(amountBottom) ? sides::BOTTOM :
    sides::NONE;
}

 void Sprite::setSourceRectX(int value){
     this->_sourceRect.x = value;
 }
void Sprite::setSourceRectY(int value){
    this->_sourceRect.y = value;
}
void Sprite::setSourceRectWidth(int value){
        this->_sourceRect.w = value;
    }
void Sprite::setSourceRectHeight(int value){
        this->_sourceRect.h=value;
    }