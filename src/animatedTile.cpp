#include "include/animatedTile.h"
#include "include/IO.h"


AnimatedTile::AnimatedTile(std::vector<Vector2> tilesetPosition, int duration, SDL_Texture* tileset,
                Vector2 size, Vector2 position) :
                Tile(tileset, size, tilesetPosition.at(0), position),
                _tilesetPosition(tilesetPosition),
                _tileToDraw(0),
                _duration(duration)
                
                {
                    

                }

void AnimatedTile::update(int elapsedTime){
    if(this->_amountOfTime <=0){
        if(static_cast<unsigned>(this->_tileToDraw) == this->_tilesetPosition.size()-1){
            this->_tileToDraw = 0;
        }
        else{this->_tileToDraw++;
        }
        this->_amountOfTime = this->_duration;
    }
    else{
        this->_amountOfTime -= elapsedTime;
    }

    Tile::update(elapsedTime);
}

void AnimatedTile::draw(IO &graph){
    SDL_Rect destRect = {this->_position.x, this->_position.y,
                         this->_size.x * static_cast<int>(globals::SPRITE_SCALE), this->_size.y * static_cast<int>(globals::SPRITE_SCALE)};


    SDL_Rect sourceRect = {this->_tilesetPosition.at(this->_tileToDraw).x , this->_tilesetPosition.at(this->_tileToDraw).y,
                            this->_size.x,this->_size.y};

    graph.blitSurface(this->_tileset, &sourceRect, &destRect);
    

}

