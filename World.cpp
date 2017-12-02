//
// Created by Mengmeng Xu on 11/10/17.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include "World.h"
#include "SpriteNode.h"
#include "Cloud.h"
#include "Obstacle.h"
#include "Projectile.h"
#include "Utility.h"

World::World(sf::RenderWindow &window) :
        mWindow(window),
        mWorldView(window.getDefaultView()),
        mWorldBounds(0.f, 0.f, mWorldView.getSize().x * 5,
                     mWorldView.getSize().y * 5), // view boundary == 10*real boundary
        mOrigin(mWorldBounds.width / 2, mWorldBounds.height / 2),
        mPlayerTank1(nullptr), mPlayerTank2(nullptr),
        mScrollSpeed(300), mFont(), mStat() {
    // buildScene();
    // mSceneGraph -> layer 1 (Back) -> object 1
    //             -> layer 2 (Air)  -> tank1, tank2, bullets, stones
    //             -> layer 3 (Sky)  -> clouds
    for (int k = 0; k < LayerCount; k++) {
        // build each layer
        SceneNode *layer = new SceneNode();
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
    mWorldView.setSize(mWindow.getSize().x * .8, mWindow.getSize().y * .8);
    // font
    mFont.loadFromFile("../Media/GODOFWAR.ttf");
    mStat.setFont(mFont);
    mStat.setCharacterSize(60);
}

void World::draw() {
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);

    //test
    if (mPlayerTank1->mShowInfo)
        mWindow.draw(mStat);
}

void World::update(sf::Time dt) {
    while (!mCommandQ.isEmpty()) {
        mSceneGraph.onCommand(mCommandQ.pop(), dt);
        // std::cout << "mSceneGraph.onCommand(mCommandQ.pop(), dt);.." << std::endl;
    }
    updateView(dt);
    handleCollisions();
    mSceneGraph.update(dt);

    // stat
    std::string stat = " - Player 1 (Green) \n";
    stat += map_to_string(mPlayerTank1->info());
    stat += " - Player 2 (Blue) \n";
    stat += map_to_string(mPlayerTank2->info());
    mStat.setString(stat);
    mStat.setScale(mWorldView.getSize().x / 2000, mWorldView.getSize().x / 2000);
    // centerOrigin(mStat);
    mStat.setPosition(mWorldView.getCenter().x - mWorldView.getSize().x / 2,
                      mWorldView.getCenter().y - mWorldView.getSize().y / 2);

}

CommandQ &World::getCommandQ() {
    return mCommandQ;
}

void World::updateView(sf::Time dt) {
    // update viewport
    // mWorldView.rotate(1);
    sf::Vector2f tankCenter(
            mPlayerTank1->getWorldPosition().x * .5f + mPlayerTank2->getWorldPosition().x * .5f,
            mPlayerTank1->getWorldPosition().y * .5f + mPlayerTank2->getWorldPosition().y * .5f
    );
    sf::Vector2f tankBox(
            mPlayerTank1->getWorldPosition().x - mPlayerTank2->getWorldPosition().x,
            mPlayerTank1->getWorldPosition().y - mPlayerTank2->getWorldPosition().y
    );
    sf::Vector2f scroll(0, 0);
    sf::Vector2f size(mWorldView.getSize());
    float sizeRatio = size.y / size.x;

    // Use scroll in case of camera shake
    // std::cout<< "Tank pos: " << mPlayerTank->getWorldPosition().y << " " << mWorldView.getCenter().y << std::endl;
    if (tankCenter.y < mWorldView.getCenter().y - mWindow.getSize().y * 0.05)
        scroll.y -= mScrollSpeed * dt.asSeconds();
    // mWorldView.move(0,-mScrollSpeed * dt.asSeconds());
    if (tankCenter.y > mWorldView.getCenter().y + mWindow.getSize().y * 0.05)
        scroll.y += mScrollSpeed * dt.asSeconds();
    // mWorldView.move(0,mScrollSpeed * dt.asSeconds());
    if (tankCenter.x < mWorldView.getCenter().x - mWindow.getSize().x * 0.10)
        scroll.x -= mScrollSpeed * dt.asSeconds();
    // mWorldView.move(-mScrollSpeed * dt.asSeconds(),0);
    if (tankCenter.x > mWorldView.getCenter().x + mWindow.getSize().x * 0.10)
        scroll.x += mScrollSpeed * dt.asSeconds();
    // mWorldView.move(mScrollSpeed * dt.asSeconds(),0);
    mWorldView.move(scroll);

    if (abs((int) tankBox.x) > mWorldView.getSize().x - mWindow.getSize().x * 0.4 ||
        abs((int) tankBox.y) > mWorldView.getSize().y - mWindow.getSize().y * 0.5) {
        size.x += mScrollSpeed * dt.asSeconds();
        size.y += mScrollSpeed * dt.asSeconds() * sizeRatio;
    }

    if (size.x > mWindow.getSize().x * .8 &&
        abs((int) tankBox.x) < mWorldView.getSize().x - mWindow.getSize().x * 0.5 &&
        abs((int) tankBox.y) < mWorldView.getSize().y - mWindow.getSize().y * 0.6) {
        size.x -= mScrollSpeed * dt.asSeconds();
        size.y -= mScrollSpeed * dt.asSeconds() * sizeRatio;
    }

    mWorldView.setSize(size);
}

