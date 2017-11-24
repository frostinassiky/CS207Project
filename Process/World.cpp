//
// Created by Mengmeng Xu on 11/10/17.
//

#include <iostream>
#include "World.h"
#include "SpriteNode.h"
#include "Cloud.h"
#include "Obstacle.h"
#include "Projectile.h"

World::World(sf::RenderWindow &window):
        mWindow(window),
        mWorldView(window.getDefaultView()),
        mWorldBounds(0.f, 0.f, mWorldView.getSize().x*10,mWorldView.getSize().y*10), // view boundary == 10*real boundary
        mOrigin(mWorldBounds.width/2,mWorldBounds.height/2),
        mPlayerTank1(nullptr),mPlayerTank2(nullptr),
        mScrollSpeed(200)
{
    // buildScene();
    // mSceneGraph -> layer 1 (Back) -> object 1
    //             -> layer 2 (Air)  -> tank1, tank2, bullets, stones
    //             -> layer 3 (Sky)  -> clouds
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
    mSceneLayers[Sky]->mCategory = CSky;

    addEntities();

    mWorldView.setCenter(mOrigin);
    mWorldView.setSize(mWindow.getSize().x*.8,mWindow.getSize().y*.8);
}

void World::draw() {
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
}

void World::update(sf::Time dt) {
//    sf::Vector2f position = mPlayerTank->getPosition();
//    sf::Vector2f velocity = mPlayerTank->getVelocity();
//    if (position.y <= mWorldBounds.top + 150
//        || position.y >= mWorldBounds.top + mWorldBounds.height - 150)
//    {
//        velocity.y = -velocity.y;
//        mPlayerTank->setVelocity(velocity);
//        mPlayerTank->setRotation(mPlayerTank->getRotation()+180);
//    }
    // std::cout << "World::update(sf::Time dt).." << std::endl; -- debug
    // Forward commands to the scene graph
    while (!mCommandQ.isEmpty()){
        mSceneGraph.onCommand(mCommandQ.pop(), dt);
        // std::cout << "mSceneGraph.onCommand(mCommandQ.pop(), dt);.." << std::endl;
    }
    updateView(dt);
    handleCollisions();
    mSceneGraph.update(dt);
}

CommandQ &World::getCommandQ() {
    return mCommandQ;
}

void World::updateView(sf::Time dt) {
    // update viewport
    // mWorldView.rotate(1);
    sf::Vector2f tankCenter(
            mPlayerTank1->getWorldPosition().x*.5f + mPlayerTank2->getWorldPosition().x*.5f,
            mPlayerTank1->getWorldPosition().y*.5f + mPlayerTank2->getWorldPosition().y*.5f
    );
    sf::Vector2f tankBox(
            mPlayerTank1->getWorldPosition().x - mPlayerTank2->getWorldPosition().x,
            mPlayerTank1->getWorldPosition().y - mPlayerTank2->getWorldPosition().y
    );
    sf::Vector2f scroll(0,0);
    sf::Vector2f size(mWorldView.getSize());
    float sizeRatio = size.y / size.x;

    // Use scroll in case of camera shake
    // std::cout<< "Tank pos: " << mPlayerTank->getWorldPosition().y << " " << mWorldView.getCenter().y << std::endl;
    if (tankCenter.y < mWorldView.getCenter().y-mWindow.getSize().y*0.15)
        scroll.y -= mScrollSpeed * dt.asSeconds();
        // mWorldView.move(0,-mScrollSpeed * dt.asSeconds());
    if (tankCenter.y > mWorldView.getCenter().y+mWindow.getSize().y*0.15)
        scroll.y += mScrollSpeed * dt.asSeconds();
        // mWorldView.move(0,mScrollSpeed * dt.asSeconds());
    if (tankCenter.x < mWorldView.getCenter().x-mWindow.getSize().x*0.25)
        scroll.x -= mScrollSpeed * dt.asSeconds();
        // mWorldView.move(-mScrollSpeed * dt.asSeconds(),0);
    if (tankCenter.x > mWorldView.getCenter().x+mWindow.getSize().x*0.25)
        scroll.x += mScrollSpeed * dt.asSeconds();
        // mWorldView.move(mScrollSpeed * dt.asSeconds(),0);
    mWorldView.move( scroll );

    if (abs((int)tankBox.x) > mWorldView.getSize().x - mWindow.getSize().x*0.1 ||
            abs((int)tankBox.y) > mWorldView.getSize().y - mWindow.getSize().y*0.2){
        size.x += mScrollSpeed * dt.asSeconds();
        size.y += mScrollSpeed * dt.asSeconds() * sizeRatio;
    }

    if (size.x > mWindow.getSize().x*.8 &&
            abs((int)tankBox.x) < mWorldView.getSize().x - mWindow.getSize().x*0.5 &&
            abs((int)tankBox.y) < mWorldView.getSize().y - mWindow.getSize().y*0.6 ) {
        size.x -= mScrollSpeed * dt.asSeconds();
        size.y -= mScrollSpeed * dt.asSeconds() * sizeRatio;
    }

    mWorldView.setSize(size);

}

