#ifndef _ANIMATEDSPRITE_H
#define _ANIMATEDSPRITE_h

#include "sprite.h"
#include <vector>
#include <map>
#include "globals.h"

class IO;


class animatedSprite: public Sprite{
public:
    animatedSprite();
    animatedSprite(IO &graph, const std::string &filePath, int sourceX, int sourceY ,int width,int height
                    ,float posX, float posY, float timeToUpdate);
    
    //playAnimation - plays the animation if it is not already playing
    void playAnimation(std::string animation, bool once=false);

    void update(int elapsedTime);

    void draw(IO &graph, int x , int y);

//  a required function that sets up all animations for a sprite
    

protected:
   double _timeToUpdate;
   bool _currentAnimationOnce;
   std::string _currentAnimation;
   
   //Adds animation to the map of animations for the sprite
   void addAnimation(int frames,int x , int y,std::string name, int width , int height,Vector2 offset);

   void resetAnimations();

   void stopAnimation();

//changes visibility of the animated sprite
    void setVisible(bool visible);

    //logic that happens when animation ends
    virtual void animationDone(std::string currentAnimation) = 0;
//  a required function that sets up all animations for a sprite
    virtual void setupAnimation() = 0;

private:
    std::map<std::string, std::vector<SDL_Rect>> _animations;
    std::map<std::string, Vector2> _offsets;


    int _frameIndex;
    double _timeElapsed ;
    bool _visible;

};

#endif