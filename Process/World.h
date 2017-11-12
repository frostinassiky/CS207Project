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

class World: private sf::NonCopyable {
public:
    World(sf::RenderWindow& window);
    void update(sf::Time dt);
    void draw();
    CommandQ& getCommandQ();

private:
    void loadTextures(){};
    void buildScene(){};

private:
    enum Layer
    {
        Background,
        Air,
        LayerCount
    };

private:
    sf::RenderWindow& mWindow;
    sf::View mWorldView;
    SceneNode mSceneGraph; // root of all scene
    SceneNode* mSceneLayers[LayerCount];  // book uses class array
    CommandQ mCommandQ;
    sf::FloatRect mWorldBounds;
    sf::Vector2f mSpawnPosition;
    float mScrollSpeed;
    Tank* mPlayerTank;


};


#endif //TANKCRAFT_WORLD_H