void World::addEntities() {

    srand (static_cast<unsigned int>(time(0)));
    // Load and Build background node
    sf::Texture* ptexture = new sf::Texture;
    ptexture->loadFromFile("../Media/Sand.jpg");
    sf::IntRect textureRect(mWorldBounds);
    ptexture->setRepeated(true);

    SpriteNode* bgSprite = new SpriteNode(*ptexture,textureRect);
    bgSprite->setPosition(mWorldBounds.left,mWorldBounds.top);
    // Add to layer
    mSceneLayers[Background]->attach(bgSprite);

    // Stone
    sf::Vector2f bound(mWorldBounds.width,mWorldBounds.height);
    for (int k=0; k<200; k++){
        if ( rand() % 10 > 3 )
            continue;
        std::string path =  "../Media/Obstacles/Obstacle_";
        path += std::to_string( k%10 );
        path += ".png";
        // "../Media/Obstacles/Obstacle1.png"
        mSceneLayers[Air]->attach(new Obstacle( path, bound ));
    }



    // Tank - Player 1 - control by Up-Down
    mPlayerTank1 = new Tank(Tank::PlayerUp);
    mPlayerTank1->setPosition(mOrigin-sf::Vector2f(200,-100));
    mPlayerTank1->setDirection(1.f);
    mPlayerTank1->setVelocity(0.f, -40.f);
    mPlayerTank1->mCategory = CTank;
    // Add to layer
    mSceneLayers[Air]->attach(mPlayerTank1);

    // Tank - Player 2 - control by W-S
    mPlayerTank2 = new Tank(Tank::PlayerWS);
    mPlayerTank2->setPosition(mOrigin+sf::Vector2f(200,-100));
    mPlayerTank2->setDirection(1.f);
    mPlayerTank2->setRotation(180.0f);
    mPlayerTank2->setVelocity(0.f, 40.f);
    mPlayerTank2->mCategory = CTank;
    // Add to layer
    mSceneLayers[Air]->attach(mPlayerTank2);

    // Sky
    mSceneLayers[Sky]->attach(new Cloud( "../Media/Cloud1.png", bound, 96 ));

    mSceneLayers[Sky]->attach(new Cloud( "../Media/Cloud2.png", bound, 64 ));

    mSceneLayers[Sky]->attach(new Cloud( "../Media/Cloud3.png", bound, 255 ));

    mSceneLayers[Sky]->attach(new Cloud( "../Media/Cloud2.png", bound, 96 ));

    mSceneLayers[Sky]->attach(new Cloud( "../Media/Cloud3.png", bound, 128 ));

    mSceneLayers[Sky]->attach(new Cloud( "../Media/Cloud3.png", bound, 128));


    /*
    ptexture = new sf::Texture;
    ptexture->loadFromFile("../Media/Cloud3.png");
    // Add to layer
    mSceneLayers[Sky]->attach(new Cloud( bound,*ptexture ));
    ptexture = new sf::Texture;
    ptexture->loadFromFile("../Media/Cloud3.png");
    // Add to layer
    mSceneLayers[Sky]->attach(new Cloud( bound,*ptexture ));
*/
}

void World::handleCollisions()
{
    if ((mPlayerTank1->getBoundingRect().intersects(mPlayerTank2->getBoundingRect()))) {
        std::cout << "intersect self" << std::endl;
        // mPlayerTank1->setVelocity(10.0, 10.0);
        mPlayerTank1->setScale(2,2);
        mPlayerTank2->setScale(2,2);
    }
    if ((dynamic_cast<Projectile*> (mPlayerTank1->tankBullets_[0])->getBoundingRect().intersects(mPlayerTank2->getBoundingRect())))
    {
        mPlayerTank1->setScale(2,2);
    }
}
