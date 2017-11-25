//
// Created by Mengmeng Xu on 11/10/17.
//

#ifndef TANKCRAFT_WORLD_H
#define TANKCRAFT_WORLD_H



#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <array>
#include "SceneNode.h"
#include "Tank.h"
#include <list>

class World: private sf::NonCopyable {

private:
    enum Layer
    {
        Background,
        Air,
        Sky,
        LayerCount
    };

private:
    sf::RenderWindow& mWindow;
    sf::View mWorldView;
    SceneNode mSceneGraph; // root of all scene
    SceneNode* mSceneLayers[LayerCount];  // book uses class array
    CommandQ mCommandQ;
    sf::FloatRect mWorldBounds;
    sf::Vector2f mOrigin;
    float mScrollSpeed;
    Tank* mPlayerTank1;
    Tank* mPlayerTank2;
    //std::list<sf::FloatRect> mObstacles;
    std::list<SceneNode*> mObstacles;



private:
    void addEntities();
    void updateView(sf::Time);
    void handleCollisions();

public:
    World(sf::RenderWindow& window);
    void update(sf::Time dt);
    void draw();
    CommandQ& getCommandQ();
    int winner();
};


#endif //TANKCRAFT_WORLD_H
