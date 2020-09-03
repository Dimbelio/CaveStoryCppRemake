#ifndef _RECTENG_H
#define _RECTENG_H

#include "globals.h"

class Recteng{
public:
    Recteng()=default;

    Recteng(int x , int y , int width , int height):
        _x(x), _y(y), _width(width), _height(height)
    {

    }

const int getCenterX()const {return this->_x + this->_width/2;}
const int getCenterY()const {return this->_y + this->_height/2;}

const int getLeft()const{return this->_x;}
const int getRight()const {return this->_x + this->_width;}

const int getBottom() const {return this->_y + this->_height;}
const int getTop()const {return this->_y;}

const int getWidth() const {return this->_width;}
const int getHeight() const {return this->_height;}

const int getSide(const sides::Side side){
    return 
        side ==sides::LEFT ? this->getLeft():
        side == sides::RIGHT ? this->getRight():
        side ==sides::BOTTOM ? this->getBottom() :
        side ==sides::TOP ? this->getTop():
        sides::NONE;
}

 const bool collidesWith(const Recteng &other) const{
        return
            this->getRight() >=other.getLeft() &&
            this->getLeft() <=other.getRight() &&
            this->getBottom()>= other.getTop() &&
            this->getTop() <= other.getBottom();
 }

 const bool isValidRectangle() const{
     return (this->_x>=0 && this->_y>=0 && this->_width >=0 && this->_height>=0);
 }

const inline Recteng getRect() const {return *this;}

private:
    int _x,_y,_width,_height;

};

#endif