void World::addEntities() {

    srand(static_cast<unsigned int>(time(0)));
    // Load and Build background node
    sf::Texture *ptexture = new sf::Texture;
    ptexture->loadFromFile("../Media/Sand.jpg");
    sf::IntRect textureRect(mWorldBounds);
    ptexture->setRepeated(true);

    SpriteNode *bgSprite = new SpriteNode(*ptexture, textureRect);
    bgSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
    // Add to layer
    mSceneLayers[Background]->attach(bgSprite);

    // Tank - Player 1 - control by Up-Down
    mPlayerTank1 = new Tank(Tank::PlayerUp);
    mPlayerTank1->setPosition(mOrigin - sf::Vector2f(400, 400));
    mPlayerTank1->setDirection(1.f);
    mPlayerTank1->setVelocity(0.f, 40.f);
    mPlayerTank1->mCategory = CTank;
    // Add to layer
    mSceneLayers[Air]->attach(mPlayerTank1);

    // Tank - Player 2 - control by W-S
    mPlayerTank2 = new Tank(Tank::PlayerWS);
    mPlayerTank2->setPosition(mOrigin + sf::Vector2f(400, 400));
    mPlayerTank2->setDirection(1.f);
    mPlayerTank2->setRotation(180.0f);
    mPlayerTank2->setVelocity(0.f, -40.f);
    mPlayerTank2->mCategory = CTank;
    // Add to layer
    mSceneLayers[Air]->attach(mPlayerTank2);

    // Map
    sf::Vector2f bound(mWorldBounds.width, mWorldBounds.height);
    int random = rand() % 10 + 1; // a = 1,...,10
    if (random > 5) {
        // random map
        for (int k = 0; k < 200; k++) {
            if (rand() % 10 > 1)
                continue;
            std::string path = "../Media/Obstacles/Obstacle_";
            path += std::to_string(k % 10);
            path += ".png";
            // "../Media/Obstacles/Obstacle1.png"
            auto obstacle = new Obstacle(path, bound);
            // check place
            if (obstacle->getBoundingRect().intersects(mPlayerTank1->getBoundingRect()) ||
                obstacle->getBoundingRect().intersects(mPlayerTank1->getBoundingRect()))
                delete obstacle;
            else {
                mObstacles.push_back(obstacle);
                mSceneLayers[Air]->attach(obstacle);
            }

        }
    } else {
        // load map
        std::string fileName("../Map/MAP");
        fileName += std::to_string(random) + ".txt";
        std::string path = "../Media/Obstacles/ObstacleWall.png";
        std::ifstream file(fileName);
        std::string line;
        if (file.bad()) std::cout << "Warning! Bad file " << fileName << std::endl;
        for (int k = 0; k < 20; k++) {
            std::vector<bool> data;
            if (!getline(file, line))
                std::cout << "Error! No enough lines in file " << fileName << std::endl;
            std::istringstream ss(line);
            std::string bit;
            for (int l = 0; l < 20; l++) {
                ss >> bit;
                if (bit[0] == '1') {
                    auto obstacle = new Obstacle(path, bound, k - 10, l - 10);
                    mObstacles.push_back(obstacle);
                    mSceneLayers[Air]->attach(obstacle);
                }
            }
        }

    }

    // Sky
    mSceneLayers[Sky]->attach(new Cloud("../Media/Cloud1.png", bound, 96));

    mSceneLayers[Sky]->attach(new Cloud("../Media/Cloud2.png", bound, 64));

    mSceneLayers[Sky]->attach(new Cloud("../Media/Cloud3.png", bound, 255));

    mSceneLayers[Sky]->attach(new Cloud("../Media/Cloud2.png", bound, 96));

    mSceneLayers[Sky]->attach(new Cloud("../Media/Cloud3.png", bound, 128));

    mSceneLayers[Sky]->attach(new Cloud("../Media/Cloud3.png", bound, 128));


}

