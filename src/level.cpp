#include "include/level.h"
#include "include/IO.h"

#include "include/tinyxml2.h"
#include "include/utils.h"
#include "include/player.h"
#include "include/enemy.h"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace tinyxml2;

Level::Level(){
}

Level::Level(std::string mapName,IO &graph)
:
    _mapName(mapName),
    _size(Vector2(0,0))
{
this->loadMap(mapName,graph);  
}

Level::~Level(){}

void Level::loadMap(std::string mapName,IO & graph){

  //parse the .tmx file
    XMLDocument doc;
    std::stringstream ss;
    ss<< "content/maps/" <<mapName << ".tmx";
    doc.LoadFile(ss.str().c_str());
    XMLElement * mapNode = doc.FirstChildElement("map");

    
    //get the width and the height of the whole map and store it in _size;
    int width, height;
    mapNode->QueryIntAttribute("width", &width);
    mapNode->QueryIntAttribute("height", &height);
    this->_size = Vector2(width,height);

    
    //get the width and the height of the tile
    int tileWidth, tileHeight;
    mapNode->QueryIntAttribute("tilewidth", &tileWidth);
    mapNode->QueryIntAttribute("tileheight", &tileHeight);

    //printf("HEY\n");
    this->_tileSize = Vector2(tileWidth,tileHeight);

    //loading tilesets
    std::stringstream npcSym;
    npcSym<<"content/tilesets/NpcSym.xml";
    XMLDocument npc;
    npc.LoadFile(npcSym.str().c_str());
    XMLElement* npcTileset = npc.FirstChildElement("tileset");
    
    npcSym.str(std::string());



    std::vector<SDL_Texture*> tex;
    XMLElement* pTileset = mapNode->FirstChildElement("tileset");
    if(pTileset != NULL){
        //With this for loop we put different png files-Tilesets to our _tilesets vector
        //This way we can go through more than one tileset.
        for(int j = 0;pTileset;j++){
            int firstGid;
            const char* source = pTileset->Attribute("source");
            
           //const char* path ;
            std::stringstream ss;
              
              ss <<"content";
            for(int i = 2; i<(int)strlen(source);++i){
                if(source[i]=='.' && source[i+1]=='x'){break;}
                ss<<source[i];
            }
            ss<<".png";

            
            tex.push_back(SDL_CreateTextureFromSurface(graph.getRenderer(),graph.loadImage(ss.str())));
            
            pTileset->QueryIntAttribute("firstgid",&firstGid);

                   
            this->_tilesets.push_back(Tileset(tex[j],firstGid));
            if(tex[j] ==NULL){
                printf("error");
            }
            
            pTileset = pTileset->NextSiblingElement("tileset");

            
         if(npcTileset!=NULL){
            while(npcTileset){
             XMLElement* npcTileA = npcTileset->FirstChildElement("tile");
            //AnimatedTileInfo ati;
            for(int i = 0 ; npcTileA;++i){

             XMLElement* npcAnimation = npcTileA->FirstChildElement("animation");

                while(npcAnimation){
                    AnimatedTileInfo ati;
                    ati.StartTileId = npcTileA->IntAttribute("id")+ 81;
                    ati.TilesetsFirstGid = 0;
                    XMLElement* npcFrame = npcAnimation->FirstChildElement("frame");
                    while(npcFrame){

                    ati.TileId.push_back(npcFrame->IntAttribute("tileid")+81);
                    
                    ati.Duration = npcFrame->IntAttribute("duration");
                    npcFrame = npcFrame->NextSiblingElement("frame");
                    }
                    npcAnimation = npcAnimation->NextSiblingElement("animation");
                this->_animatedTileInfos.push_back(ati);
                }
                
                
                npcTileA = npcTileA->NextSiblingElement("tile");
            }
            npcTileset= npcTileset->NextSiblingElement("tileset");
        }
    }



        }
    }

    XMLElement* pLayer = mapNode->FirstChildElement("layer");
    if(pLayer!= NULL){
        while(pLayer){
            //Loading the data element
            XMLElement* pData = pLayer->FirstChildElement("data");
            if(pData !=NULL){
                while(pData){
                    const char* tilearray;

                    tilearray = pData->GetText();
                    std::string tilestring(tilearray);

                    std::vector<int> vect;
                    std::stringstream ss(tilestring);

                    int i;
                    while(ss>>i)
                    {
                        vect.push_back(i);
                        if(ss.peek() == ','){
                            ss.ignore();
                        }
                    }
                    
                    for(size_t j = 0 ; j<vect.size();++j){
                         int tlsSize = 0;
                        if(vect.at(j)!=0){
                            Tileset tls;
                            for(size_t i = 0; i<this->_tilesets.size();++i){
                                if(this->_tilesets[i].FirstGid<=vect.at(j)){
                                        if(this->_tilesets[i].FirstGid>tlsSize){
                                            tlsSize = this->_tilesets[i].FirstGid;
                                            tls=this->_tilesets.at(i);

                                        }
                               
                                }
                              
                            }
                            if(tls.FirstGid == -1){
                                printf("Errorrr");
                        }
                      
                        int xx = 0;
                        int yy = 0;

                        xx = j % width;
                        xx *= tileWidth;
                        yy += tileHeight * (j/width);

                        Vector2 finalTilePosition = Vector2(xx,yy);
                        //calculate the position of the tile in the tileset
                        Vector2 finalTileSetPosition = this->getTilesetPosition(tls,j,tileWidth,tileHeight,vect);
                        bool isAnimatedTile = false;
                        AnimatedTileInfo ati;

                       
                      
                        for(size_t i = 0 ; i<this->_animatedTileInfos.size();i++)
                        {
                            if(this->_animatedTileInfos.at(i).StartTileId == vect.at(j)){
                                ati = this->_animatedTileInfos.at(i);
                                isAnimatedTile = true;
                                break;
                               
                            }
                        }
                        
                        
                           
                        if(isAnimatedTile == true){
                            std::vector<Vector2> tilesetPositions;
                             int ja = ati.TileId.size()-1;
                            for(size_t i = 0 ; i <ati.TileId.size();i++){
                               
                                if(ja>=0){
                                tilesetPositions.push_back(getTilesetPosition(Tileset(tex[1],81),ja,tileWidth,tileHeight,
                                    ati.TileId));
                                    }
                            --ja;
                            }
                                
                                    AnimatedTile tile(tilesetPositions,ati.Duration,tls.texture,
                                                Vector2(tileWidth,tileHeight),finalTilePosition);
                                    this->_animatedTileList.push_back(tile);
                        }
                        else{
                        Tile tile(tls.texture,Vector2(tileWidth,tileHeight), finalTileSetPosition, finalTilePosition);
                        this->_tileList.push_back(tile);
                        }        

                        }

                    }
                    pData = pData->NextSiblingElement("data");
                }
            }

            pLayer= pLayer->NextSiblingElement("layer");
        }
    }

    //Parse the collision
    XMLElement* pObjectGroup = mapNode->FirstChildElement("objectgroup");
    if(pObjectGroup!= NULL){
        while(pObjectGroup){
            const char* name = pObjectGroup->Attribute("name");
            std::stringstream ss;
            ss<<name;
            if(ss.str() == "collisions"){
                
                XMLElement * pObject = pObjectGroup->FirstChildElement("object");
                if(pObject !=NULL){
                    while(pObject){
                    
                        float x,y,width,height;
                        x=pObject->FloatAttribute("x");
                        y=pObject->FloatAttribute("y");
                        width=pObject->FloatAttribute("width");
                        height=pObject->FloatAttribute("height");

                        this->_collisionRects.push_back(Recteng(
                            std::ceil(x) * globals::SPRITE_SCALE,
                            std::ceil(y) * globals::SPRITE_SCALE,
                            std::ceil(width) * globals::SPRITE_SCALE,
                            std::ceil(height) * globals::SPRITE_SCALE
                        ));

                        pObject = pObject->NextSiblingElement("object");
                    }
                }
            }
            //Other ojectgroups go here with an else if (ss.str() == "whatever object name")
            else if(ss.str()=="slopes"){
            XMLElement* pObject = pObjectGroup->FirstChildElement("object");
            if (pObject != NULL){
                while(pObject){
                    std::vector<Vector2> points;
                    Vector2 p1;
                    p1 = Vector2(std::ceil(pObject->FloatAttribute("x")),std::ceil(pObject->FloatAttribute("y")));
                    XMLElement * pPolyline = pObject->FirstChildElement("polyline");
                    if(pPolyline != NULL){
                        std::vector<std::string> pairs;
                        const char* pointString = pPolyline->Attribute("points");
                        std::stringstream sss;
                        sss<<pointString;

                        Utils::split(sss.str(), pairs,' ');
                        //now we have each of the pairs.
                        
                        for(size_t i = 0 ; i<pairs.size() ; ++i){
                       
                            std::vector<std::string> ps;
                            Utils::split(pairs.at(i),ps, ',');
                            points.push_back(Vector2(std::stoi(ps.at(0)),std::stoi(ps.at(1))));
                        }
                    }

                    for(size_t i =0 ; i<points.size()-1; i++){
                        Vector2 point1 = Vector2((p1.x + points.at(i).x)* globals::SPRITE_SCALE,
					                (p1.y + points.at(i).y) * globals::SPRITE_SCALE);
			            Vector2 point2 = Vector2((p1.x + points.at(i + 1).x) * globals::SPRITE_SCALE,
					                (p1.y + points.at(i + 1).y) * globals::SPRITE_SCALE);
			            Slope slope = Slope(point1,point2);
			            this->_slopes.push_back(slope);
                       // printf("In _slopes\n");
                    }
                    pObject = pObject->NextSiblingElement("object");
                }
            }

            }
            else if(ss.str() == "spawn_point"){
                 
                XMLElement* pObject = pObjectGroup ->FirstChildElement("object");
                if(pObject != NULL){
                    
                    while(pObject){
                        float x = pObject->FloatAttribute("x");
                        float y = pObject->FloatAttribute("y");
                        const char* name =pObject->Attribute("name");
                        std::stringstream sss;
                        sss<<name;
                        if(sss.str()=="player"){
                           
                            this->_spawnPoint = Vector2(
                                std::ceil(x)*globals::SPRITE_SCALE, std::ceil(y)* globals::SPRITE_SCALE);
                        
                        }
                        
                        pObject = pObject->NextSiblingElement("object");
                    }
                }
            }

            else if (ss.str() == "Doors"){
                XMLElement* pObject = pObjectGroup->FirstChildElement("object");
                while(pObject){
                    float x = pObject->FloatAttribute("x");
                    float y = pObject->FloatAttribute("y");
                    float h = pObject->FloatAttribute("height");
                    float w = pObject->FloatAttribute("width");
                    Recteng rect = Recteng(x,y,w,h);

                    XMLElement* pProperties = pObject->FirstChildElement("properties");
                    while(pProperties){
                        XMLElement* pProperty = pProperties->FirstChildElement("property");
                        while(pProperty){
                            const char* name = pProperty->Attribute("name");
                            std::stringstream ss;
                            ss<<name;
                            if(ss.str()=="Destination"){
                                const char* value = pProperty->Attribute("value");
                                std::stringstream ss2;
                                ss2<<value;
                                
                                Door door = Door(rect,ss2.str());
                                this->_doorList.push_back(door);
                            }
                            
                            pProperty = pProperty->NextSiblingElement("property");
                        }
                        pProperties= pProperties->NextSiblingElement("properties");
                    }
                    

                    pObject = pObject->NextSiblingElement("object");
                }
            }
            
            else if(ss.str()=="enemies"){
                float x,y;
                XMLElement *pObject = pObjectGroup->FirstChildElement("object");
                while(pObject){

                    const char* name = pObject->Attribute("name");

                    std::stringstream ss;
                    ss<<name;
                    if(ss.str()=="bat"){
                        x = pObject->FloatAttribute("x");
                        y = pObject->FloatAttribute("y");
                        this->_enemies.push_back(std::make_shared<Bat>(graph,Vector2(std::floor(x)*globals::SPRITE_SCALE,
                                            std::floor(y)*globals::SPRITE_SCALE)));
                                          
                    }

                    pObject = pObject->NextSiblingElement("object");
                }
            }

            pObjectGroup= pObjectGroup->NextSiblingElement("objectgroup");
        }
    }
}

