#include "include/game.h"
#include "include/IO.h"
#include "include/input.h"

/*
Holds all information for our main game loop
*/
namespace {
    const int FPS = 50;
    const int MAX_FRAME_TIME = 1000/FPS;
}


Game::Game(){
    SDL_Init(SDL_INIT_EVERYTHING);
    this->gameLoop();
}

Game::~Game(){
}

void Game::gameLoop(){
    IO graph;
    Input input;
    SDL_Event evnt;

  //  std::string str= "./content/sprites/MyChar.png";
    
    this->_level = Level("FirstMap", graph);
    this->_player = Player(graph,this->_level.getPlayerSpawnPoint());
    this->_hud = Hud(graph,this->_player);

int LAST_UPDATE_TIME= SDL_GetTicks();

//start game loop
    while(true){
        input.beginNewFrame();

        if(SDL_PollEvent(&evnt)){
            if(evnt.type == SDL_KEYDOWN){
                if (evnt.key.repeat == 0){
                    input.keyDownEvent(evnt);
                }
            }else if(evnt.type ==SDL_KEYUP){
                input.keyUpEvent(evnt);
            }
            else if(evnt.type == SDL_QUIT)
            {
                return;
            }
        }

        if(input.wasKeyPressed(SDL_SCANCODE_ESCAPE)){
            graph.clear();
            return;
        }
        else if(input.isKeyHold(SDL_SCANCODE_LEFT) ==true)
        {
            this->_player.moveLeft();
        }
        else if (input.isKeyHold(SDL_SCANCODE_RIGHT)== true){
            this->_player.moveRight();
        }

//look down and up:
        if(input.isKeyHold(SDL_SCANCODE_UP)){
            this->_player.lookUp();
        }
        else if (input.isKeyHold(SDL_SCANCODE_DOWN)){
            this->_player.lookDown();
        }

        if(input.wasKeyRelease(SDL_SCANCODE_DOWN)){
            this->_player.stopLookingDown();
        }
        else if (input.wasKeyRelease(SDL_SCANCODE_UP)){
            this->_player.stopLookingUp();
        }
//

        if(input.wasKeyPressed(SDL_SCANCODE_Z) == true){
            this->_player.jump();
        }
        if(!input.isKeyHold(SDL_SCANCODE_RIGHT) && !input.isKeyHold(SDL_SCANCODE_LEFT)){
            this->_player.stopMoving();
        }

//this way we fix the fps to 50  , so the movement is the same on every kind of PC
    const int CURRENT_TIME_MS = SDL_GetTicks();
    int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;

    this->_graph = graph;

    this->update(std::min(ELAPSED_TIME_MS,MAX_FRAME_TIME));
    LAST_UPDATE_TIME = CURRENT_TIME_MS;
    
    
    this->draw(graph);
    }

}

void Game::draw(IO &graphics){
    graphics.clear();
    this->_level.draw(graphics);
    this->_player.draw(graphics);
    this->_hud.draw(graphics);
    
    graphics.flip();
}

void Game::update(float elapsedTime){
    this->_level.update(elapsedTime, this->_player);
    this->_player.update(elapsedTime);
    this->_hud.update(elapsedTime,this->_player);
    

    std::vector<Recteng> others;
    if((others = this->_level.checkTileCollision(this->_player.getBoundingBox())).size() > 0){
        this->_player.handleTileCollisions(others);
    }

    //check slopes
    std::vector<Slope> otherSlopes;
    if((otherSlopes = this->_level.checkSlopeCollision(this->_player.getBoundingBox())).size()>0){
        this->_player.handleSlopeCollisions(otherSlopes);
    }
    std::vector<Door> dr;
    if((dr = this->_level.checkDoorCollision(this->_player.getBoundingBox())).size() > 0){
    
        this->_player.handleDoorCollision(dr, this->_level, this->_graph);
    }

    std::vector<std::shared_ptr<Enemy>> otherEnemies;
    if((otherEnemies=this->_level.checkEnemyCollision(this->_player.getBoundingBox())).size()>0){
        this->_player.handleEnemyCollision(otherEnemies);
    }

}