void World::handleCollisions() {
    // two tanks collision
    if ((mPlayerTank1->getBoundingRect().intersects(mPlayerTank2->getBoundingRect()))) {
        // std::cout << "intersect self" << std::endl;
        // mPlayerTank1->setVelocity(10.0, 10.0);
        float alpha = 0.5; // collision
        sf::Vector2f v1(mPlayerTank1->getVelocity());
        sf::Vector2f v2(mPlayerTank2->getVelocity());
        mPlayerTank1->lastCondition();
        mPlayerTank2->lastCondition();
        // exchange speed
        mPlayerTank1->setVelocity(v2.x * alpha, v2.y * alpha);
        mPlayerTank2->setVelocity(v1.x * alpha, v1.y * alpha);


    }
    // tank1 shot tank2
    mPlayerTank2->gotoBullets(mPlayerTank1->tankBullets_);
    mPlayerTank1->gotoBullets(mPlayerTank2->tankBullets_);

    // tank1 wall
    mPlayerTank1->gotoOb(mObstacles, mWorldBounds);

    // tank 2 wall
    mPlayerTank2->gotoOb(mObstacles, mWorldBounds);

    // bullet 1 wall
    mPlayerTank1->bulletShotOb(mObstacles);

    // bullet 2 wall
    mPlayerTank2->bulletShotOb(mObstacles);
}

int World::winner() {
    if (mPlayerTank1->lost()) return 2; // Player 2 win
    if (mPlayerTank2->lost()) return 1; // Player 1 win
    return 0;
}

void World::reset() {
    mPlayerTank1->setPosition(mOrigin - sf::Vector2f(400, 400));
    mPlayerTank1->setDirection(1.f);
    mPlayerTank1->setRotation(.0f);
    mPlayerTank1->setVelocity(0.f, 40.f);
    mPlayerTank1->setRotation(0.0f);

    mPlayerTank2->setPosition(mOrigin + sf::Vector2f(400, 400));
    mPlayerTank2->setDirection(1.f);
    mPlayerTank2->setRotation(180.0f);
    mPlayerTank2->setVelocity(0.f, -40.f);

    mPlayerTank1->reset();
    mPlayerTank2->reset();

    //delete remaining bullets at the end of game
    while (!mPlayerTank1->tankBullets_.empty()) {
        auto bullet = mPlayerTank1->tankBullets_.front();
        mPlayerTank1->tankBullets_.pop_front();
        mSceneLayers[Air]->detach(bullet);
        delete bullet;
    }
    while (!mPlayerTank2->tankBullets_.empty()) {
        auto bullet = mPlayerTank2->tankBullets_.front();
        mPlayerTank2->tankBullets_.pop_front();
        mSceneLayers[Air]->detach(bullet);
        delete bullet;
    }


    for (auto bullet: mPlayerTank2->tankBullets_) {
        mSceneLayers[Air]->detach(bullet);
    }


}

std::string World::map_to_string(std::map<std::string, std::string> m) {
    std::string output = "";
    for (auto it = m.cbegin(); it != m.cend(); it++)
        output += (it->first) + ":" + (it->second) + "\n";
    return output;
}
