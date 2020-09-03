#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include <map>

class Input{
    public:
    void beginNewFrame();
    void keyUpEvent(const SDL_Event & evnt);
    void keyDownEvent(const SDL_Event &evnt);

    bool wasKeyPressed(SDL_Scancode key);
    bool wasKeyRelease(SDL_Scancode key);
    bool isKeyHold(SDL_Scancode key);

    private:
    std::map<SDL_Scancode, bool> _heldKeys;
    std::map<SDL_Scancode, bool> _pressedKeys;
    std::map<SDL_Scancode, bool> _releaseKeys;

};


#endif