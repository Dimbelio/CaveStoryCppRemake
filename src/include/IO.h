#ifndef IO_H
#define IO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <map>
#include <string>

class IO{
public:
    IO();
    ~IO();

//SDL_Surface* loadImage -- it loads image into the spriteSheets map if it doesn`t already exist
//As a result each image will only be loaded once.
//returns the image from the map regadless of whether or not it was just loaded
SDL_Surface* loadImage( const std::string &filePath);

//blitSurface will draw images to the certain part of the screen
// source is what image we want to draw, sourceRectangle is where on the image is our exact image 
//destinationRectangle is where we want to draw it on the screen
void blitSurface(SDL_Texture* source, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle);

//void flip renders everything to the screen;
void flip();

//clears the screen
void clear();

//Returns the renderer- _renderer
SDL_Renderer* getRenderer() const;

private:
 SDL_Window* _screen;
 SDL_Renderer* _renderer;
 std::map<std::string, SDL_Surface*> _spriteSheets;

};



#endif