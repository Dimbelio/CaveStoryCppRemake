#include "include/input.h"


//Keeps track of keyboard state

//This function is called at the beggining of each frame to reset the keys that are no longer relevent
void Input::beginNewFrame(){
    this->_pressedKeys.clear();
    this->_releaseKeys.clear();

}

//this gets called when a key is pressed;
void Input::keyDownEvent(const SDL_Event &evnt){
    this->_pressedKeys[evnt.key.keysym.scancode] = true;
    this->_heldKeys[evnt.key.keysym.scancode] = true;

}
//this gets called when a key is release
void Input::keyUpEvent(const SDL_Event &evnt){
    this->_releaseKeys[evnt.key.keysym.scancode] = true;
    this->_heldKeys[evnt.key.keysym.scancode]= false;

}
//check if key was pressed during the current frame
bool Input::wasKeyPressed(SDL_Scancode key){
    return this->_pressedKeys[key];
}

//check if a certain key was released
bool Input::wasKeyRelease(SDL_Scancode key){
    return this->_releaseKeys[key];
    }

//if key is held now.
bool Input::isKeyHold(SDL_Scancode key){
    return this->_heldKeys[key];
    }