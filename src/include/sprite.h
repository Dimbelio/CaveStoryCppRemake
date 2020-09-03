#ifndef _SPRITE_H
#define _SPRITE_H

#include <string>
#include <SDL2/SDL.h>
class IO;
#include "recteng.h"



// Holds all info for individual sprites;

class Sprite{
public:
    Sprite();
    Sprite(IO &graph, const std::string &filePath, int sourceX , int sourceY , int width, int heigh, float posX , float posY);

    virtual ~Sprite();
    virtual void update();
    void draw(IO &graph , int x , int y);

    const Recteng getBoundingBox() const;
    const sides::Side getCollisionSide(Recteng & other) const;


    const inline int getX()const { return this->_x;}
    const inline int getY() const{return this->_y;}
    void setSourceRectX(int value);
    void setSourceRectY(int value);
    void setSourceRectWidth(int value);
    void setSourceRectHeight(int value);

protected:

    SDL_Rect _sourceRect;
    SDL_Texture* _spriteSheet;

    Recteng _boundingBox;
      float _x , _y;
      
private:
   

};

#endif