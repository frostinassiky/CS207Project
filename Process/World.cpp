//
// Created by Mengmeng Xu on 11/10/17.
//

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

    // Load and Build background node
    sf::Texture* ptexture = new sf::Texture;
    ptexture->loadFromFile("../Media/Sand.jpg");
    sf::IntRect textureRect(mWorldBounds);
    ptexture->setRepeated(true);

    SpriteNode* bgSprite = new SpriteNode(*ptexture,textureRect); // TODO debug: ugly
    bgSprite->setPosition(mWorldBounds.left,mWorldBounds.top);
    // Add to layer
    mSceneLayers[Background]->attach(bgSprite);

    // Tank - Ally
    Tank* leader = new Tank(Tank::Ally);
    mPlayerTank = leader;
    mPlayerTank->setPosition(mSpawnPosition);
    mPlayerTank->setVelocity(0.f, -40.f);
    mSceneLayers[Air]->attach(leader);

    // Tank Bullet
    Tank* Bullet = new Tank(Tank::Enemy);
    Bullet->setPosition(0, 0);
    Bullet->setVelocity(0, -80.f);
    Bullet->setRotation(0);
    mPlayerTank->attach(Bullet);


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
    mSceneGraph.update(dt);
}