void Level::update(int elapsedTime,Player &player){
        for(size_t  i = 0 ; i <this->_animatedTileList.size();++i){
            this->_animatedTileList.at(i).update(elapsedTime);
        }

    for(size_t i = 0; i< this->_enemies.size();++i){
            this->_enemies.at(i)->update(elapsedTime,player);
    }
}

std::vector<Door> Level::checkDoorCollision(const Recteng& other){
    std::vector<Door> dr;
    for(size_t i = 0 ; i<this->_doorList.size();++i){
        if(this->_doorList.at(i).collidesWith(other)){
            dr.push_back(this->_doorList.at(i));
        }
    }
    return dr;
}

std::vector<Recteng> Level::checkTileCollision(const Recteng &other){
    std::vector<Recteng> temp;
    for(size_t i = 0 ; i< this->_collisionRects.size();++i){
        if(this->_collisionRects.at(i).collidesWith(other)){
            temp.push_back(this->_collisionRects.at(i));
        }
    }
    return temp;

}

std::vector<Slope> Level::checkSlopeCollision(const Recteng & other){
    std::vector<Slope> temp;
    for(size_t i = 0; i<this->_slopes.size(); ++i){
        if(this->_slopes.at(i).collidesWith(other)){
            temp.push_back(this->_slopes.at(i));
        }
    }
    return temp;
}

