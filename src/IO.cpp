#include "include/IO.h"
#include <SDL2/SDL_image.h>
#include "include/globals.h"

//IO class holds all information dealing with graphigs

IO::IO(){
    SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH,globals::SCREEN_HEIGHT,0,&this->_screen,&this->_renderer);
    SDL_SetWindowTitle(this->_screen,"CaveStory");
}

IO::~IO(){
    SDL_DestroyWindow(this->_screen);
    SDL_DestroyRenderer(this->_renderer);

}

SDL_Surface* IO::loadImage(const std::string &filePath)
{
    if(this->_spriteSheets.count(filePath)==0){
        this->_spriteSheets[filePath] = IMG_Load(filePath.c_str());
    }
    return this->_spriteSheets[filePath];
}

void IO::blitSurface(SDL_Texture* text, SDL_Rect* sourceRect, SDL_Rect* destinationRect)
{
    SDL_RenderCopy(this->_renderer,text ,sourceRect,destinationRect);
}

void IO::flip(){
    SDL_RenderPresent(this->_renderer);

}

void IO::clear(){
    SDL_RenderClear(this->_renderer);
}
SDL_Renderer* IO::getRenderer()const{
    return this->_renderer;
}
