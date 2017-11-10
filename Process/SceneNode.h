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

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable {
    /*
public:
    typedef std::unique_ptr<SceneNode> Ptr;
     */
private:
    SceneNode* mParent;
    // I save all the children pointer into a vector
    std::vector<SceneNode*> mChildren; // Book says it can not work P56
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    SceneNode();
    void attach(SceneNode* child);
    SceneNode* detach(SceneNode* child);

};


#endif //TANKCRAFT_SCENENODE_H
