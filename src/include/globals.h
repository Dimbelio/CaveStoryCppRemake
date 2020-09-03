#ifndef _GLOBALS_H
#define _GLOBALS_H

namespace globals{
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    const float SPRITE_SCALE = 2.0f;

}

namespace sides{
    enum Side{
        TOP,
        BOTTOM,
        LEFT,
        RIGHT,
        NONE
    };

    const inline Side getOppositeSide(Side side) {
            return 
                side == TOP ? BOTTOM :
                side == BOTTOM ? TOP :
                side == LEFT ? RIGHT :
                side == RIGHT ? LEFT :
                NONE ;
    }
}

enum Direction{
    LEFT,
    RIGHT,
    UP,
    DOWN
};


class Vector2{
public:
    int x,y;
    Vector2():
        x(0),y(0){}
    
    Vector2(int a , int b) 
        : x(a), y(b){ }
    
    Vector2 zero(){
        return Vector2(0,0);
        
    }

};





#endif