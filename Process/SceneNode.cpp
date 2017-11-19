//
// Created by Mengmeng Xu on 11/9/17.
//

#include <iostream>
#include "SceneNode.h"
SceneNode::SceneNode()
{
    mParent = nullptr;
    mCategory = Croot;
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
    for (auto itr = mChildren.begin(); itr != mChildren.end(); ++itr)
        (*itr)->draw(target, states);
}

void SceneNode::update(sf::Time dt) {
    updateCurrent(dt);
    for (auto itr = mChildren.begin(); itr != mChildren.end(); ++itr)
        (*itr)->update(dt);
}

sf::Transform SceneNode::getWorldTransform() const {
    // Identity matrix
    sf::Transform transform = sf::Transform::Identity;
    for (const SceneNode* node = this;
         node != nullptr; node = node->mParent)
        transform = node->getTransform() * transform;
    return transform;
}

void SceneNode::onCommand(const Command &command, sf::Time dt) {
    // std::cout << "@@ > command.category, this->Category " << command.category << ", "<< this->mCategory << std::endl;
    try {
        command.mCategory;
        this->mCategory;
    } catch (const std::exception& e) {
        std::cout<< "Error" << std::endl;
        return;
    }

    if (command.mCategory == this->mCategory){
        // std::cout << "this->Category" << this->mCategory << std::endl;
        command.action(*this, dt);
    }
    for ( int t = 0; t < mChildren.size(); t++){
        auto child = mChildren[t];
        child->onCommand(command, dt);
    }
//    for (auto iter = mChildren.cbegin(); iter!=mChildren.cend(); iter ++){
//        // std::cout << mChildren.end()-mChildren.begin() << std::endl;
//        (*iter)->onCommand(command,dt);
//    }

}
