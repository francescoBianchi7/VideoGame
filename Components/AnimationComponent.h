//
// Created by bianc on 29/12/2021.
//

#ifndef VIDEOGAME_ANIMATIONCOMPONENT_H
#define VIDEOGAME_ANIMATIONCOMPONENT_H
#include "PreCompHeaders.h"

class AnimationComponent {
private:
    class Animation{
    public:
        sf::Sprite& sprite;
        sf::Texture& textureSheet;
        float animationTimer;//time to pass between an anim and another
        float timer;
        int width;
        int height;
        sf::IntRect startRect{},currentRect{},endRect{};//currentRect cycles throught start and end
        Animation(sf::Sprite& sprite,sf::Texture& textureSheet,float animation_timer,
                  int start_frame_x,int start_frame_y,int frames_x
                  ,int frames_y,int width,int height)
        :sprite(sprite),textureSheet(textureSheet),
        animationTimer(animation_timer),width(width),height(height)
        {
            //frames_x tells me how many frames i cycle
            this->timer=0.f;
            this->startRect=sf::IntRect(start_frame_x*width,start_frame_y*height,width,height);
            this->endRect=sf::IntRect(frames_x*width,frames_y*height,width,height);
            this->currentRect=startRect;
            this->sprite.setTexture(this->textureSheet,true);
            this->sprite.setTextureRect(this->startRect);
        }
        void play(const float& dt){
            //update timer
            this->timer+=50.f*dt;
            if(this->timer>=this->animationTimer){
                //reset timer
                this->timer=0.f;
                //Animate
                if(this->currentRect!=this->endRect){
                    this->currentRect.left+=this->width;
                }
                else
                {
                    this->currentRect.left=this->startRect.left;
                }
                this->sprite.setTextureRect(this->currentRect);
            }
        }//updates which Rect is on
        void reset(){
            this->timer=0.f;
            this->currentRect=this->startRect;
        }//resets cycle
    };
    //ATTRIBUTES FOR ANIMATIONCOMPONENT CLASS
    sf::Sprite& sprite;
    sf::Texture& textureSheet;
    std::map<std::string,Animation*> animations;
    Animation* lastAnimation;

public:
    AnimationComponent(sf::Sprite& sprite,sf::Texture& textureSheet);
    virtual ~AnimationComponent();
    void addAnimation(const std::string& key,float animation_timer,
                                            int start_frame_x,int start_frame_y,int frames_x
                                            ,int frames_y,int width,int height);
    void play(const std::string& key,const float& dt);

};


#endif //VIDEOGAME_ANIMATIONCOMPONENT_H
