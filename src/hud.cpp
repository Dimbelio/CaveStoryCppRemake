#include "include/hud.h"
#include "include/IO.h"

#include <iostream>
Hud::Hud(IO & graph, Player &player)

{
    this->_player = player;
    this->_healthBarSprite = Sprite(graph, "./content/sprites/TextBox.png",0 ,40,64,8, 35, 70);
    this->_healthNumber1 = Sprite(graph, "./content/sprites/TextBox.png",0 , 56, 8, 8, 66,70);
    this->_currentHealthBar = Sprite(graph, "./content/sprites/TextBox.png",0,25,39,5,83,72);
    this->_lvWord = Sprite(graph,"./content/sprites/TextBox.png",81,81,11,7,38,55);
    this->_lvNumber = Sprite(graph,"./content/sprites/TextBox.png",0,56,8,8,66,52);
    this->_xpBar = Sprite(graph,"./content/sprites/TextBox.png",0,73,40,8,83,52);
    this->_slash = Sprite(graph,"./content/sprites/TextBox.png",72,48,8,8,100,36);
    this->_dash = Sprite(graph,"./content/sprites/TextBox.png",81,51,15,11,132,26);
}

void Hud::update(int elapsedTime,Player &player){
    this->_player = player;
    this->_healthNumber1.setSourceRectX(8*this->_player.getCurrentHealth());

    float num = static_cast<float>(this->_player.getCurrentHealth()) / this->_player.getMaxHealth();
   
     this->_currentHealthBar.setSourceRectWidth(std::floor(num*39));
}

void Hud::draw(IO &graph){
    this->_healthBarSprite.draw(graph, this->_healthBarSprite.getX(), this->_healthBarSprite.getY());
    this->_healthNumber1.draw(graph, this->_healthNumber1.getX(),this->_healthNumber1.getY());
    this->_currentHealthBar.draw(graph,this->_currentHealthBar.getX(),this->_currentHealthBar.getY());
    this->_lvWord.draw(graph,this->_lvWord.getX(),this->_lvWord.getY());
    this->_lvNumber.draw(graph,this->_lvNumber.getX(),this->_lvNumber.getY());
    this->_xpBar.draw(graph,this->_xpBar.getX(),this->_xpBar.getY());
    this->_slash.draw(graph,this->_slash.getX(),this->_slash.getY());
    this->_dash.draw(graph,this->_dash.getX(),this->_dash.getY());

}