//
// Created by bianc on 29/12/2021.
//

#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite,sf::Texture& textureSheet)
:sprite(sprite),textureSheet(textureSheet),lastAnimation(nullptr) {}

AnimationComponent::~AnimationComponent() {
    delete lastAnimation;
}
//loads animation sheet
void AnimationComponent::addAnimation(const std::string& key,float animation_timer,
                                      int start_frame_x,int start_frame_y,int frames_x
                                      ,int frames_y,int width,int height) {
    this->animations[key]=new Animation(this->sprite,this->textureSheet,animation_timer,
                                        start_frame_x,start_frame_y,
                                        frames_x,frames_y,width,height);
}

void AnimationComponent::play(const std::string& key,const float &dt) {
    if (this->lastAnimation != this->animations[key])
    {
        if (this->lastAnimation == nullptr)
            this->lastAnimation = this->animations[key];
        else
        {
            this->lastAnimation->reset();
            this->lastAnimation = this->animations[key];
        }
    }
    this->animations[key]->play(dt);
}

