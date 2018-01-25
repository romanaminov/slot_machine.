#ifndef BUTTON_START_H
#define BUTTON_START_H

#include "headers/button.h"

class ButtonStart: public Button
{
public:
    ButtonStart(ButtonState _state, double _lb_xrf, double _lb_yrf, double _rt_xrf, double _rt_yr);
    ~ButtonStart();
private:
    // Связанные текстуры. Отображают состояние кнопки,
    // кога она выключена или включена
    std::shared_ptr<TextureObjectManager> textureEna;
    std::shared_ptr<TextureObjectManager> textureDis;
};

#endif // BUTTON_START_H
