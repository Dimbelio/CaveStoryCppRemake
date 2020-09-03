#ifndef _DOOR_H
#define _DOOR_H

#include "recteng.h"
#include "globals.h"
#include <string>

class Door: public Recteng{
public:
    Door() = default;
    Door(Recteng r, std::string destination):
        Recteng(r.getLeft() * globals::SPRITE_SCALE, r.getTop() * globals::SPRITE_SCALE,
        r.getWidth() * globals::SPRITE_SCALE,r.getHeight()* globals::SPRITE_SCALE),_destination(destination)
    {

    }

    const inline Recteng getRecteng()const {return this->getRect();}

    const inline std::string getDestination() const {return this->_destination;}


private:
std::string _destination;

};


#endif