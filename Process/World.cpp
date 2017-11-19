//
// Created by Mengmeng Xu on 11/10/17.
//

#include <iostream>
#include "World.h"
#include "SpriteNode.h"

World::World(sf::RenderWindow &window):
        mWindow(window),
        mWorldView(window.getDefaultView()),
        mWorldBounds(0.f, 0.f, mWorldView.getSize().x,mWorldView.getSize().y), // view boundary == real boundary
        mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldView.getSize().y / 2.f), // spawn in the center
        mPlayerTank(nullptr)
{
    // loadTextures(); TODO load files here, not separately

    // buildScene();
    // mSceneGraph -> layer 1 -> object 1
    //             -> layer 2 -> object 2
    for (int k = 0; k < LayerCount; k++)
    {
        // build each layer
        SceneNode* layer = new SceneNode();
        // record
        mSceneLayers[k] = layer;
        // attach to root: mSceneGraph
        mSceneGraph.attach(layer); // In book: std::move(layer) might have bug
    }
    // set mCategary
    mSceneLayers[Background]->mCategory = CBackgroundLayer;
    mSceneLayers[Air]->mCategory = CAirLayer;

    // Load and Build background node
    sf::Texture* ptexture = new sf::Texture;
    ptexture->loadFromFile("../Media/Sand.jpg");
    sf::IntRect textureRect(mWorldBounds);
    ptexture->setRepeated(true);

    SpriteNode* bgSprite = new SpriteNode(*ptexture,textureRect); // TODO debug: ugly
    bgSprite->setPosition(mWorldBounds.left,mWorldBounds.top);
    // Add to layer
    mSceneLayers[Background]->attach(bgSprite);

    // Tank - Player 1 - control by Up-Down
    Tank* Tank1 = new Tank(Tank::PlayerUp);
    mPlayerTank = Tank1;
    mPlayerTank->setPosition(mSpawnPosition-sf::Vector2f(200,-100));
    mPlayerTank->setDirection(1.f);
    mPlayerTank->setVelocity(0.f, -40.f);
    mPlayerTank->mCategory = CTank;
    mSceneLayers[Air]->attach(Tank1);

    // Tank - Player 2 - control by W-S
    Tank* Tank2 = new Tank(Tank::PlayerWS);
    mPlayerTank = Tank2;
    mPlayerTank->setPosition(mSpawnPosition+sf::Vector2f(200,-100));
    mPlayerTank->setDirection(1.f);
    mPlayerTank->setRotation(180.0f);
    mPlayerTank->setVelocity(0.f, 40.f);
    mPlayerTank->mCategory = CTank;
    mSceneLayers[Air]->attach(Tank2);

    /*/ Tank Bullet
    Tank* Bullet = new Tank(Tank::Enemy);
    Bullet->setPosition(0, 0);
    Bullet->setVelocity(0, -80.f);
    Bullet->setRotation(0);
    mPlayerTank->attach(Bullet);
    */

    mWorldView.setCenter(mSpawnPosition);
}

void World::draw() {
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
}

void World::update(sf::Time dt) {
    mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());
    sf::Vector2f position = mPlayerTank->getPosition();
    sf::Vector2f velocity = mPlayerTank->getVelocity();
    if (position.y <= mWorldBounds.top + 150
        || position.y >= mWorldBounds.top + mWorldBounds.height - 150)
    {
        velocity.y = -velocity.y;
        mPlayerTank->setVelocity(velocity);
        mPlayerTank->setRotation(mPlayerTank->getRotation()+180);
    }
    // std::cout << "World::update(sf::Time dt).." << std::endl; -- debug
    // Forward commands to the scene graph
    while (!mCommandQ.isEmpty()){
        mSceneGraph.onCommand(mCommandQ.pop(), dt);
        // std::cout << "mSceneGraph.onCommand(mCommandQ.pop(), dt);.." << std::endl;
    }
    mSceneGraph.update(dt);
}

CommandQ &World::getCommandQ() {
    return mCommandQ;
}
