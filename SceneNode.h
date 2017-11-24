//
// Created by Mengmeng Xu on 11/9/17.
//

#ifndef TANKCRAFT_SCENENODE_H
#define TANKCRAFT_SCENENODE_H

#include <memory> // use unique_ptr
// a smart pointer that owns and manages another object
// through a pointer and disposes of that object when the unique_ptr goes
// * out of scope * .
#include <vector>
#include <SFML/Graphics.hpp>
#include "CommandQ.h"
#include "Category.h"

struct Command; // Declare class

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable {
    /*
public:
    typedef std::unique_ptr<SceneNode> Ptr;
     */
private:
    SceneNode* mParent;
    // I save all the children pointer into a vector
    std::vector<SceneNode*> mChildren; // Book says it can not work P56

    // draw all node in SceneNode
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    // draw current
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {};

    // update current
    virtual void updateCurrent(sf::Time dt) {};
    void drawBoundingRect(sf::RenderTarget& target, sf::RenderStates) const;


public:
    SceneNode();
    void attach(SceneNode* child);
    SceneNode* detach(SceneNode* child);

    // update all node in SceneNode
    virtual void update(sf::Time dt);

    // compute position in world coordinate
    sf::Transform getWorldTransform() const;
    sf::Vector2f getWorldPosition() const {
        return getWorldTransform() * sf::Vector2f();
    }
    void onCommand(const Command& command, sf::Time dt);
    SceneNode*& getParent() {return mParent;}
    Category mCategory;
    virtual sf::FloatRect getBoundingRect() const;

};


#endif //TANKCRAFT_SCENENODE_H