std::vector<std::shared_ptr<Enemy>> Level::checkEnemyCollision(const Recteng&other){
        std::vector<std::shared_ptr<Enemy>> en;
        for(size_t i = 0 ; i<this->_enemies.size();++i){
            if(this->_enemies.at(i)->getBoundingBox().collidesWith(other)){
                    en.push_back(this->_enemies.at(i));
            }
        }
        return en;
}


const Vector2 Level::getPlayerSpawnPoint()const{
    return this->_spawnPoint;
}

void Level::draw(IO &graph)
{

  
    for (size_t i = 0; i<this->_tileList.size();++i){
              this->_tileList.at(i).draw(graph);
    }

  for(size_t i = 0 ; i <this->_animatedTileList.size();++i){
        this->_animatedTileList.at(i).draw(graph);
        
    }
  for(size_t i= 0 ; i<this->_enemies.size();++i){
      
        this->_enemies.at(i)->draw(graph);   
    }


}

Vector2 Level::getTilesetPosition(Tileset tls, int j , int tileWidth, int tileHeight,std::vector<int> vect){
                        
                        int tilesetWidth, tilesetHeight;
                        
                        SDL_QueryTexture(tls.texture, NULL,NULL,&tilesetWidth,&tilesetHeight);
                        
                        
                        int tsxx = vect.at(j)  % (tilesetWidth/tileWidth)-1;
                        //std::cout<<vect.at(9)<<std::endl;
                        tsxx *= tileWidth;
                        
                        
                        
                        int tsyy = 0;
                        int amt =( (vect.at(j) - tls.FirstGid )/ (tilesetWidth/tileWidth));
                        

                        tsyy = tileHeight * amt;
                        Vector2 finalTileSetPosition = Vector2(tsxx,tsyy);
                        
                        return finalTileSetPosition;

}
