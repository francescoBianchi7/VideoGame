
#include "PreCompHeaders.h"
#include "GUI.h"

GUI::Button::Button(float x,float y,float width,float height,
               sf::Font* font,const std::string buttonText,unsigned characterSize,
               sf::Color text_idleColor,sf::Color text_hoverColor,sf::Color text_pressedColor,
               sf::Color idleColor,sf::Color hoverColor,sf::Color pressedColor ,sf::Color outlineIdleColor,sf::Color outlineHoverColor,sf::Color outlinePressedColor,
               short unsigned id) {

    this->buttonState=BTN_Idle;
    this->id=id;

    this->shape.setPosition(sf::Vector2f(x,y));
    this->shape.setSize(sf::Vector2f(width,height));
    this->shape.setFillColor(this->idleColor);
    this->shape.setOutlineThickness(1.f);
    this->shape.setFillColor(outlineIdleColor);

    this->font=font;
    this->buttonText.setFont(*this->font);
    this->buttonText.setString(buttonText);
    this->buttonText.setFillColor(text_idleColor);
    this->buttonText.setCharacterSize(characterSize);//to be adjusted
    this->buttonText.setPosition(
            shape.getPosition().x+(this->shape.getGlobalBounds().width/2.f) -this->buttonText.getGlobalBounds().width/2.f,
            shape.getPosition().y);
            //+(this->shape.getGlobalBounds().height/2.f)-this->buttonText.getGlobalBounds().height/2.f);

    this->text_IdleColor=text_idleColor;
    this->text_hoverColor=text_hoverColor;
    this->text_pressedColor=text_pressedColor;
    this->idleColor=idleColor;
    this->hoverColor=hoverColor;
    this->pressedColor=pressedColor;
    this->outlineIdleColor=outlineIdleColor;
    this->outlineHoverColor=outlineHoverColor;
    this->outlinePressedColor=outlinePressedColor;

}

GUI::Button::~Button() {

}
void GUI::Button::render(sf::RenderTarget &target) {
    target.draw(this->shape);
    target.draw(this->buttonText);
}

void GUI::Button::update(const sf::Vector2f mousePos) {
    //idle
    buttonState=BTN_Idle;
    shape.setFillColor(this->idleColor);
    this->buttonText.setFillColor(this->text_IdleColor);
    shape.setOutlineColor(this->outlineIdleColor);
    //hover
    if(this->shape.getGlobalBounds().contains(mousePos)){
        buttonState=BTN_Hover;
        shape.setFillColor(this->hoverColor);
        this->buttonText.setFillColor(this->text_hoverColor);
        shape.setOutlineColor(this->outlineHoverColor);
        //Pressed
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            buttonState=BTN_Pressed;
            shape.setFillColor(this->pressedColor);
            this->buttonText.setFillColor(this->text_pressedColor);
            shape.setOutlineColor(this->outlinePressedColor);
        }
    }
}
//ACCESSORS
//used in gameEngine
bool GUI::Button::isBTNPressed() const {
    if(this->buttonState==BTN_Pressed)
        return true;
    return false;
}

std::string GUI::Button::getText(){
    return this->buttonText.getString();
}

const short unsigned &GUI::Button::getId() const {
    return this->id;
}
//MODIFIER
void GUI::Button::setText(const std::string buttonText) {
    this->buttonText.setString(buttonText);
}

void GUI::Button::setId(const unsigned short id) {
    this->id=id;
}

//DROPDOWNLIST CLASS
GUI::DropDownList::DropDownList(float x,float y,float width,float height,sf::Font& font,std::string list[],unsigned nrofElements,unsigned defaultIndex)
:font(font),showList(false),keyTimeMax(1.f),keyTime(0.f) {
    this->activeElement=new GUI::Button(x,y,width,height,
                                        &this->font,list[defaultIndex],12,
                                        sf::Color(255,255,255,150),
                                        sf::Color(255,255,255,255),
                                        sf::Color(20,20,20,50),
                                        sf::Color(70,70,70,200),
                                        sf::Color(151,151,151,0),
                                        sf::Color(255,150,25,0),
                                        sf::Color(255,255,255,200),
                                        sf::Color(255,255,255,0),
                                        sf::Color(20,20,20,50));
    for(size_t i=0;i<nrofElements;i++){
        this->list.push_back(new GUI::Button(x,y+((i+1)*height),width,height,
                                             &this->font,list[i],14,
                                             sf::Color(255,255,255,200),
                                             sf::Color(255,255,255,255),
                                             sf::Color(20,20,20,50),
                                             sf::Color(70,70,70,200),
                                             sf::Color(151,151,151,0),
                                             sf::Color(255,150,25,0),
                                             sf::Color(255,255,255,200),
                                             sf::Color(255,255,255,0),
                                             sf::Color(20,20,20,50),i));
        this->list[i]->setId(i);
    }
}

GUI::DropDownList::~DropDownList() {
    delete this->activeElement;
    for (size_t i = 0; i < this->list.size(); i++)
    {
        delete this->list[i];
    }
}

void GUI::DropDownList::render(sf::RenderTarget &target) {
    activeElement->render(target);
    if(this->showList){
        for(auto &i:list)
            i->render(target);
    }
}

void GUI::DropDownList::update(const sf::Vector2i &mousePosWindow,const float &dt) {
    this->updateKeyTime(dt);
    this->activeElement->update(static_cast<sf::Vector2f>(mousePosWindow));
    //shows and hides list
    if(this->activeElement->isBTNPressed() && this->getKeyTime()){
        if(showList)
            this->showList=false;
        else{
            this->showList=true;
            std::cout<<this->showList;
        }
    }

    if (this->showList){
        for (auto &i : this->list)
        {
            i->update(static_cast<sf::Vector2f>(mousePosWindow));
            if(i->isBTNPressed()&& this->getKeyTime()){
                this->showList = false;
                this->activeElement->setText(i->getText());
                this->activeElement->setId(i->getId());
            }
        }
    }
}

void GUI::DropDownList::updateKeyTime(const float &dt) {
    if(this->keyTime>=this->keyTimeMax)
        this->keyTime+=10.f*dt;
}

bool GUI::DropDownList::getKeyTime() {
    if(keyTime<keyTimeMax)
    {
        keyTime=0.f;
        return true;
    }
        return false;
}

const unsigned short &GUI::DropDownList::getActiveElementId() const{
    return this->activeElement->getId();
}


