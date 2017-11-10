//
// Created by Mengmeng Xu on 11/9/17.
//

#include "SceneNode.h"
SceneNode::SceneNode()
{
    mParent = nullptr;
    // mChildren = NULL;
}

void SceneNode::attach(SceneNode* child)
{
    // connect two node
    child->mParent = this;
    this->mChildren.push_back(child);
}

SceneNode* SceneNode::detach(SceneNode* child)
{
    // we need find the child
    child->mParent = nullptr;
    for (auto iter=this->mChildren.cbegin(); iter!=this->mChildren.cend(); iter++){
        if ( (*iter)==child ){
            this->mChildren.erase(iter);
        }
    }
    return child;
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // find transform
    states.transform *= getTransform();
    // draw current scene
    drawCurrent(target, states);
    // draw children
    for (auto itr = mChildren.begin(); itr != mChildren.end(); ++itr) {
        (*itr)->draw(target, states);
    }
}