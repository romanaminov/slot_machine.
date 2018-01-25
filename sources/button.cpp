#include "headers/button.h"
#include "headers/textureobjectmanager.h"

Button::Button(ButtonState _state, double _lb_xrf, double _lb_yrf, double _rt_xrf, double _rt_yr) :
Object(_state, _lb_xrf, _lb_yrf, _rt_xrf, _rt_yr)
{
}

Button::~Button()
{
}


void Button::Update() {

    // Обновляем значение флага ena для текстур, связанных с кнопкой
    // одну текстуру выключаем, другую включаем,
    // в зависимости от предыдущего состояния
    TextureMap *TextureMap = this->getTextureMap();
    TextureMap::iterator it;
    for (it = TextureMap->begin(); it != TextureMap->end(); it ++)
    {
        it->second->ena = !(it->second->ena);
    }

    // Изменяем текущее состояние на противоположное
    if (this->getState() == ButtonState::_disabled) {
        this->setState(ButtonState::_enabled);
    }
    else {
        this->setState(ButtonState::_disabled);
    }

}
